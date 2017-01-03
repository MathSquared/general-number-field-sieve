// Utilities, or: things that should be in NTL

#ifndef _UTIL_H_
#define _UTIL_H_

#include <NTL/vec_GF2.h>
#include <NTL/ZZ.h>
#include <NTL/ZZX.h>

namespace gnfs {
    // Returns f(a).
    NTL::ZZ eval(const NTL::ZZX& f, const NTL::ZZ& a);

    // Turns a ZZ into a vec_GF2, MSB first,
    // length equal to the bitlength of bf.
    NTL::vec_GF2 bitfield(const NTL::ZZ& bf);

    // Solves the linear congruence
    // ax \equiv b (mod m).
    long lincon(long a, long b, long m);
    NTL::ZZ lincon(const NTL::ZZ& a, const NTL::ZZ& b, const NTL::ZZ& m);
}

#endif
