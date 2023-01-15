#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H
#include <cstdio>

class S21Matrix {
 public:
  // конструкторы и деструкторы
  S21Matrix();
  S21Matrix(const int rows, const int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  // методы
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // сеттеры и геттеры
  int GetRows() const;
  int GetCols() const;
  void SetRows(const int rows);
  void SetCols(const int cols);

  // технические методы
  void PrintMatrix();
  void InitMatrix();

  // перегрузка операторов
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  S21Matrix& operator+(const S21Matrix& other);
  S21Matrix& operator-(const S21Matrix& other);
  S21Matrix& operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(const int i, const int j);
  double operator()(const int i, const int j) const;

  friend S21Matrix& operator*(const double num, S21Matrix&);
  friend S21Matrix& operator*(S21Matrix&, const double num);

 private:
  int rows_ = 0, cols_ = 0;
  double** matrix_ = nullptr;

  void MemoryAlloc();
  void MemoryFree();

  double MinorCalc() const;
  S21Matrix MinorCreate(int rows, int cols) const;
};

#endif  // S21_MATRIX_OOP_H