#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>

namespace {
    namespace mp = boost::multiprecision;
}

int main(int argc, char** argv) {
    mp::cpp_int n;  // number to factor
    std::cin >> n;

    // do the thing

    std::cout << "something";
}
