#include "s21_matrix_oop.h"

#include <cmath>
#include <cstring>
#include <iostream>

S21Matrix ::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  MemoryAlloc();
}

S21Matrix ::S21Matrix(const int rows, const int cols)
    : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) throw std::logic_error("error invalid size");
  MemoryAlloc();
}

// конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  MemoryAlloc();
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// конструктор переноса
S21Matrix ::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix ::~S21Matrix() { MemoryFree(); }

// оператор присваивания копированием
S21Matrix& S21Matrix ::operator=(const S21Matrix& other) {
  if (this == &other) return *this;
  this->MemoryFree();
  cols_ = other.cols_;
  rows_ = other.rows_;
  MemoryAlloc();
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix& S21Matrix ::operator=(S21Matrix&& other) noexcept {
  if (this == &other) return *this;
  this->MemoryFree();
  cols_ = other.cols_;
  rows_ = other.rows_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;

  return *this;
}

void S21Matrix ::MemoryAlloc() {
  matrix_ = new double*[rows_]();
  matrix_[0] = new double[rows_ * cols_]();
  for (auto i = 1; i != rows_; ++i) matrix_[i] = matrix_[i - 1] + cols_;
}

void S21Matrix ::MemoryFree() {
  if (matrix_ && matrix_[0]) {
    delete[] matrix_[0];
    delete[] matrix_;
    cols_ = 0;
    rows_ = 0;
  }
}

// Геттеры
int S21Matrix ::GetRows() const { return rows_; }
int S21Matrix ::GetCols() const { return cols_; }

// Сеттеры
void S21Matrix ::SetRows(const int rows) {
  if (rows < 1) throw std::logic_error("error invalid size");
  if (rows != rows_) {
    S21Matrix temp(rows, cols_);
    for (int i = 0; i < rows_ && i < temp.rows_; i++) {
      for (int j = 0; j < cols_ && j < temp.cols_; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }

    *this = std::move(temp);
  }
}

void S21Matrix ::SetCols(const int cols) {
  if (cols < 1) throw std::logic_error("error invalid size");
  if (cols != cols_) {
    S21Matrix temp(rows_, cols);
    for (int i = 0; i < rows_ && i < temp.rows_; i++) {
      for (int j = 0; j < cols_ && j < temp.cols_; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }

    *this = std::move(temp);
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 01E-7) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::PrintMatrix() {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      std ::cout << matrix_[i][j] << "  ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void S21Matrix::InitMatrix() {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = i + j;
    }
  }
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("error invalid size");
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("error invalid size");
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}
void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (rows_ != other.cols_ || cols_ != other.rows_)
    throw std::logic_error("error invalid size");
  S21Matrix Result(rows_, other.cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < other.cols_; j++) {
      for (auto k = 0; k < cols_; k++) {
        Result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(Result);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix Result(rows_, cols_);

  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      Result.matrix_[j][i] = matrix_[i][j];
    }
  }

  return Result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::logic_error("error invalid size");
  S21Matrix Result(rows_, cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      S21Matrix Minor = this->MinorCreate(i + 1, j + 1);
      Result.matrix_[i][j] = Minor.Determinant() * pow(-1, (i + j));
    }
  }

  return Result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) throw std::logic_error("error invalid size");
  double result = 0;
  if (rows_ == 1) return matrix_[0][0];

  double temp = 0;
  int sign = 1;
  for (int j = 0; j < rows_; j++) {
    S21Matrix Minor = this->MinorCreate(1, j + 1);
    if (Minor.rows_ == 2)
      temp = Minor.MinorCalc();
    else
      temp = Minor.Determinant();
    result += matrix_[0][j] * temp * sign;
    sign *= -1;
  }

  return result;
}

S21Matrix S21Matrix::MinorCreate(int rows, int cols) const {
  S21Matrix Minor(rows_ - 1, cols_ - 1);
  rows--;
  cols--;
  auto i_minor = 0;
  for (auto i = 0; i < rows_; i++) {
    auto j_minor = 0;
    for (auto j = 0; j < cols_; j++) {
      if (i != rows && j != cols) {
        Minor.matrix_[i_minor][j_minor] = this->matrix_[i][j];
        j_minor++;
      }
    }
    if (i != rows) i_minor++;
  }
  return Minor;
}

double S21Matrix::MinorCalc() const {
  return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = this->Determinant();
  if (fabs(det - 0) < 01E-7) throw std::logic_error("determinant equal zero");
  S21Matrix Result = this->CalcComplements();
  Result.Transpose();
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      Result.matrix_[i][j] = Result.matrix_[i][j] / det;
    }
  }
  return Result;
}

double& S21Matrix::operator()(const int i, const int j) {
  if (i > rows_ || i < 0 || j > cols_ || j < 0)
    throw std::logic_error("index is outside the matrix");
  return matrix_[i][j];
}
double S21Matrix::operator()(const int i, const int j) const {
  if (i > rows_ || i < 0 || j > cols_ || j < 0)
    throw std::logic_error("index is outside the matrix");
  return matrix_[i][j];
}

S21Matrix& S21Matrix::operator+(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator-(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& operator*(const double num, S21Matrix& M) {
  M.MulNumber(num);
  return M;
}
S21Matrix& operator*(S21Matrix& M, const double num) {
  M.MulNumber(num);
  return M;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}
