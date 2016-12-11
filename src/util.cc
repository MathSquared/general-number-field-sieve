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
}
