/**
 * @file test_small_matrix.catch2.cpp
 * @author Dan Nguyen (z5206032)
 * @brief Test suite for MTRN2500 2022T3 assignment 1 Small Matrix using catch2.
 */

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#define CATCH_CONFIG_MAIN
#include "SmallMatrix.hpp"
#include "catch.hpp"

constexpr auto small_size = 144;

bool is_it_small(int num_rows, int num_cols) { return num_rows * num_cols < small_size; }

TEST_CASE("SmallMatrix()", "[progress-check]") {
    SECTION("0 x 0") {
        auto m = mtrn2500::SmallMatrix();
        CHECK(m.size() == std::make_pair(0, 0));
        CHECK(m.isSmall() == true);
    }
}

TEST_CASE("SmallMatrix(int, int)", "[progress-check]") {
    auto num_rows = 0;
    auto num_cols = 0;

    SECTION("0 x 0") {
        num_rows = 0;
        num_cols = 0;
        auto m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK(m.isSmall() == true);
        CHECK(m.size() == std::make_pair(num_rows, num_cols));
    }

    SECTION("6 x 5") {
        num_rows = 6;
        num_cols = 5;
        auto m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK(m.isSmall() == true);
        CHECK(m.size() == std::make_pair(num_rows, num_cols));
        for (int i = 0; i < m.size().first; i++) {
            for (int j = 0; j < m.size().second; j++) {
                CHECK(m(i, j) == Approx(0.0));
            }
        }
    }

    SECTION("12 x 12") {
        num_rows = 12;
        num_cols = 12;
        auto m = mtrn2500::SmallMatrix(num_rows, num_cols);
        REQUIRE(m.isSmall() == false);
        CHECK(m.size() == std::make_pair(num_rows, num_cols));
        for (int i = 0; i < m.size().first; i++) {
            for (int j = 0; j < m.size().second; j++) {
                CHECK(m(i, j) == Approx(0.0));
            }
        }
    }

    SECTION("5 x 29") {
        num_rows = 5;
        num_cols = 29;
        auto m = mtrn2500::SmallMatrix(num_rows, num_cols);
        REQUIRE(m.isSmall() == false);
        CHECK(m.size() == std::make_pair(num_rows, num_cols));
        for (int i = 0; i < m.size().first; i++) {
            for (int j = 0; j < m.size().second; j++) {
                CHECK(m(i, j) == Approx(0.0));
            }
        }
    }
}

TEST_CASE("SmallMatrix(int, int, double)", "[progress-check]") {
    auto num_rows = 0;
    auto num_cols = 0;
    auto value = 0.0;

    SECTION("0 x 0, 42.2") {
        num_rows = 0;
        num_cols = 0;
        value = 42.2;
        auto m = mtrn2500::SmallMatrix(num_rows, num_cols, value);
        CHECK(m.isSmall() == true);
        CHECK(m.size() == std::make_pair(num_rows, num_cols));
    }

    SECTION("6 x 5, -0.42") {
        num_rows = 6;
        num_cols = 5;
        value = -0.42;
        auto m = mtrn2500::SmallMatrix(num_rows, num_cols, value);
        CHECK(m.isSmall() == true);
        CHECK(m.size() == std::make_pair(num_rows, num_cols));
        for (int i = 0; i < m.size().first; i++) {
            for (int j = 0; j < m.size().second; j++) {
                CHECK(m(i, j) == Approx(value));
            }
        }
    }

    SECTION("12 x 12, 19.21") {
        num_rows = 12;
        num_cols = 12;
        value = -19.21;
        auto m = mtrn2500::SmallMatrix(num_rows, num_cols, value);
        REQUIRE(m.isSmall() == false);
        CHECK(m.size() == std::make_pair(num_rows, num_cols));
        for (int i = 0; i < m.size().first; i++) {
            for (int j = 0; j < m.size().second; j++) {
                CHECK(m(i, j) == Approx(value));
            }
        }
    }

    SECTION("5 x 29, 19.21") {
        num_rows = 5;
        num_cols = 29;
        value = -19.21;
        auto m = mtrn2500::SmallMatrix(num_rows, num_cols, value);
        REQUIRE(m.isSmall() == false);
        CHECK(m.size() == std::make_pair(num_rows, num_cols));
        for (int i = 0; i < m.size().first; i++) {
            for (int j = 0; j < m.size().second; j++) {
                CHECK(m(i, j) == Approx(value));
            }
        }
    }
}

TEST_CASE("SmallMatrix(std::initializer_list<std::initializer_list<double>> const&)",
          "[progress-check]") {
    SECTION("0 x 0") {
        auto m = mtrn2500::SmallMatrix({});
        CHECK(m.isSmall() == true);
        CHECK(m.size() == std::make_pair(0, 0));
    }

    SECTION("3 x 3") {
        auto m = mtrn2500::SmallMatrix({
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
        });
        CHECK(m.isSmall() == true);
        CHECK(m.size() == std::make_pair(3, 3));
        int count = 1;
        for (int i = 0; i < m.size().first; i++) {
            for (int j = 0; j < m.size().second; j++) {
                CHECK(m(i, j) == Approx(count++));
            }
        }
    }

    SECTION("5 x 6, malformed row @ 1") {
        CHECK_THROWS_AS(mtrn2500::SmallMatrix({
                            {1, 2, 3, 4, 5, 6},
                            {1, 2, 3, 4, 5, 6, 7},
                            {1, 2, 3, 4, 5, 6},
                            {1, 2, 3, 4, 5, 6},
                            {1, 2, 3, 4, 5, 6},
                        }),
                        std::invalid_argument);
    }

    SECTION("5 x 7, malformed row @ 4") {
        CHECK_THROWS_AS(mtrn2500::SmallMatrix({
                            {1, 2, 3, 4, 5, 6},
                            {1, 2, 3, 4, 5, 6},
                            {1, 2, 3, 4, 5, 6},
                            {1, 2, 3, 4, 5, 6},
                            {1, 2, 3, 4, 5},
                        }),
                        std::invalid_argument);
    }

    SECTION("12 x 12") {
        auto m = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        REQUIRE(m.isSmall() == false);
        CHECK(m.size() == std::make_pair(12, 12));
        for (int i = 0; i < m.size().first; i++) {
            for (int j = 0; j < m.size().second; j++) {
                CHECK(m(i, j) == Approx(j));
            }
        }
    }

    SECTION("12 x 12, malformed row @ 2") {
        CHECK_THROWS_AS(mtrn2500::SmallMatrix({
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                        }),
                        std::invalid_argument);
    }

    SECTION("11 x 13, malformed row @ 11") {
        CHECK_THROWS_AS(mtrn2500::SmallMatrix({
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
                        }),
                        std::invalid_argument);
    }
}

TEST_CASE("SmallMatrix(SmallMatrix const&)", "[progress-check]") {
    SECTION("3 x 3") {
        auto m1 = mtrn2500::SmallMatrix({
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
        });
        {
            REQUIRE(m1.isSmall() == true);
            REQUIRE(m1.size() == std::make_pair(3, 3));
            int count = 1;
            for (int i = 0; i < m1.size().first; i++) {
                for (int j = 0; j < m1.size().second; j++) {
                    REQUIRE(m1(i, j) == Approx(count++));
                }
            }
        }
        auto m2 = m1;
        {
            CHECK(m2.isSmall() == m1.isSmall());
            CHECK(m2.size() == m1.size());
            CHECK(m2 == m1);
        }
    }

    SECTION("12 x 12") {
        auto m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        {
            REQUIRE(m1.isSmall() == false);
            REQUIRE(m1.size() == std::make_pair(12, 12));
            for (int i = 0; i < m1.size().first; i++) {
                for (int j = 0; j < m1.size().second; j++) {
                    REQUIRE(m1(i, j) == Approx(j));
                }
            }
        }
        auto m2 = m1;
        {
            CHECK(m2.isSmall() == m1.isSmall());
            CHECK(m2.size() == m1.size());
            CHECK(m2 == m1);
        }
    }
}

TEST_CASE("SmallMatrix(SmallMatrix&&)", "[progress-check]") {
    SECTION("3 x 3") {
        auto m1 = mtrn2500::SmallMatrix({
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
        });
        {
            REQUIRE(m1.isSmall() == true);
            REQUIRE(m1.size() == std::make_pair(3, 3));
            int count = 1;
            for (int i = 0; i < m1.size().first; i++) {
                for (int j = 0; j < m1.size().second; j++) {
                    REQUIRE(m1(i, j) == Approx(count++));
                }
            }
        }
        auto m2 = std::move(m1);
        {
            CHECK(m2.isSmall() == true);
            CHECK(m2.size() == std::make_pair(3, 3));
            int count = 1;
            for (int i = 0; i < m2.size().first; i++) {
                for (int j = 0; j < m2.size().second; j++) {
                    CHECK(m2(i, j) == Approx(count++));
                }
            }
        }
    }

    SECTION("12 x 12") {
        auto m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        {
            REQUIRE(m1.isSmall() == false);
            REQUIRE(m1.size() == std::make_pair(12, 12));
            for (int i = 0; i < m1.size().first; i++) {
                for (int j = 0; j < m1.size().second; j++) {
                    REQUIRE(m1(i, j) == Approx(j));
                }
            }
        }
        auto m2 = std::move(m1);
        {
            CHECK(m2.isSmall() == false);
            CHECK(m2.size() == std::make_pair(12, 12));
            for (int i = 0; i < m2.size().first; i++) {
                for (int j = 0; j < m2.size().second; j++) {
                    CHECK(m2(i, j) == Approx(j));
                }
            }
        }
    }
}

TEST_CASE("SmallMatrix& operator=(SmallMatrix const&)", "[progress-check]") {
    auto m2 = mtrn2500::SmallMatrix();

    SECTION("3 x 3") {
        auto m1 = mtrn2500::SmallMatrix({
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
        });
        {
            REQUIRE(m1.isSmall() == true);
            REQUIRE(m1.size() == std::make_pair(3, 3));
            int count = 1;
            for (int i = 0; i < m1.size().first; i++) {
                for (int j = 0; j < m1.size().second; j++) {
                    REQUIRE(m1(i, j) == Approx(count++));
                }
            }
        }
        m2 = m1;
        {
            CHECK(m2.isSmall() == m1.isSmall());
            CHECK(m2.size() == m1.size());
            CHECK(m2 == m1);
        }
    }

    SECTION("12 x 12") {
        auto m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        {
            REQUIRE(m1.isSmall() == false);
            REQUIRE(m1.size() == std::make_pair(12, 12));
            for (int i = 0; i < m1.size().first; i++) {
                for (int j = 0; j < m1.size().second; j++) {
                    REQUIRE(m1(i, j) == Approx(j));
                }
            }
        }
        m2 = m1;
        {
            CHECK(m2.isSmall() == m1.isSmall());
            CHECK(m2.size() == m1.size());
            CHECK(m2 == m1);
        }
    }
}

TEST_CASE("SmallMatrix& operator=(SmallMatrix&&)", "[progress-check]") {
    auto m2 = mtrn2500::SmallMatrix();

    SECTION("3 x 3") {
        auto m1 = mtrn2500::SmallMatrix({
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
        });
        {
            REQUIRE(m1.isSmall() == true);
            REQUIRE(m1.size() == std::make_pair(3, 3));
            int count = 1;
            for (int i = 0; i < m1.size().first; i++) {
                for (int j = 0; j < m1.size().second; j++) {
                    REQUIRE(m1(i, j) == Approx(count++));
                }
            }
        }
        m2 = std::move(m1);
        {
            CHECK(m2.isSmall() == true);
            CHECK(m2.size() == std::make_pair(3, 3));
            int count = 1;
            for (int i = 0; i < m2.size().first; i++) {
                for (int j = 0; j < m2.size().second; j++) {
                    CHECK(m2(i, j) == Approx(count++));
                }
            }
        }
    }

    SECTION("12 x 12") {
        auto m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        {
            REQUIRE(m1.isSmall() == false);
            REQUIRE(m1.size() == std::make_pair(12, 12));
            for (int i = 0; i < m1.size().first; i++) {
                for (int j = 0; j < m1.size().second; j++) {
                    REQUIRE(m1(i, j) == Approx(j));
                }
            }
        }
        m2 = std::move(m1);
        {
            CHECK(m2.isSmall() == false);
            CHECK(m2.size() == std::make_pair(12, 12));
            for (int i = 0; i < m2.size().first; i++) {
                for (int j = 0; j < m2.size().second; j++) {
                    CHECK(m2(i, j) == Approx(j));
                }
            }
        }
    }
}

TEST_CASE("double& operator()(int, int)", "[progress-check]") {
    auto num_rows = 0;
    auto num_cols = 0;
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("2 x 2") {
        num_rows = 2;
        num_cols = 2;
        m = mtrn2500::SmallMatrix(num_rows, num_cols);
        m(0, 0) = 47.8;
        m(0, 1) = 35.87;
        m(1, 0) = 53.5;
        m(1, 1) = 42.9;

        e = mtrn2500::SmallMatrix({
            {47.8, 35.87},
            {53.5, 42.9},
        });
    }

    SECTION("12 x 12") {
        num_rows = 12;
        num_cols = 12;
        m = mtrn2500::SmallMatrix(num_rows, num_cols);
        for (int i{0}; i < num_rows; i++) {
            for (int j{0}; j < num_cols; j++) {
                m(i, j) = j;
            }
        }
        m(0, 0) = 45.6;
        m(0, 1) = 54.6;
        m(1, 0) = 42.1;
        m(1, 1) = 96.3;
        m(4, 3) = 0.0001;
        m(4, 4) = 0.1231;
        m(6, 8) = 75.2521;
        m(11, 7) = 12.32;
        m(11, 11) = 1.000;

        e = mtrn2500::SmallMatrix({
            {45.6, 54.6, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {42.1, 96.3, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 0.0001, 0.1231, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 75.2521, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 12.32, 8, 9, 10, 1.000},
        });
    }

    SECTION("21 x 4, @ (-1, 3, std::out_of_range @ row @ -1") {
        num_rows = 21;
        num_cols = 4;
        m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(-1, 3) = 42.2, std::out_of_range);
        e = m;
    }

    SECTION("21 x 4, @ (21, 3), std::out_of_range @ row @ 21") {
        num_rows = 21;
        num_cols = 4;
        m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(21, 3) = 42.2, std::out_of_range);
        e = m;
    }

    SECTION("21 x 4, @ (16, 4), std::out_of_range @ col @ 4") {
        num_rows = 21;
        num_cols = 4;
        m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(16, 4) = 42.2, std::out_of_range);
        e = m;
    }

    SECTION("21 x 45, @ (-1, 3), std::out_of_range @ row @ -1") {
        num_rows = 21;
        num_cols = 45;
        m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(-1, 3) = 42.2, std::out_of_range);
        e = m;
    }

    SECTION("21 x 45, @ (16, -1), std::out_of_range @ col @ -1") {
        num_rows = 21;
        num_cols = 45;
        m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(16, -1) = 42.2, std::out_of_range);
        e = m;
    }

    CHECK(m == e);
}

TEST_CASE("const double& operator()(int, int) const", "[progress-check]") {
    auto num_rows = 0;
    auto num_cols = 0;

    SECTION("2 x 2") {
        num_rows = 2;
        num_cols = 2;
        auto const m = mtrn2500::SmallMatrix({
            {47.8, 35.87},
            {53.5, 42.9},
        });
        CHECK(m(0, 0) == 47.8);
        CHECK(m(0, 1) == 35.87);
        CHECK(m(1, 0) == 53.5);
        CHECK(m(1, 1) == 42.9);
    }

    SECTION("12 x 12") {
        num_rows = 12;
        num_cols = 12;
        auto const m = mtrn2500::SmallMatrix({
            {45.6, 54.6, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {42.1, 96.3, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 0.0001, 0.1231, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 75.2521, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 12.32, 8, 9, 10, 1.000},
        });
        CHECK(m(0, 0) == 45.6);
        CHECK(m(0, 1) == 54.6);
        CHECK(m(1, 0) == 42.1);
        CHECK(m(1, 1) == 96.3);
        CHECK(m(4, 3) == 0.0001);
        CHECK(m(4, 4) == 0.1231);
        CHECK(m(6, 8) == 75.2521);
        CHECK(m(11, 7) == 12.32);
        CHECK(m(11, 11) == 1.000);
    }

    SECTION("21 x 4, @ (21, 3), std::out_of_range @ row @ 21") {
        num_rows = 21;
        num_cols = 4;
        auto const m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(21, 3), std::out_of_range);
    }

    SECTION("21 x 4, @ (16, -1), std::out_of_range @ col @ -1") {
        num_rows = 21;
        num_cols = 4;
        auto const m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(16, -1), std::out_of_range);
    }

    SECTION("21 x 45, @ (-1, 3), std::out_of_range @ row @ -1") {
        num_rows = 21;
        num_cols = 45;
        auto const m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(-1, 3), std::out_of_range);
    }

    SECTION("21 x 45, @ (21, 3), std::out_of_range @ row @ 21") {
        num_rows = 21;
        num_cols = 45;
        auto const m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(21, 3), std::out_of_range);
    }

    SECTION("21 x 45, @ (16, 45), std::out_of_range @ col @ 45") {
        num_rows = 21;
        num_cols = 45;
        auto const m = mtrn2500::SmallMatrix(num_rows, num_cols);
        CHECK_THROWS_AS(m(16, 45), std::out_of_range);
    }
}

TEST_CASE("std::vector<double*> row(int)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 3, row @ 0") {
        m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        auto actual = m.row(0);
        *actual[0] = 9.9;
        *actual[1] = 9.8;
        *actual[2] = 9.7;
        e = mtrn2500::SmallMatrix({{9.9, 9.8, 9.7}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
    }

    SECTION("3 x 3, row @ 1") {
        m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        auto actual = m.row(1);
        *actual[0] = 9.9;
        *actual[1] = 9.8;
        *actual[2] = 9.7;
        e = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {9.9, 9.8, 9.7}, {7.8, 8.3, 9.1}});
    }

    SECTION("3 x 3, row @ -1, std::out_of_range @ -1") {
        m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        CHECK_THROWS_AS(*m.row(-1)[0] = 1, std::out_of_range);
        e = m;
    }

    SECTION("3 x 3, row @ 3, std::out_of_range @ 3") {
        m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        CHECK_THROWS_AS(*m.row(3)[0] = 1, std::out_of_range);
        e = m;
    }

    SECTION("5 x 29, row @ 4") {
        m = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        });
        auto actual = m.row(4);
        *actual[0] = 3.3;
        *actual[1] = 2.1;
        *actual[2] = 4.3;
        *actual[3] = 6.8;
        *actual[4] = 9.7;
        *actual[14] = 6.4;
        *actual[15] = 0.1;
        *actual[26] = -2.4;
        *actual[27] = -2.3;
        *actual[28] = -12.3;
        e = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {3.3, 2.1, 4.3, 6.8, 9.7, 5,  6,  7,  8,  9,  10, 11,   12,   13,   6.4,
             0.1, 16,  17,  18,  19,  20, 21, 22, 23, 24, 25, -2.4, -2.3, -12.3},
        });
    }

    SECTION("5 x 29, row @ 5, std::out_of_range @ 5") {
        m = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        });
        CHECK_THROWS_AS(*m.row(5)[0] = 1, std::out_of_range);
        e = m;
    }

    CHECK(m == e);
}

TEST_CASE("std::vector<double const*> row(int) const") {
    SECTION("3 x 3, row @ 0") {
        auto const m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        auto const actual = m.row(0);
        auto const expected = std::vector<double>({1.2, 3.2, 4.3});

        REQUIRE(actual.size() == expected.size());  // Doesn't continue the SECTION if it fails.
        for (unsigned i = 0; i < actual.size(); i++) {
            CHECK(*actual[i] == Approx(expected[i]));
        }
    }

    SECTION("3 x 3, row @ 1") {
        auto const m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        auto const actual = m.row(1);
        auto const expected = std::vector<double>({4.6, 5.4, 6.7});

        REQUIRE(actual.size() == expected.size());  // Doesn't continue the SECTION if it fails.
        for (unsigned i = 0; i < actual.size(); i++) {
            CHECK(*actual[i] == Approx(expected[i]));
        }
    }

    SECTION("3 x 3, row @ -1, std::out_of_range @ -1") {
        auto const m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        CHECK_THROWS_AS(m.row(-1), std::out_of_range);
    }

    SECTION("3 x 3, row @ 3, std::out_of_range @ 3") {
        auto const m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        CHECK_THROWS_AS(m.row(3), std::out_of_range);
    }

    SECTION("5 x 29, row @ 4") {
        auto const m = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        });
        auto const actual = m.row(4);
        auto const expected =
            std::vector<double>({0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
                                 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28});

        REQUIRE(actual.size() == expected.size());  // Doesn't continue the SECTION if it fails.
        for (unsigned i = 0; i < actual.size(); i++) {
            CHECK(*actual[i] == Approx(expected[i]));
        }
    }

    SECTION("5 x 29, row @ 5, std::out_of_range @ 5") {
        auto const m = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        });
        CHECK_THROWS_AS(m.row(5), std::out_of_range);
    }
}

TEST_CASE("std::vector<double*> col(int)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 3, col @ 0") {
        m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        auto actual = m.col(0);
        *actual[0] = 9.9;
        *actual[1] = 9.8;
        *actual[2] = 9.7;
        e = mtrn2500::SmallMatrix({{9.9, 3.2, 4.3}, {9.8, 5.4, 6.7}, {9.7, 8.3, 9.1}});
    }

    SECTION("3 x 3, col @ 1") {
        m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        auto actual = m.col(1);
        *actual[0] = 9.9;
        *actual[1] = 9.8;
        *actual[2] = 9.7;
        e = mtrn2500::SmallMatrix({{1.2, 9.9, 4.3}, {4.6, 9.8, 6.7}, {7.8, 9.7, 9.1}});
    }

    SECTION("3 x 3, col @ -1, std::out_of_range @ -1") {
        m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        CHECK_THROWS_AS(*m.col(-1)[0] = 1, std::out_of_range);
        e = m;
    }

    SECTION("3 x 3, col @ 3, std::out_of_range @ 3") {
        m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        CHECK_THROWS_AS(*m.col(3)[0] = 1, std::out_of_range);
        e = m;
    }

    SECTION("5 x 29, col @ 28") {
        m = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        });
        auto actual = m.col(28);
        *actual[0] = 321.2;
        *actual[1] = 689.5;
        *actual[2] = 753.6;
        *actual[3] = 379.2;
        *actual[4] = 593.8;
        e = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,   14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 321.2},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,   14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 689.5},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,   14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 753.6},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,   14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 379.2},
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,   14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 593.8},
        });
    }

    SECTION("5 x 29, col @ 29, std::out_of_range @ 29") {
        m = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        });
        CHECK_THROWS_AS(m.col(29), std::out_of_range);
        e = m;
    }

    CHECK(m == e);
}

TEST_CASE("std::vector<double const*> col(int) const") {
    SECTION("3 x 3, col @ 0") {
        auto const m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        auto const actual = m.col(0);
        auto const expected = std::vector<double>({1.2, 4.6, 7.8});

        REQUIRE(actual.size() == expected.size());  // Doesn't continue the SECTION if it fails.
        for (unsigned i = 0; i < actual.size(); i++) {
            CHECK(*actual[i] == Approx(expected[i]));
        }
    }

    SECTION("3 x 3, col @ 1") {
        auto const m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        auto const actual = m.col(1);
        auto const expected = std::vector<double>({3.2, 5.4, 8.3});

        REQUIRE(actual.size() == expected.size());  // Doesn't continue the SECTION if it fails.
        for (unsigned i = 0; i < actual.size(); i++) {
            CHECK(*actual[i] == Approx(expected[i]));
        }
    }

    SECTION("3 x 3, col @ -1, std::out_of_range @ -1") {
        auto const m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        CHECK_THROWS_AS(m.col(-1), std::out_of_range);
    }

    SECTION("3 x 3, col @ 3, std::out_of_range @ 3") {
        auto const m = mtrn2500::SmallMatrix({{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}});
        CHECK_THROWS_AS(m.col(3), std::out_of_range);
    }

    SECTION("5 x 29, col @ 4") {
        auto const m = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        });
        auto const actual = m.col(4);
        auto const expected = std::vector<double>({4, 4, 4, 4, 4});

        REQUIRE(actual.size() == expected.size());  // Doesn't continue the SECTION if it fails.
        for (unsigned i = 0; i < actual.size(); i++) {
            CHECK(*actual[i] == Approx(expected[i]));
        }
    }

    SECTION("5 x 29, col @ 29, std::out_of_range @ 29") {
        auto const m = mtrn2500::SmallMatrix({
            {0.1, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.2, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.3, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0.4, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        });
        CHECK_THROWS_AS(m.col(29), std::out_of_range);
    }
}

TEST_CASE("std::pair<int, int> size()", "[progress-check]") {
    auto num_rows = 0;
    auto num_cols = 0;

    SECTION("0 x 0") {
        num_rows = 0;
        num_cols = 0;
    }

    SECTION("12 x 1") {
        num_rows = 12;
        num_cols = 1;
    }

    SECTION("42 x 42") {
        num_rows = 42;
        num_cols = 42;
    }

    auto const m = mtrn2500::SmallMatrix(num_rows, num_cols);
    CHECK(m.size() == std::make_pair(num_rows, num_cols));
}

TEST_CASE("bool isSmall()", "[progress-check]") {
    auto num_rows = 0;
    auto num_cols = 0;

    SECTION("0 x 0") {
        num_rows = 0;
        num_cols = 0;
    }

    SECTION("11 x 13") {
        num_rows = 11;
        num_cols = 13;
    }

    SECTION("12 x 12") {
        num_rows = 12;
        num_cols = 12;
    }

    SECTION("29 x 6") {
        num_rows = 29;
        num_cols = 5;
    }

    auto const m = mtrn2500::SmallMatrix(num_rows, num_cols);
    CHECK(m.isSmall() == is_it_small(num_rows, num_cols));
}

TEST_CASE("void resize(int, int)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 3 -> 0 x 0") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        m.resize(0, 0);
        e = mtrn2500::SmallMatrix();
    }

    SECTION("3 x 3 -> 2 x 3") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        m.resize(2, 3);
        e = mtrn2500::SmallMatrix({{1, 1, 1}, {1, 1, 1}});
    }

    SECTION("3 x 3 -> 6 x 3") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        m.resize(6, 3);
        e = mtrn2500::SmallMatrix(
            {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    }

    SECTION("3 x 3 -> 6 x 6") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        m.resize(6, 6);
        e = mtrn2500::SmallMatrix({{1, 1, 1, 0, 0, 0},
                                   {1, 1, 1, 0, 0, 0},
                                   {1, 1, 1, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0}});
    }

    SECTION("3 x 3, std::out_of_range)") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        CHECK_THROWS_AS(m.resize(-1, 0), std::out_of_range);
        e = m;
    }

    SECTION("3 x 3 -> 12 x 12") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        REQUIRE(m.isSmall() == true);
        m.resize(15, 15);
        REQUIRE(m.isSmall() == false);
        e = mtrn2500::SmallMatrix({
            {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        });
    }

    SECTION("12 x 12 -> 12 x 12") {
        m = mtrn2500::SmallMatrix(12, 12, 1);
        m.resize(12, 12);
        e = mtrn2500::SmallMatrix(12, 12, 1);
    }

    SECTION("11, 16 -> 4, 9") {
        m = mtrn2500::SmallMatrix(11, 16, 1);
        REQUIRE(m.isSmall() == false);
        m.resize(4, 9);
        REQUIRE(m.isSmall() == false);
        e = mtrn2500::SmallMatrix({
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
        });
    }

    SECTION("12 x 12, std::out_of_range)") {
        m = mtrn2500::SmallMatrix({12, 12, 1});
        CHECK_THROWS_AS(m.resize(-1, 13), std::out_of_range);
        e = m;
    }

    CHECK(m == e);
}

TEST_CASE("void insertRow(int, std::vector<double> const&)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 3 -> insert row @ 0") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        m.insertRow(0, {0, 0, 0});
        e = mtrn2500::SmallMatrix({{0, 0, 0}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
    }

    SECTION("3 x 3 -> insert row @ 3") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        m.insertRow(3, {0, 0, 0});
        e = mtrn2500::SmallMatrix({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {0, 0, 0}});
    }

    SECTION("3 x 3 -> insert row @ 3, std::invalid_argument @ 4 cols") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        CHECK_THROWS_AS(m.insertRow(3, {0, 0, 0, 0}), std::invalid_argument);
        e = m;
    }

    SECTION("3 x 3 -> insert row @ 4, std::out_of_range @ 4") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        CHECK_THROWS_AS(m.insertRow(4, {0, 0, 0}), std::out_of_range);
        e = m;
    }

    SECTION("12 x 12 -> insert row @ 12") {
        m = mtrn2500::SmallMatrix(12, 12, 1);
        REQUIRE(m.isSmall() == false);
        m.insertRow(12, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
        REQUIRE(m.isSmall() == false);
        e = mtrn2500::SmallMatrix({
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        });
    }

    SECTION("12 x 12 -> insert row @ 0") {
        m = mtrn2500::SmallMatrix(12, 12, 1);
        m.insertRow(0, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
        e = mtrn2500::SmallMatrix({
            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        });
    }

    SECTION("12 x 12 -> insert row @ 0, std::invalid_argument @ 13 cols") {
        m = mtrn2500::SmallMatrix(12, 12, 1);
        CHECK_THROWS_AS(m.insertRow(0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
                        std::invalid_argument);
        e = m;
    }

    SECTION("12 x 12 -> insert row @ -1, std::out_of_range @ -1") {
        m = mtrn2500::SmallMatrix(12, 12, 1);
        CHECK_THROWS_AS(m.insertRow(-1, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}), std::out_of_range);
        e = m;
    }

    CHECK(m == e);
}

TEST_CASE("void insertCol(int, std::vector<double> const&)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 0 -> insert col @ [0, 1, 2]") {
        m = mtrn2500::SmallMatrix(3, 0);
        m.insertCol(0, {1, 2, 3});
        m.insertCol(1, {4, 5, 6});
        m.insertCol(2, {7, 8, 9});
        e = mtrn2500::SmallMatrix({{1, 4, 7}, {2, 5, 8}, {3, 6, 9}});
    }

    SECTION("3 x 3 -> insert col @ 0") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        m.insertCol(0, {0, 0, 0});
        e = mtrn2500::SmallMatrix({{{0, 1, 1, 1}, {0, 1, 1, 1}, {0, 1, 1, 1}}});
    }

    SECTION("3 x 3 -> insert col @ 3") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        m.insertCol(3, {0, 0, 0});
        e = mtrn2500::SmallMatrix({{1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}});
    }

    SECTION("3 x 3 -> insert col @ 3, std::invalid_argument @ 4 rows") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        CHECK_THROWS_AS(m.insertCol(3, {0, 0, 0, 0}), std::invalid_argument);
        e = m;
    }

    SECTION("3 x 3 -> insert col @ -1, std::out_of_range @ -1") {
        m = mtrn2500::SmallMatrix(3, 3, 1);
        CHECK_THROWS_AS(m.insertCol(-1, {0, 0, 0}), std::out_of_range);
        e = m;
    }

    SECTION("12 x 11 -> insert col @ 0") {
        m = mtrn2500::SmallMatrix(12, 11, 1);
        REQUIRE(m.isSmall() == true);
        m.insertCol(0, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
        REQUIRE(m.isSmall() == false);
        e = mtrn2500::SmallMatrix({
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        });
    }

    SECTION("12 x 12 -> insert col @ 12") {
        m = mtrn2500::SmallMatrix(12, 12, 1);
        REQUIRE(m.isSmall() == false);
        m.insertCol(12, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
        REQUIRE(m.isSmall() == false);
        e = mtrn2500::SmallMatrix({
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        });
    }

    SECTION("12 x 12 -> insert col @ 0") {
        m = mtrn2500::SmallMatrix(12, 12, 1);
        m.insertCol(0, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
        e = mtrn2500::SmallMatrix({
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        });
    }

    SECTION("12 x 12 -> insert col @ 0, std::invalid_argument @ 13 rows") {
        m = mtrn2500::SmallMatrix(12, 12, 1);
        CHECK_THROWS_AS(m.insertCol(0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
                        std::invalid_argument);
        e = m;
    }

    SECTION("12 x 12 -> insert col @ -1, std::out_of_range @ -1") {
        m = mtrn2500::SmallMatrix(12, 12, 1);
        CHECK_THROWS_AS(m.insertCol(-1, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}), std::out_of_range);
        e = m;
    }

    CHECK(m == e);
}

TEST_CASE("void eraseRow(int)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 3 -> erase row @ 0") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.eraseRow(0);
        e = {{4, 5, 6}, {7, 8, 9}};
    }

    SECTION("3 x 3 -> erase row @ 1") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.eraseRow(1);
        e = {{1, 2, 3}, {7, 8, 9}};
    }

    SECTION("3 x 3 -> erase row @ 2") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.eraseRow(2);
        e = {{1, 2, 3}, {4, 5, 6}};
    }

    SECTION("3 x 3 -> erase row @ [0, 1, 2]") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.eraseRow(0);
        m.eraseRow(1);
        m.eraseRow(0);
        e = mtrn2500::SmallMatrix(0, 3);
    }

    SECTION("3 x 3 -> erase row @ -1, std::out_of_range @ -1") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        CHECK_THROWS_AS(m.eraseRow(-1), std::out_of_range);
        e = m;
    }

    SECTION("3 x 3 -> erase row @ 3, std::out_of_range @ 3") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        CHECK_THROWS_AS(m.eraseRow(3), std::out_of_range);
        e = m;
    }

    CHECK(m == e);
}

TEST_CASE("void eraseCol(int)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 3 -> erase col @ 0") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.eraseCol(0);
        e = {{2, 3}, {5, 6}, {8, 9}};
    }

    SECTION("3 x 3 -> erase col @ 1") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.eraseCol(1);
        e = {{1, 3}, {4, 6}, {7, 9}};
    }

    SECTION("3 x 3 -> erase col @ 2") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.eraseCol(2);
        e = {{1, 2}, {4, 5}, {7, 8}};
    }

    SECTION("3 x 3 -> erase col @ [0, 1, 2]") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.eraseCol(0);
        m.eraseCol(1);
        m.eraseCol(0);
        e = mtrn2500::SmallMatrix(3, 0);
    }

    SECTION("3 x 3 -> erase col @ -1, std::out_of_range @ -1") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        CHECK_THROWS_AS(m.eraseCol(-1), std::out_of_range);
        e = m;
    }

    SECTION("3 x 3 -> erase col @ 3, std::out_of_range @ 3") {
        m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        CHECK_THROWS_AS(m.eraseCol(3), std::out_of_range);
        e = m;
    }

    CHECK(m == e);
}

TEST_CASE("friend bool operator==(SmallMatrix const&, SmallMatrix const&)", "[progress-check]") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();
    auto is_same = false;

    SECTION("2 x 4 == 2 x 4, expect false") {
        m = mtrn2500::SmallMatrix({{1, 2, 4, 6}, {5, -2, 5, 6}});
        e = mtrn2500::SmallMatrix({{1, 2, 4, 12}, {5, -2, 92, 6}});
        is_same = false;
    }

    SECTION("2 x 4 == 2 x 3, expect false") {
        m = mtrn2500::SmallMatrix({{1, 2, 4, 6}, {5, -2, 5, 8}});
        e = mtrn2500::SmallMatrix({{1, 2, 4}, {5, -2, 5}});
        is_same = false;
    }

    SECTION("16 x 16 == 16 x 16, expect true") {
        m = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        });
        e = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        });
        is_same = true;
    }

    CHECK((m == e) == is_same);
}

TEST_CASE("friend bool operator!=(SmallMatrix const&, SmallMatrix const&)", "[progress-check]") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();
    auto is_diff = false;

    SECTION("2 x 4 != 2 x 4, expect true") {
        m = mtrn2500::SmallMatrix({{1, 2, 4, 6}, {5, -2, 5, 6}});
        e = mtrn2500::SmallMatrix({{1, 2, 4, 12}, {5, -2, 92, 6}});
        is_diff = true;
    }

    SECTION("2 x 4 != 2 x 3, expect true") {
        m = mtrn2500::SmallMatrix({{1, 2, 4, 6}, {5, -2, 5, 8}});
        e = mtrn2500::SmallMatrix({{1, 2, 4}, {5, -2, 5}});
        is_diff = true;
    }

    SECTION("16 x 16 != 16 x 16, expect true") {
        m = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        });
        e = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 321.42, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        });
        is_diff = true;
    }

    CHECK((m != e) == is_diff);
}

TEST_CASE("friend SmallMatrix operator+(SmallMatrix const&, SmallMatrix const&)") {
    auto m1 = mtrn2500::SmallMatrix();
    auto m2 = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("2 x 2") {
        m1 = mtrn2500::SmallMatrix({{3, 5}, {1, 8}});
        m2 = mtrn2500::SmallMatrix({{6, 2}, {7, 12}});
        e = mtrn2500::SmallMatrix({{9, 7}, {8, 20}});
    }

    SECTION("2 x 2, std::invalid_argument @ 2 x 1") {
        m1 = mtrn2500::SmallMatrix(2, 2, 21);
        m2 = mtrn2500::SmallMatrix(2, 1, 1);
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = {};
        m2 = {};
        e = {};
    }

    SECTION("2 x 2, std::invalid_argument @ 7 x 2") {
        m1 = mtrn2500::SmallMatrix(2, 2, 1);
        m2 = mtrn2500::SmallMatrix(7, 2, 1);
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = {};
        m2 = {};
        e = {};
    }

    SECTION("12 x 12") {
        m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {8, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        m2 = mtrn2500::SmallMatrix({
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
        });
        e = mtrn2500::SmallMatrix({
            {1, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {2, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {3, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {4, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {5, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {6, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {7, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {8, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {9, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {10, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {11, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {12, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
        });
    }

    CHECK(m1 + m2 == e);
}

TEST_CASE("friend SmallMatrix operator-(SmallMatrix const&, SmallMatrix const&)") {
    auto m1 = mtrn2500::SmallMatrix();
    auto m2 = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("2 x 2") {
        m1 = mtrn2500::SmallMatrix({{3, 5}, {1, 8}});
        m2 = mtrn2500::SmallMatrix({{6, 2}, {7, 12}});
        e = mtrn2500::SmallMatrix({{-3, 3}, {-6, -4}});
    }

    SECTION("2 x 2, std::invalid_argument @ 2 x 1") {
        m1 = mtrn2500::SmallMatrix(2, 2, 21);
        m2 = mtrn2500::SmallMatrix(2, 1, 1);
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = {};
        m2 = {};
        e = {};
    }

    SECTION("2 x 2, std::invalid_argument @ 7 x 2") {
        m1 = mtrn2500::SmallMatrix(2, 2, 1);
        m2 = mtrn2500::SmallMatrix(7, 2, 1);
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = {};
        m2 = {};
        e = {};
    }

    SECTION("12 x 12") {
        m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {8, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        m2 = mtrn2500::SmallMatrix({
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
        });
        e = mtrn2500::SmallMatrix({
            {-1, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {1, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {2, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {3, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {4, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {5, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {6, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {7, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {8, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {9, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {10, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
        });
    }

    CHECK(m1 - m2 == e);
}

TEST_CASE("friend SmallMatrix operator*(SmallMatrix const&, SmallMatrix const&)") {
    auto m1 = mtrn2500::SmallMatrix();
    auto m2 = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 3 * 3 x 2") {
        m1 = mtrn2500::SmallMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        m2 = mtrn2500::SmallMatrix({{2, 3}, {4, 5}, {6, 7}});
        e = mtrn2500::SmallMatrix({{28, 34}, {64, 79}, {100, 124}});
    }

    SECTION("1 x 3, std::invalid_argument @ 1 x 1") {
        m1 = mtrn2500::SmallMatrix({{1, 2, 3}});
        m2 = mtrn2500::SmallMatrix({{2}});
        CHECK_THROWS_AS(m1 * m2, std::invalid_argument);
        m1 = mtrn2500::SmallMatrix();
        m2 = mtrn2500::SmallMatrix();
        e = mtrn2500::SmallMatrix();
    }

    SECTION("11 x 12 * 12 x 11") {
        m1 = mtrn2500::SmallMatrix(11, 12, 3);
        m2 = mtrn2500::SmallMatrix(12, 11, 2);
        e = mtrn2500::SmallMatrix(11, 11, 72);
    }

    auto a = m1 * m2;
    CHECK(a.isSmall() == e.isSmall());
    CHECK(a == e);
}

TEST_CASE("friend SmallMatrix operator*(double, SmallMatrix const&)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();
    double d;

    SECTION("-2.1 * 2 x 5") {
        d = -2.1;
        m = mtrn2500::SmallMatrix({{3, 5, 6, 2, 1}, {1, 4, 7, 1, 8}});
        e = mtrn2500::SmallMatrix(
            {{-6.3, -10.5, -12.6, -4.2, -2.1}, {-2.1, -8.4, -14.7, -2.1, -16.8}});
    }

    SECTION("2.3 * 12 x 12") {
        d = 2.3;
        m = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {8, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        e = mtrn2500::SmallMatrix({
            {0, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {2.3, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {4.6, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {6.9, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {9.2, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {11.5, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {13.8, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {16.1, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {18.4, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {20.7, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {23, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {25.3, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
        });
    }

    CHECK(d * m == e);
}

TEST_CASE("friend SmallMatrix operator*(SmallMatrix const&, double)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();
    double d;

    SECTION("2 x 5 * -2.1") {
        d = -2.1;
        m = mtrn2500::SmallMatrix({{3, 5, 6, 2, 1}, {1, 4, 7, 1, 8}});
        e = mtrn2500::SmallMatrix(
            {{-6.3, -10.5, -12.6, -4.2, -2.1}, {-2.1, -8.4, -14.7, -2.1, -16.8}});
    }

    SECTION("12 x 12 * 2.3") {
        d = 2.3;
        m = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {8, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        e = mtrn2500::SmallMatrix({
            {0, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {2.3, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {4.6, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {6.9, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {9.2, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {11.5, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {13.8, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {16.1, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {18.4, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {20.7, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {23, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {25.3, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
        });
    }

    CHECK(m * d == e);
}

TEST_CASE("SmallMatrix& operator+=(SmallMatrix const&)") {
    auto m1 = mtrn2500::SmallMatrix();
    auto m2 = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("2 x 2") {
        m1 = mtrn2500::SmallMatrix({{3, 5}, {1, 8}});
        m2 = mtrn2500::SmallMatrix({{6, 2}, {7, 12}});
        e = mtrn2500::SmallMatrix({{9, 7}, {8, 20}});
    }

    SECTION("2 x 2, std::invalid_argument @ 2 x 1") {
        m1 = mtrn2500::SmallMatrix(2, 2, 21);
        m2 = mtrn2500::SmallMatrix(2, 1, 1);
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = {};
        m2 = {};
        e = {};
    }

    SECTION("2 x 2, std::invalid_argument @ 7 x 2") {
        m1 = mtrn2500::SmallMatrix(2, 2, 1);
        m2 = mtrn2500::SmallMatrix(7, 2, 1);
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = {};
        m2 = {};
        e = {};
    }

    SECTION("12 x 12") {
        m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {8, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        m2 = mtrn2500::SmallMatrix({
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
        });
        e = mtrn2500::SmallMatrix({
            {1, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {2, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {3, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {4, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {5, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {6, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {7, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {8, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {9, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {10, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {11, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
            {12, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23},
        });
    }

    SECTION("16 x 16, std::invalid_argument @ 16 x 17") {
        m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        });
        m2 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
        });
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = mtrn2500::SmallMatrix();
        m2 = mtrn2500::SmallMatrix();
        e = mtrn2500::SmallMatrix();
    }

    m1 += m2;
    CHECK(m1 == e);
}

TEST_CASE("SmallMatrix& operator-=(SmallMatrix const&)") {
    auto m1 = mtrn2500::SmallMatrix();
    auto m2 = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("1 x 1") {
        m1 = mtrn2500::SmallMatrix(1, 1, 42);
        m2 = mtrn2500::SmallMatrix(1, 1, 56);
        e = mtrn2500::SmallMatrix(1, 1, -14);
    }

    SECTION("2 x 2") {
        m1 = mtrn2500::SmallMatrix({{3, 5}, {1, 8}});
        m2 = mtrn2500::SmallMatrix({{6, 2}, {7, 12}});
        e = mtrn2500::SmallMatrix({{-3, 3}, {-6, -4}});
    }

    SECTION("2 x 2, std::invalid_argument @ 2 x 1") {
        m1 = mtrn2500::SmallMatrix(2, 2, 21);
        m2 = mtrn2500::SmallMatrix(2, 1, 1);
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = {};
        m2 = {};
        e = {};
    }

    SECTION("2 x 2, std::invalid_argument @ 7 x 2") {
        m1 = mtrn2500::SmallMatrix(2, 2, 1);
        m2 = mtrn2500::SmallMatrix(7, 2, 1);
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = {};
        m2 = {};
        e = {};
    }

    SECTION("12 x 12") {
        m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {8, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        m2 = mtrn2500::SmallMatrix({
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
            {1, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12},
        });
        e = mtrn2500::SmallMatrix({
            {-1, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {1, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {2, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {3, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {4, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {5, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {6, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {7, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {8, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {9, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
            {10, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1},
        });
    }

    SECTION("16 x 16, std::invalid_argument @ 16 x 17") {
        m1 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        });
        m2 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
        });
        CHECK_THROWS_AS(m1 + m2, std::invalid_argument);
        m1 = mtrn2500::SmallMatrix();
        m2 = mtrn2500::SmallMatrix();
        e = mtrn2500::SmallMatrix();
    }

    m1 -= m2;
    CHECK(m1 == e);
}

TEST_CASE("SmallMatrix& operator*=(SmallMatrix const&)") {
    auto m1 = mtrn2500::SmallMatrix();
    auto m2 = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 3 * 3 x 2") {
        m1 = mtrn2500::SmallMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        m2 = mtrn2500::SmallMatrix({{2, 3}, {4, 5}, {6, 7}});
        e = mtrn2500::SmallMatrix({{28, 34}, {64, 79}, {100, 124}});
    }

    SECTION("1 x 3, std::invalid_argument @ 1 x 1") {
        m1 = mtrn2500::SmallMatrix({{1, 2, 3}});
        m2 = mtrn2500::SmallMatrix({{2}});
        CHECK_THROWS_AS(m1 * m2, std::invalid_argument);
        m1 = mtrn2500::SmallMatrix();
        m2 = mtrn2500::SmallMatrix();
        e = mtrn2500::SmallMatrix();
    }

    SECTION("11 x 12 * 12 x 11") {
        m1 = mtrn2500::SmallMatrix(11, 12, 3);
        m2 = mtrn2500::SmallMatrix(12, 11, 2);
        e = mtrn2500::SmallMatrix(11, 11, 72);
    }

    m1 *= m2;
    CHECK(m1.isSmall() == e.isSmall());
    CHECK(m1 == e);
}

TEST_CASE("SmallMatrix& operator*=(double)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();
    double d;

    SECTION("2 x 5 *= -2.1") {
        d = -2.1;
        m = mtrn2500::SmallMatrix({{3, 5, 6, 2, 1}, {1, 4, 7, 1, 8}});
        e = mtrn2500::SmallMatrix(
            {{-6.3, -10.5, -12.6, -4.2, -2.1}, {-2.1, -8.4, -14.7, -2.1, -16.8}});
    }

    SECTION("12 x 12 *= 2.3") {
        d = 2.3;
        m = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {8, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
        e = mtrn2500::SmallMatrix({
            {0, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {2.3, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {4.6, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {6.9, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {9.2, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {11.5, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {13.8, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {16.1, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {18.4, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {20.7, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {23, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
            {25.3, 2.3, 4.6, 6.9, 9.2, 11.5, 13.8, 16.1, 18.4, 20.7, 23, 25.3},
        });
    }

    m *= d;
    CHECK(m == e);
}

TEST_CASE("friend SmallMatrix transpose(SmallMatrix const&)") {
    auto m = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    SECTION("3 x 4 T 4 x 3") {
        m = {{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}};
        e = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {4, 7, 10}};
    }

    SECTION("11 x 16 T 16 x 11") {
        m = {
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
            {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        };
        e = {
            {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2},
            {1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2},
            {2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2},
            {3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2},
            {4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2},
            {5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2},
            {6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2},
            {7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2},
            {8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2},
            {9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2},
            {10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2},
            {11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2},
            {12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2},
            {13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2},
            {14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2},
            {15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2},
        };
    }

    auto a = mtrn2500::transpose(m);
    CHECK(a == e);
}

TEST_CASE("friend std::ostream& operator<<(std::ostream&, SmallMatrix const&)") {
    auto m = mtrn2500::SmallMatrix();
    auto s = std::string();

    SECTION("0 x 0") {
        m = {};
        s = "[\n]\n";
    }

    SECTION("3 x 3") {
        m = {{1.2, 3.2, 4.3}, {4.6, 5.4, 6.7}, {7.8, 8.3, 9.1}};
        s = "[\n"
            "  [ 1.2 3.2 4.3 ]\n"
            "  [ 4.6 5.4 6.7 ]\n"
            "  [ 7.8 8.3 9.1 ]\n"
            "]\n";
    }

    SECTION("16 x 16") {
        m = {
            {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2},
            {1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2},
            {2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2},
            {3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2, 3.2},
            {4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2},
            {5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2, 5.2},
            {6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2, 6.2},
            {7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2, 7.2},
            {8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2, 8.2},
            {9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2},
            {10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2, 10.2},
            {11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2, 11.2},
            {12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2},
            {13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2},
            {14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2, 14.2},
            {15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2, 15.2},
        };
        s = "[\n"
            "  [ 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 ]\n"
            "  [ 1.2 1.2 1.2 1.2 1.2 1.2 1.2 1.2 1.2 1.2 1.2 ]\n"
            "  [ 2.2 2.2 2.2 2.2 2.2 2.2 2.2 2.2 2.2 2.2 2.2 ]\n"
            "  [ 3.2 3.2 3.2 3.2 3.2 3.2 3.2 3.2 3.2 3.2 3.2 ]\n"
            "  [ 4.2 4.2 4.2 4.2 4.2 4.2 4.2 4.2 4.2 4.2 4.2 ]\n"
            "  [ 5.2 5.2 5.2 5.2 5.2 5.2 5.2 5.2 5.2 5.2 5.2 ]\n"
            "  [ 6.2 6.2 6.2 6.2 6.2 6.2 6.2 6.2 6.2 6.2 6.2 ]\n"
            "  [ 7.2 7.2 7.2 7.2 7.2 7.2 7.2 7.2 7.2 7.2 7.2 ]\n"
            "  [ 8.2 8.2 8.2 8.2 8.2 8.2 8.2 8.2 8.2 8.2 8.2 ]\n"
            "  [ 9.2 9.2 9.2 9.2 9.2 9.2 9.2 9.2 9.2 9.2 9.2 ]\n"
            "  [ 10.2 10.2 10.2 10.2 10.2 10.2 10.2 10.2 10.2 10.2 10.2 ]\n"
            "  [ 11.2 11.2 11.2 11.2 11.2 11.2 11.2 11.2 11.2 11.2 11.2 ]\n"
            "  [ 12.2 12.2 12.2 12.2 12.2 12.2 12.2 12.2 12.2 12.2 12.2 ]\n"
            "  [ 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 ]\n"
            "  [ 14.2 14.2 14.2 14.2 14.2 14.2 14.2 14.2 14.2 14.2 14.2 ]\n"
            "  [ 15.2 15.2 15.2 15.2 15.2 15.2 15.2 15.2 15.2 15.2 15.2 ]\n"
            "]\n";
    }

    auto a = std::stringstream();
    a << m;
    CHECK(a.str() == s);
}
