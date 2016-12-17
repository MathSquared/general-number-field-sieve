#include "smooth_pair_finder.h"

#include <NTL/RR.h>

#include "util.h"

namespace {
    using namespace NTL;
}

namespace gnfs {
    SmoothPairFinder::SmoothPairFinder(const ZZ& n, long B, const ZZX& f, const ZZ& m)
      : n_(n), B_(B), f_(f), m_(m), M_(B), Mold_(0), a_(B), b_(-1) {
        ZZX fprime = diff(f);

        // Figure out what the factorbase columns represent.
        // Each one is a pair (p,r), where p is a prime up to B
        // and r is something where f(r) \equiv 0 (mod p).
        PrimeSeq pseq;
        long p;
        while ((p = pseq.next()) <= B) {
            cols_modular_.push_back(p);
            for (long r = 0; r < p; r++) {
                ZZ res = eval(f, ZZ(r));
                if (res % p == 0)
                    cols_algebraic_.emplace_back(p, r);
            }
        }

        // Generate pairs (q,s) for Adleman columns.
        // For each q (named p here), find an s where
        // f(s) \equiv 0 (mod p) and f'(s) \not\equiv 0 (mod p).
        long k = conv<long>(3 * log(conv<RR>(n)));
        long k_so_far = 0;
        while (k_so_far < k) {
            for (long s = 0; s < p; s++) {
                ZZ zs(s);
                if (eval(f, zs) % p == 0 && eval(fprime, zs) % p != 0) {
                    cols_adleman_.emplace_back(p, s);
                    k_so_far++;
                }
            }

            p = pseq.next();
        }
    }

    std::pair<std::pair<long, long>, vec_GF2> SmoothPairFinder::get() {
        // TODO
        return std::make_pair(std::make_pair(0, 0), vec_GF2(INIT_SIZE, num_cols()));
    }
}
