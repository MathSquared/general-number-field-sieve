// Compute the norm of a - \alpha b given f, a, and b.

#ifndef _NORM_FINDING_H_
#define _NORM_FINDING_H_

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>

namespace gnfs {
    // Returns the norm. This is equivalent to evaluating
    // b^d f(a/b),
    // where d is the degree of f.
    NTL::ZZ eval_norm(const NTL::ZZX& f, const NTL::ZZ& a, const NTL::ZZ& b);
}

#endif
