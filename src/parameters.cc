#include "parameters.h"

#include <NTL/RR.h>

namespace {
    using namespace NTL;
}

namespace gnfs {
    long param_d(const ZZ& n) {
        RR ln = log(conv<RR>(n));
        RR base = (3 * ln) / log(ln);
        return conv<long>(pow(base, RR(1.0/3)));
    }

    long param_B(const ZZ& n) {
        RR ln = log(conv<RR>(n));
        RR base = 8.0 / 9 * ln * log(ln) * log(ln);
        return conv<long>(exp(pow(base, RR(1.0/3))));
    }

    std::pair<ZZ, ZZX> param_mf(const ZZ& n, long d) {
        ZZ m = conv<ZZ>(pow(conv<RR>(n), RR(1.0/d)));

        // Write n in base m
        ZZX f;
        ZZ cur = n;
        long i = 0;
        while (cur != 0) {
            SetCoeff(f, i, cur % m);
            cur /= m;
            i++;
        }

        return std::make_pair(m, f);
    }
}
