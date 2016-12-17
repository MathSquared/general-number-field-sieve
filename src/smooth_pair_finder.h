#ifndef _SMOOTH_PAIR_FINDER_H_
#define _SMOOTH_PAIR_FINDER_H_

#include <vector>

#include <NTL/vec_GF2.h>
#include <NTL/ZZ.h>
#include <NTL/ZZX.h>

namespace gnfs {
    // Produces rows of a matrix in GF2 corresponding to pairs a,b, where
    // - the ideal (a - \alpha b) is B-smooth and
    // - a - mb is B-smooth mod n.
    class SmoothPairFinder {
      public:
        // Creates an apparatus to find B-smooth pairs and exponent vectors
        // with parameters n, f, and m.
        SmoothPairFinder(const NTL::ZZ& n, long B, const NTL::ZZX& f,
                const NTL::ZZ& m);

        // Returns the number of columns in an exponent vector
        // returned from this apparatus.
        long num_cols() {
            return 1 + cols_modular_.size() + cols_algebraic_.size()
                + cols_adleman_.size();
        }

        // Produces a smooth exponent vector,
        // returning a, b, and the exponent vector.
        std::pair<std::pair<long, long>, NTL::vec_GF2> get();
      private:
        const NTL::ZZ& n_;
        const long B_;
        const NTL::ZZX& f_;
        const NTL::ZZ& m_;

        // Size of the region we're currently searching.
        // a_ and b_ range over [-M,M]\[-Mold,Mold] x (Mold,M].
        // (This intentionally excludes a=0 when Mold=0.)
        const long M_;
        // If we had to expand M_, this is the size of the region
        // that we'd already examined.
        // Starts at 0.
        const long Mold_;
        // Cursors for the search. These indicate where we last left off.
        // Each request of a row starts at the pair after (a,b),
        // in b-major order.
        const long a_;
        const long b_;

        // The entries in returned exponent vectors represent
        // modular factorbase entries, algebraic factorbase entries,
        // or Adleman columns.
        // Also, the first column represents the "prime" -1
        // in the modular factorbase.
        std::vector<long> cols_modular_;
        std::vector<std::pair<long, long>> cols_algebraic_;  // pairs (p,r)
        std::vector<std::pair<long, long>> cols_adleman_;  // pairs (q,s)
    };
}

#endif
