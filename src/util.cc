#include "util.h"

namespace {
    using namespace NTL;
}

namespace gnfs {
    ZZ eval(const ZZX& f, const ZZ& a) {
        // Remainder Theorem: f / (x - a) = f(a)
        ZZX rem = f % (ZZX(INIT_MONO, 1) - ZZX(a));
        return rem[0];
    }

    vec_GF2 bitfield(const ZZ& bf) {
        vec_GF2 ret(INIT_SIZE, NumBits(bf));
        for (long i = 0; i < NumBits(bf); i++) {
            ret[i] = bit(bf, i);
        }
        return ret;
    }

    ZZ lincon(const ZZ& a, const ZZ& b, const ZZ& m) {
        ZZ d, s, t;
        XGCD(d, s, t, a, m);
        if (b % d != 0)
            return m;
        return s * (b / d);
    }
}
