#include "gnfs.h"

#include "parameters.h"
#include "setup.h"

namespace {
    using namespace NTL;
}

namespace gnfs {
    ZZ find_factor(const ZZ& n) {
        // Set parameters: d,B,m,f.
        long d = param_d(n);
        long B = param_B(n);
        auto mf = param_mf(n, d);
        ZZ m = mf.first;
        ZZX f = mf.second;

        // Check if f is irreducible.
        ZZ f_irred = check_f_irred(f, m);
        if (f_irred != n) return f_irred;

        // Sieve until we have a suitable matrix.

        // Find a linear dependence in the matrix.

        // Get gamma, v, and u.

        // Return a factor.
    }
}
