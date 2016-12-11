#ifndef _GNFS_H_
#define _GNFS_H_

#include <NTL/ZZ.h>

namespace gnfs {
    // Finds a nontrivial factor of n.
    NTL::ZZ find_factor(const NTL::ZZ& n);
}

#endif
