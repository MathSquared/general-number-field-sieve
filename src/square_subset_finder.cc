#include "square_subset_finder.h"

#include <vector>

#include <NTL/vec_vec_GF2.h>

namespace {
    using namespace NTL;
    using namespace std;
}

namespace gnfs {
    template <typename RowGenerator>
    vector<pair<typename SquareSubsetFinder<RowGenerator>::Index, vec_GF2>> SquareSubsetFinder<RowGenerator>::get() {
        // TODO
    }
}
