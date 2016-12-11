// Functions for computing global parameters used by the GNFS.

#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>

namespace gnfs {
    // Computes a suggested value for d,
    // the degree of the polynomial used in the sieve.
    long param_d(const NTL::ZZ& n);

    // Computes a suggested value for B,
    // the smoothness bound for the pairs we sieve over.
    long param_B(const NTL::ZZ& n);

    // Computes a suggested value for f,
    // the polynomial used in the sieve (of degree d),
    // and a root m mod n.
    std::pair<NTL::ZZ, NTL::ZZX> param_mf(const NTL::ZZ& n, long d);
}

#endif
