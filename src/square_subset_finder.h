#ifndef _SQUARE_SUBSET_FINDER_H_
#define _SQUARE_SUBSET_FINDER_H_

#include <utility>
#include <vector>

#include <NTL/mat_GF2.h>
#include <NTL/vec_GF2.h>

#include "smooth_pair_finder.h"

namespace gnfs {
    // Reads exponent vectors until it finds a subset whose product is square.
    //
    // RowGenerator shall implement two methods:
    // - std::pair<Index, vec_GF2> get(), which returns the next
    //   exponent vector and its associated index object
    // - long num_cols(), which returns the size of any vector
    //   returned by get()
    template <typename RowGenerator>
    class SquareSubsetFinder {
      public:
        // To use rg_ instead of the declval stuff,
        // I have to declare Index after rg_,
        // but then get() can't use Index.
        typedef decltype(std::declval<RowGenerator>().get().first) Index;

        SquareSubsetFinder(RowGenerator& rg) : rg_(rg), matrix_(NTL::INIT_SIZE, 0, rg.num_cols()), basis_cursor_(-1) { }

        // #TemplateMetaprogramming
        std::vector<std::pair<typename SquareSubsetFinder<RowGenerator>::Index, NTL::vec_GF2>> get();
      private:
        RowGenerator& rg_;
        NTL::mat_GF2 matrix_;
        std::vector<Index> indices_;

        // When we find a basis for the kernel, we store the basis here
        NTL::mat_GF2 basis_;
        // and where we are in it here. -1 means we don't yet have a basis.
        // The cursor is where we last left off.
        NTL::ZZ basis_cursor_;

        // If true, we only return subsets that include
        // the last row of the matrix.
        // We use this after adding a row to matrix_
        // to make sure we don't return sets that we've returned previously.
        bool suppress_;
    };

    template class SquareSubsetFinder<SmoothPairFinder>;
}

#endif
