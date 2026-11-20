// cache_core.hpp — shared bit-exact reference model for the ext_cache black
// box (used by both the C++ user class and to cross-check cache.v).
//
// Geometry mirrors a scaled-down DavinciBaseLine v5_l1d_cache flavor:
//   2 sets x 2 ways, 16-byte lines, 32-bit word-aligned requests.
//   addr bits: [1:0] ignored, [4:2] word offset in line (4 words x 32b =
//   128b line data), [5] set index, [>=6] tag.
//
// Cycle contract (docs/external-modules.md):
//   eval()        — combinational view of the CURRENT inputs vs the
//                   registered state: hit / rdata / dirty_evict / resp_valid.
//   tick_commit() — state update: write accept, miss FSM advance, flush.
#pragma once
#include <cstdint>
#include <cstring>

namespace ext_cache_core {

constexpr unsigned kLineWords = 4;                 // 4 x 32b = 128b line
constexpr unsigned kSets = 2;
constexpr unsigned kWays = 2;
constexpr unsigned kWordBits = 2;                  // log2(kLineWords)
constexpr unsigned kSetBits = 1;                   // log2(kSets)
constexpr unsigned kTagLsb = kWordBits + kSetBits; // addr[5]=set, [>=6]=tag
constexpr unsigned kRefillLatency = 2;
constexpr unsigned kBackWords = 1u << 12;          // 4K-word backing store

// 128-bit line payload carried over the 128b data port.
struct Bits128 {
    std::uint64_t lo;
    std::uint64_t hi;
};

inline Bits128 pack_line(const std::uint32_t *w) {
    return Bits128{(std::uint64_t)w[0] | ((std::uint64_t)w[1] << 32),
                   (std::uint64_t)w[2] | ((std::uint64_t)w[3] << 32)};
}

inline void unpack_line(Bits128 v, std::uint32_t *w) {
    w[0] = (std::uint32_t)(v.lo & 0xFFFFFFFFu);
    w[1] = (std::uint32_t)(v.lo >> 32);
    w[2] = (std::uint32_t)(v.hi & 0xFFFFFFFFu);
    w[3] = (std::uint32_t)(v.hi >> 32);
}

inline unsigned set_of(std::uint32_t addr) { return (addr >> kWordBits) & (kSets - 1); }
inline std::uint32_t tag_of(std::uint32_t addr) { return addr >> kTagLsb; }
inline unsigned word_of(std::uint32_t addr) { return (addr >> 2) & (kLineWords - 1); }
inline std::uint32_t line_base(std::uint32_t addr) {
    return addr & ~std::uint32_t((1u << kTagLsb) - 1);
}

struct Line {
    std::uint32_t tag;
    std::uint32_t word[kLineWords];
    bool valid;
    bool dirty;
};

struct Inputs {
    std::uint32_t addr;
    bool req_valid;
    bool wr;
    Bits128 wdata;
    std::uint16_t wmask;
    bool flush;
};

struct CombOut {
    Bits128 rdata;
    bool hit;
    bool resp_valid;
    bool dirty_evict;
};

// Reference model: one instance holds the whole cache state.
struct Model {
    Line line[kSets][kWays];
    std::uint32_t age[kSets][kWays];
    std::uint32_t now;

    // Single-entry miss FSM (refill = kRefillLatency cycles after accept).
    bool miss_pending;
    std::uint32_t miss_addr;
    bool miss_write;
    std::uint32_t miss_wdata[kLineWords];
    std::uint16_t miss_wmask;
    bool miss_dirty_evict;
    int miss_timer; // response is served (resp_valid=1) when timer == 0

    // Backing store standing in for the next-level memory.
    std::uint32_t backing[kBackWords];

    void reset() {
        std::memset(this, 0, sizeof(*this));
        for (unsigned s = 0; s < kSets; ++s)
            for (unsigned w = 0; w < kWays; ++w)
                line[s][w].valid = false;
    }

    int find_hit(unsigned s, std::uint32_t tag) const {
        for (unsigned w = 0; w < kWays; ++w)
            if (line[s][w].valid && line[s][w].tag == tag)
                return (int)w;
        return -1;
    }

    unsigned lru_way(unsigned s) const {
        unsigned oldest = 0;
        for (unsigned w = 1; w < kWays; ++w)
            if (age[s][w] < age[s][oldest])
                oldest = w;
        return oldest;
    }

    // Same-cycle combinational view. `miss_resp` covers the cycle where a
    // previously accepted read-miss completes.
    CombOut eval(const Inputs &in) const {
        CombOut out{};
        out.hit = false;
        out.resp_valid = false;
        out.dirty_evict = false;

        if (in.req_valid && !in.flush) {
            const unsigned s = set_of(in.addr);
            const int w = find_hit(s, tag_of(in.addr));
            if (w >= 0) {
                out.hit = true;
                out.resp_valid = true;
                const Line &l = line[s][w];
                if (in.wr) {
                    // Write hit: combinational view returns the line WITH the
                    // new word patched in (write-through view of this cycle).
                    std::uint32_t tmp[kLineWords];
                    for (unsigned i = 0; i < kLineWords; ++i)
                        tmp[i] = l.word[i];
                    tmp[word_of(in.addr)] = (std::uint32_t)(in.wdata.lo >> (32 * word_of(in.addr)))
                                            ; // lo holds words 0..1; hi holds 2..3
                    // recompute properly below (word_of may be 2 or 3)
                    switch (word_of(in.addr)) {
                    case 0: tmp[0] = (std::uint32_t)(in.wdata.lo & 0xFFFFFFFFu); break;
                    case 1: tmp[1] = (std::uint32_t)(in.wdata.lo >> 32); break;
                    case 2: tmp[2] = (std::uint32_t)(in.wdata.hi & 0xFFFFFFFFu); break;
                    default: tmp[3] = (std::uint32_t)(in.wdata.hi >> 32); break;
                    }
                    out.rdata = pack_line(tmp);
                } else {
                    out.rdata = pack_line(l.word);
                }
            }
        }
        // Read-miss completion response.
        if (miss_pending && !miss_write && miss_timer == 0) {
            if (!out.resp_valid) {
                out.resp_valid = true;
                std::uint32_t tmp[kLineWords];
                for (unsigned i = 0; i < kLineWords; ++i)
                    tmp[i] = backing[(line_base(miss_addr) >> 2) + i];
                out.rdata = pack_line(tmp);
                out.dirty_evict = miss_dirty_evict;
            }
        }
        return out;
    }

    // State update at end of cycle.
    void tick_commit(const Inputs &in) {
        ++now;

        // Flush: invalidate every line (dirty data stays in the backing store
        // because write-back is modelled as immediate).
        if (in.flush) {
            for (unsigned s = 0; s < kSets; ++s)
                for (unsigned w = 0; w < kWays; ++w)
                    line[s][w].valid = false;
            miss_pending = false;
            miss_timer = -1;
            return;
        }

        // Advance the miss FSM.
        if (miss_pending) {
            if (miss_timer > 0) {
                --miss_timer;
            } else {
                // Fill the line now (read or write-miss allocation).
                fill_from_miss();
                miss_pending = false;
                miss_timer = -1;
            }
        }

        if (!in.req_valid)
            return;

        const unsigned s = set_of(in.addr);
        const std::uint32_t tag = tag_of(in.addr);
        const int w = find_hit(s, tag);

        if (in.wr) {
            if (w >= 0) {
                // Write hit: patch the word in place.
                apply_word(line[s][w], in.addr, in.wdata);
                line[s][w].dirty = true;
                age[s][w] = now;
            } else if (!miss_pending) {
                // Write miss: allocate via backing store, mark dirty.
                start_miss(in.addr, /*write=*/true, in.wdata, in.wmask);
            }
        } else {
            if (w >= 0) {
                age[s][w] = now; // read hit refreshes LRU
            } else if (!miss_pending) {
                start_miss(in.addr, /*write=*/false, in.wdata, in.wmask);
            }
        }
    }

private:
    static void apply_word(Line &l, std::uint32_t addr, Bits128 v) {
        switch (word_of(addr)) {
        case 0: l.word[0] = (std::uint32_t)(v.lo & 0xFFFFFFFFu); break;
        case 1: l.word[1] = (std::uint32_t)(v.lo >> 32); break;
        case 2: l.word[2] = (std::uint32_t)(v.hi & 0xFFFFFFFFu); break;
        default: l.word[3] = (std::uint32_t)(v.hi >> 32); break;
        }
    }

    void fill_from_miss() {
        const unsigned s = set_of(miss_addr);
        const std::uint32_t tag = tag_of(miss_addr);
        const unsigned victim = pick_victim(s);
        Line &l = line[s][victim];

        // Refill from backing store, then apply pending write if any.
        const std::uint32_t base = line_base(miss_addr) >> 2;
        for (unsigned i = 0; i < kLineWords; ++i)
            l.word[i] = backing[base + i];
        if (miss_write)
            apply_word(l, miss_addr,
                       Bits128{(std::uint64_t)miss_wdata[0] | ((std::uint64_t)miss_wdata[1] << 32),
                               (std::uint64_t)miss_wdata[2] | ((std::uint64_t)miss_wdata[3] << 32)});
        l.tag = tag;
        l.valid = true;
        l.dirty = miss_write;
        age[s][victim] = now;
    }

    unsigned pick_victim(unsigned s) {
        for (unsigned w = 0; w < kWays; ++w)
            if (!line[s][w].valid)
                return w;
        return lru_way(s);
    }

    void start_miss(std::uint32_t addr, bool write, Bits128 wdata, std::uint16_t wmask) {
        const unsigned s = set_of(addr);
        const std::uint32_t tag = tag_of(addr);
        const int w = find_hit(s, tag);
        miss_pending = true;
        miss_addr = addr;
        miss_write = write;
        unpack_line(wdata, miss_wdata);
        miss_wmask = wmask;
        miss_timer = kRefillLatency - 1;
        // Dirty eviction when the chosen victim line is dirty.
        const unsigned victim = pick_victim(s);
        miss_dirty_evict = line[s][victim].valid && line[s][victim].dirty;
        if (miss_dirty_evict) {
            // Write back the victim into the backing store first.
            const std::uint32_t vbase = ((line[s][victim].tag << kTagLsb) | (s << kWordBits)) >> 2;
            for (unsigned i = 0; i < kLineWords; ++i)
                backing[vbase + i] = line[s][victim].word[i];
        }
    }
};

} // namespace ext_cache_core
