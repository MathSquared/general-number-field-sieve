#ifndef _SQUARE_SUBSET_FINDER_H_
#define _SQUARE_SUBSET_FINDER_H_

#include <utility>
#include <vector>

#include <NTL/mat_GF2.h>
#include <NTL/vec_GF2.h>

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
        SquareSubsetFinder(RowGenerator& rg) : rg_(rg), matrix_(NTL::INIT_SIZE, 0, rg.num_cols()), basis_cursor_(-1) { }

        // #TemplateMetaprogramming
        std::vector<std::pair<typename SquareSubsetFinder<RowGenerator>::Index, NTL::vec_GF2>> get();
      private:
        RowGenerator& rg_;
        NTL::mat_GF2 matrix_;

        // When we find a basis for the kernel, we store the basis here
        NTL::mat_GF2 basis_;
        // and where we are in it here. -1 means we don't yet have a basis.
        NTL::ZZ basis_cursor_;

        typedef decltype(rg_.get().first) Index;
    };
}

#endif
