# MTRN2500 - Assignment 1 (Small Matrix)

It may be useful to have a sense of how difficult the class methods are to each other. This may help you complete the assignment by completing the easier methods first then progressing to the more challenging ones. In some cases, the more challenging methods will have to rely on the easier methods anyways.

## Average Difficulty

To understand how to read the difficulty allocations. If you're aiming for a PS, then you would have only completed the methods in the PS group. Likewise if you're aiming for CR, then you would have only completed the PS and CR group.

### PS

- `SmallMatrix()`
- `SmallMatrix(int, int)`
- `SmallMatrix(int, int, double)`
- `SmallMatrix(SmallMatrix const&)`
- `SmallMatrix(SmallMatrix&&)`
- `SmallMatrix& operator=(SmallMatrix const&)`
- `SmallMatrix& operator=(SmallMatrix&&)`
- `~SmallMatrix()`
- `double& operator()(int, int)`
- `const double& operator()(int, int) const`
- `std::pair<int, int> size()`
- `bool isSmall()`

### CR

- ~~`SmallMatrix(std::initializer_list<std::initializer_list<double>> const&)`~~ (GIVEN)
- `std::vector<double*> row(int)`
- `std::vector<double const*> row(int) const`
- `std::vector<double*> col(int)`
- `std::vector<double const*> col(int) const`
- `friend bool operator==(SmallMatrix const&, SmallMatrix const&)`
- `friend bool operator!=(SmallMatrix const&, SmallMatrix const&)`
- `friend SmallMatrix operator+(SmallMatrix const&, SmallMatrix const&)`
- `friend SmallMatrix operator-(SmallMatrix const&, SmallMatrix const&)`
- `friend SmallMatrix operator*(double, SmallMatrix const&)`
- `friend SmallMatrix operator*(SmallMatrix const&, double)`
- `SmallMatrix& operator+=(SmallMatrix const&)`
- `SmallMatrix& operator-=(SmallMatrix const&)`
- `SmallMatrix& operator*=(double)`

### DN

- `void resize(int, int)`
- `friend SmallMatrix operator*(SmallMatrix const&, SmallMatrix const&)`
- `SmallMatrix& operator*=(SmallMatrix const&)`
- `friend SmallMatrix transpose(SmallMatrix const&)`
- `friend std::ostream& operator<<(std::ostream&, SmallMatrix const&)`

### HD

- `void insertRow(int, std::vector<double> const&)`
- `void insertCol(int, std::vector<double> const&)`
- `void eraseRow(int)`
- `void eraseCol(int)`
