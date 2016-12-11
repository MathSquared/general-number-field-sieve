// Functions used in the setup phase.

#ifndef _SETUP_H_
#define _SETUP_H_

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>

namespace gnfs {
    // If f is irreducible, returns f(m) = n.
    // Else, returns g(m) for some g|f, which is guaranteed to be a
    // nontrivial factor of n.
    NTL::ZZ check_f_irred(const NTL::ZZX& f, const NTL::ZZ& m);
}

#endif
