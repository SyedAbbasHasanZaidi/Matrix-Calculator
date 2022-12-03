/**
 * @file test_small_matrix.doctest.cpp
 * @author Dan Nguyen (z5206032)
 * @brief Test suite for MTRN2500 2022T3 assignment 1 Small Matrix using doctest.
 */

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#define DOCTEST_CONFIG_REQUIRE_STRINGIFICATION_FOR_ALL_USED_TYPES
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

namespace std {

template <template <typename> class Cont, typename T>
auto operator<<(std::ostream& os, Cont<T> const& cont) -> std::ostream& {
    os << "[";
    for (auto const& i : cont) {
        os << i << " ";
    }
    os << "]";
    return os;
}

template <typename OuterCont, typename InnerCont = typename OuterCont::value_type,
          typename T = typename InnerCont::value_type>
auto operator<<(std::ostream& os, OuterCont const& cont) -> std::ostream& {
    os << "[";
    for (auto const& inner : cont) {
        os << "[";
        for (auto const& i : inner) {
            os << i << " ";
        }
        os << "]";
    }
    os << "]";
    return os;
}

template <typename U, typename V>
auto operator<<(std::ostream& os, std::pair<U, V> const& p) -> std::ostream& {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

}  // namespace std

#include "SmallMatrix.hpp"

constexpr auto small_size = 144;

bool is_it_small(int num_rows, int num_cols) { return num_rows * num_cols < small_size; }

TEST_CASE("SmallMatrix& inverse()") {
    auto m1 = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SUBCASE("0 x 0") {
        auto m = mtrn2500::SmallMatrix();
        CHECK(m.size() == std::make_pair(0, 0));
        CHECK(m.isSmall() == true);
    }

    SUBCASE("2 x 2") {
        m1 = mtrn2500::SmallMatrix({{1, 2}, {3, 4}});
        e = mtrn2500::SmallMatrix({{-2, 1}, {3/2, -1/2}});
    }

}