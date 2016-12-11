#include "setup.h"

#include <NTL/ZZXFactoring.h>

#include "util.h"

namespace {
    using namespace NTL;
}

namespace gnfs {
    ZZ check_f_irred(const ZZX& f, const ZZ& m) {
        ZZ c;
        vec_pair_ZZX_long factors;

        factor(c, factors, f);

        // just evaluate at first factor
        // if irreducible, this spits out f(m)
        return eval(factors[0].a, m);
    }
}
