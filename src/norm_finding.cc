#include "norm_finding.h"

namespace {
    using namespace NTL;
}

namespace gnfs {
    ZZ eval_norm(const ZZX& f, const ZZ& a, const ZZ& b) {
        long d = deg(f);
        ZZ ret(0);

        // iterate from 0 through d
        for (long i = 0; i <= d; i++) {
            ret += f[i] * power(a, i) * power(b, d - i);
        }

        return ret;
    }
}
