The General Number Field Sieve [WIP]
==============================

This project implements the general number field sieve, the asymptotically-fastest algorithm for factoring large integers.

The algorithm is as described in *Algebraic Number Theory* by Jarvis, *Prime Numbers: A Computational Perspective* by Crandall and Pomerance, and others.

Building
--------

This project depends on Victor Shoup's [NTL](http://www.shoup.net/ntl/index.html) and CMake, and is written in C++11. Build as follows:

    mkdir build
    cd build
    cmake ..
    make -j8
