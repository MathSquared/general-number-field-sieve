#include "smooth_pair_finder.h"

#include <NTL/RR.h>

#include "norm_finding.h"
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

    bool SmoothPairFinder::add_cols_modular(long a, long b, vec_GF2& ret) {
        ZZ ammb = a - m_ * b;
        ammb %= n_;

        if (ammb < 0) {
            ammb *= -1;
            ret.append(GF2(1));
        } else {
            ret.append(GF2(0));
        }

        for (const auto& p : cols_modular_) {
            bool divcount = false;
            while (ammb % p == 0) {
                ammb /= p;
                divcount ^= true;
            }
            ret.append(divcount ? GF2(1) : GF2(0));
        }

        return ammb == 1;
    }

    bool SmoothPairFinder::add_cols_algebraic(long a, long b, vec_GF2& ret) {
        ZZ namab = eval_norm(f_, ZZ(a), ZZ(b));

        // Iterate through each prime.
        // For each one, find r first,
        // then set the appropriate entry in the index vector.

        // Here, we'll keep a cursor into cols_algebraic_.
        auto alg_it = cols_algebraic_.cbegin();

        for (const auto& p : cols_modular_) {
            long r = lincon(a, b, p);

            // Get the divcount as before
            bool divcount = false;
            while (namab % p == 0) {
                namab /= p;
                divcount ^= true;
            }
            GF2 to_add = divcount ? GF2(1) : GF2(0);

            // Scroll past algebraic factorbase entries
            // until we find where we want to add this item.
            // Then add it.
            while (alg_it->first != p || alg_it->second != r) {
                ++alg_it;
                ret.append(GF2(0));
            }
            ++alg_it;
            ret.append(to_add);
        }

        // Add the rest of the zeros to the vector that we return.
        while (alg_it != cols_algebraic_.cend()) {
            ++alg_it;
            ret.append(GF2(0));
        }

        return namab == 1;
    }

    bool SmoothPairFinder::add_cols_adleman(long a, long b, NTL::vec_GF2& ret) {
        for (const auto& qs : cols_adleman_) {
            long q = qs.first;
            long s = qs.second;
            long jacobi_top = a - b * s;
            long jacobi = Jacobi(ZZ(jacobi_top % q), ZZ(q));
            ret.append(jacobi == -1 ? GF2(1) : GF2(0));
        }

        return true;
    }

    vec_GF2 SmoothPairFinder::generate_row(long a, long b) {
        vec_GF2 ret;  // if this length != num_cols, invalid
        // we always return ret so we can have the return value optimzn
        // even if ret ends up being invalid

        // Modular factorbase and -1.
        if (!add_cols_modular(a, b, ret)) {
            // ammb is not B-smooth
            // make SURE the length is invalid
            if (ret.length() == num_cols()) ret.append(GF2(0));
            return ret;
        }

        // Algebraic factorbase.
        if (!add_cols_algebraic(a, b, ret)) {
            // namab is not B-smooth
            // make SURE the length is invalid
            if (ret.length() == num_cols()) ret.append(GF2(0));
            return ret;
        }

        // Adleman columns.
        if (!add_cols_adleman(a, b, ret)) {
            // result is wrong
            // make SURE the length is invalid
            if (ret.length() == num_cols()) ret.append(GF2(0));
            return ret;
        }

        return ret;
    }

    std::pair<std::pair<long, long>, vec_GF2> SmoothPairFinder::get() {
        // TODO
        return std::make_pair(std::make_pair(0, 0), vec_GF2(INIT_SIZE, num_cols()));
    }
}
