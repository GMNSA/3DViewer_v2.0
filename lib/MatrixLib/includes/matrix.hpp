#ifndef SRC_S21_MATRIX_HPP_
#define SRC_S21_MATRIX_HPP_

#include <cmath>
#include <iostream>
using namespace std;

class S21Matrix {
public:
  S21Matrix() { this->AllocateMemory(3, 3); };
  S21Matrix(int rows, int columns);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();
  bool EqMatrix(const S21Matrix &other) const;
  int GetRows() const;
  int GetCols() const;
  S21Matrix &operator=(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;
  bool operator==(const S21Matrix &other) const;
  bool operator!=(const S21Matrix &other) const;
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(double number);
  S21Matrix operator*(const S21Matrix &other);
  double& operator()(int rows, int columns) const;
  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(const double &right);
  void ChangeSize(int rows_, int cols_);
private:
  int rows_, cols_;
  double **matrix_;
  void AllocateMemory(int rows, int columns);
  void CopyMatrix(S21Matrix &change, const S21Matrix &other);
  double CalculationDeterminant(const S21Matrix &a) const;
  double FinalMatrixDeterminant(const S21Matrix &a) const;
  void SubMatrix(S21Matrix &result, const S21Matrix &other);
  void SumMatrix(S21Matrix &result, const S21Matrix &other);
  bool EqDouble(double num1, double num2) const;
  bool SizeEqMatrix(const S21Matrix &other) const;
  void NewMatrixDeterminant(const S21Matrix &a, const S21Matrix &new_matrix,
                            int number_column, int number_row) const;
};

#endif // SRC_S21_MATRIX_HPP_