#ifndef _GNFS_H_
#define _GNFS_H_

#include <NTL/ZZ.h>

namespace gnfs {
    // Finds a nontrivial factor of n.
    NTL::ZZ factor(NTL::ZZ n);
}

#endif
