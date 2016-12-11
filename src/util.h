// Utilities, or: things that should be in NTL

#ifndef _UTIL_H_
#define _UTIL_H_

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>

namespace gnfs {
    // Returns f(a).
    NTL::ZZ eval(const NTL::ZZX& f, const NTL::ZZ& a);
}

#endif
