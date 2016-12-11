#include "square_subset_finder.h"

#include <vector>

#include <NTL/vec_vec_GF2.h>

#include "util.h"

namespace {
    using namespace NTL;
    using namespace std;
}

namespace gnfs {
    template <typename RowGenerator>
    vector<pair<typename SquareSubsetFinder<RowGenerator>::Index, vec_GF2>> SquareSubsetFinder<RowGenerator>::get() {
        long rows = matrix_.NumRows();
        long cols = rg_.num_cols();
        // If matrix_ doesn't have more rows than columns,
        // we need to generate more rows.
        // But our loop below will generate the (cols+1)th row,
        // so we stop this loop when there's a square matrix.
        while (rows < cols) {
            matrix_.SetDims(rows + 1, cols);
            rows++;
            pair<Index, vec_GF2> new_row = rg_.get();
            indices_.push_back(new_row.first);
            matrix_[rows - 1] = new_row.second;
        }

        // Overall course of events:
        // basis_cursor_ is a bitfield representing which elements
        // of basis_ to add together for the next subset we return.
        // We iterate through all values of basis_cursor_
        // until it reaches 2^(basis.NumRows()),
        // at which point we request a new row from rg_.
        // Then we iterate through the new basis,
        // suppressing returned sets that do not include the new row.
        //
        // This loop is a shoddy equivalent to an infinite generator.
        // Each iteration through the loop produces a candidate
        // that we can return.
        // Either we return it,
        // saving tons of state so we know where we left off,
        // or we continue; and produce a new candidate.
        while (true) {
            basis_cursor_++;
            if (basis_cursor_ == 0 || NumBits(basis_cursor_) >= basis_.NumRows()) {
                // Request a new row for the matrix.
                matrix_.SetDims(rows + 1, cols);
                rows++;
                pair<Index, vec_GF2> new_row = rg_.get();
                indices_.push_back(new_row.first);
                matrix_[rows - 1] = new_row.second;

                // Generate a new basis.
                kernel(basis_, matrix_);

                // Reset the cursor.
                suppress_ = (basis_cursor_ != 0);
                // Skip 0 because returning the empty set is stupid.
                basis_cursor_ = 1;
            }

            // Compute the sum of the indicated rows in the basis.
            vec_GF2 basis_rows_to_sum = bitfield(basis_cursor_);
            basis_rows_to_sum.SetLength(basis_.NumRows());
            vec_GF2 their_sum = basis_rows_to_sum * basis_;
            // Now their_sum is a vector of length rows,
            // indicating which rows are in the square subset
            // that we're about to return.

            // Check suppression.
            if (suppress_ && their_sum[rows - 1] == 0) continue;

            // For each 1 in sum, add the corresponding entry of matrix_
            // to the returned vector.
            vector<pair<Index, vec_GF2>> ret;
            for (int i = 0; i < their_sum.length(); i++) {
                if (their_sum[i] != 0) {
                    Index first = indices_[i];
                    vec_GF2 second = matrix_[i];
                    ret.emplace_back(first, second);
                }
            }

            // Make sure we're not returning the empty vector.
            if (!ret.size()) continue;

            return ret;
        }
    }
}
