#include "SmallMatrix.hpp"

namespace mtrn2500 {

SmallMatrix::SmallMatrix() {}

SmallMatrix::SmallMatrix(int numRows, int numCols) {}

SmallMatrix::SmallMatrix(int numRows, int numCols, double value) {}

SmallMatrix::SmallMatrix(std::initializer_list<std::initializer_list<double>> const& il)
    : mNumRows(il.size()),
      mNumCols(il.begin() == il.end() ? 0 : il.begin()->size()),
      mIsLargeMatrix(mNumRows * mNumCols >= mSmallSize) {
    if (std::adjacent_find(il.begin(), il.end(), [](auto const& lhs, auto const& rhs) {
            return lhs.size() != rhs.size();
        }) != il.end()) {
        throw std::invalid_argument("Rows have different sizes.");
    }

    if (mIsLargeMatrix) {
        mHeapData.resize(mNumRows);
    }

    int row_index{0};
    for (auto const& row : il) {
        if (mIsLargeMatrix) {
            mHeapData.at(row_index).reserve(mNumCols);
            std::copy(row.begin(), row.end(), mHeapData.at(row_index).begin());
        } else {
            std::transform(row.begin(), row.end(), mStackData.at(row_index).begin(),
                           [](auto const& e) { return e; });
        }
        row_index++;
    }
}

SmallMatrix::SmallMatrix(SmallMatrix const& sm) {}

SmallMatrix::SmallMatrix(SmallMatrix&& sm) {}

SmallMatrix& SmallMatrix::operator=(SmallMatrix const& sm) { return *this; }

SmallMatrix& SmallMatrix::operator=(SmallMatrix&& sm) { return *this; }

SmallMatrix::~SmallMatrix() {}

double& SmallMatrix::operator()(int numRow, int numCol) { return mStackData[0][0]; }

const double& SmallMatrix::operator()(int numRow, int numCol) const { return mStackData[0][0]; }

std::vector<double*> SmallMatrix::row(int numRow) { return {}; }

std::vector<double const*> SmallMatrix::row(int numRow) const { return {}; }

std::vector<double*> SmallMatrix::col(int numCol) { return {}; }

std::vector<double const*> SmallMatrix::col(int numCol) const { return {}; }

std::pair<int, int> SmallMatrix::size() const { return {}; }

bool SmallMatrix::isSmall() const { return false; }

void SmallMatrix::resize(int numRows, int numCols) {}

void SmallMatrix::insertRow(int numRow, std::vector<double> const& row) {}

void SmallMatrix::insertCol(int numCol, std::vector<double> const& col) {}

void SmallMatrix::eraseRow(int numRow) {}

void SmallMatrix::eraseCol(int numCol) {}

bool operator==(SmallMatrix const& lhs, SmallMatrix const& rhs) { return false; }

bool operator!=(SmallMatrix const& lhs, SmallMatrix const& rhs) { return false; }

SmallMatrix operator+(SmallMatrix const& lhs, SmallMatrix const& rhs) { return {}; }

SmallMatrix operator-(SmallMatrix const& lhs, SmallMatrix const& rhs) { return {}; }

SmallMatrix operator*(SmallMatrix const& lhs, SmallMatrix const& rhs) { return {}; }

SmallMatrix operator*(double s, SmallMatrix const& sm) { return {}; }

SmallMatrix operator*(SmallMatrix const& sm, double s) { return {}; }

SmallMatrix& SmallMatrix::operator+=(SmallMatrix const& sm) { return *this; }

SmallMatrix& SmallMatrix::operator-=(SmallMatrix const& sm) { return *this; }

SmallMatrix& SmallMatrix::operator*=(SmallMatrix const& sm) { return *this; }

SmallMatrix& SmallMatrix::operator*=(double s) { return *this; }

SmallMatrix transpose(SmallMatrix const& sm) { return {}; }

std::ostream& operator<<(std::ostream& os, SmallMatrix const& sm) { return os; }

}  // namespace mtrn2500