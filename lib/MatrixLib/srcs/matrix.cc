#include "./matrix.hpp"

S21Matrix::S21Matrix(int rows, int columns) {
  AllocateMemory(rows, columns);
}

S21Matrix::S21Matrix(const S21Matrix &other) { CopyMatrix(*this, other); };

bool S21Matrix::EqDouble(double num1, double num2) const {
  return fabs(num1 - num2) < 1e-6;
}

bool S21Matrix::SizeEqMatrix(const S21Matrix &other) const {
  return cols_ == other.cols_ && rows_ == other.rows_;
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }

void S21Matrix::operator*=(const double &right) { MulNumber(right); }

bool S21Matrix::operator==(const S21Matrix &other) const { return EqMatrix(other); }

bool S21Matrix::operator!=(const S21Matrix &other) const { return !EqMatrix(other); }

void S21Matrix::SubMatrix(const S21Matrix &other) { SubMatrix(*this, other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->~S21Matrix();
  CopyMatrix(*this, other);
  return *this;
}

S21Matrix S21Matrix::operator*(double number) {
  S21Matrix result(*this);
  result.MulNumber(number);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

void S21Matrix::MulNumber(double number) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      matrix_[i][j] *= number;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ == other.rows_) {
    double summ = 0;
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < cols_; k++) {
          summ += matrix_[i][k] * other.matrix_[k][j];
        }
        result(i, j) = summ;
        summ = 0;
      }
    }
    *this = result;
  } else {
    throw std::invalid_argument(
        "the number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}


double& S21Matrix::operator()(int rows, int columns) const {
  if (rows < 0 || rows >= rows_ || columns < 0 || columns >= cols_)
    throw std::invalid_argument("index outside the matrix");
  return matrix_[rows][columns];
}

void S21Matrix::AllocateMemory(int rows, int columns) {
  rows_ = rows, cols_ = columns;
  if (rows_ > 0 && cols_ > 0) {
    if (!(matrix_ = (double **)malloc(rows_ * sizeof(double *))))
      throw std::bad_alloc();
    for (int i = 0; i < rows_; i++)
      if (!(matrix_[i] = (double *)malloc(cols_ * sizeof(double))))
        throw std::bad_alloc();
  } else {
    throw std::invalid_argument("invalid matrix size");
  }
}

S21Matrix::~S21Matrix() {
  if (matrix_ == NULL) return;
  for (int i = 0; i < rows_; i++)
    free(matrix_[i]);
  free(matrix_);
}

void S21Matrix::CopyMatrix(S21Matrix &change, const S21Matrix &other) {
  change.AllocateMemory(other.rows_, other.cols_);
  for (int i = 0; i < change.rows_; i++)
    for (int j = 0; j < change.cols_; j++)
     change.matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  if (&other == this) return;
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.matrix_ = NULL;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++)
    for (int j = 0; j < rows_; j++)
      result.matrix_[i][j] = matrix_[j][i];
  return result;
}

void S21Matrix::SubMatrix(S21Matrix &result, const S21Matrix &other) {
  if (SizeEqMatrix(other)) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
  } else {
    throw std::invalid_argument("different dimension of matrices");
  }
}

void S21Matrix::SumMatrix(const S21Matrix &other) { SumMatrix(*this, other); }

void S21Matrix::SumMatrix(S21Matrix &result, const S21Matrix &other) {
  if (SizeEqMatrix(other)) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
  } else {
    throw std::invalid_argument("different dimension of matrices");
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool result = true;
  if (SizeEqMatrix(other)) {
    for (int i = 0; i < rows_; i++) {
      if (!result)
        break;
      for (int j = 0; j < cols_; j++)
        if (!EqDouble(matrix_[i][j], other.matrix_[i][j])) {
          result = false;
        }
    }
  } else {
    result = false;
  }
  return result;
}

double S21Matrix::Determinant() const{
  double result = 0;
  if (rows_ == cols_) {
    result = CalculationDeterminant(*this);
  } else {
    throw std::invalid_argument("the matrix is not square");
  }
  return result;
}

double S21Matrix::CalculationDeterminant(const S21Matrix &A) const{
  double res = 0;
  if (A.rows_ < 3) {
    res = FinalMatrixDeterminant(A);
  } else {
    int minus = 1;
    S21Matrix new_matrix(A.rows_ - 1, A.rows_ - 1);
    for (int i = 0; i < A.rows_; i++) {
      NewMatrixDeterminant(A, new_matrix, 0, i);
      res += A.matrix_[0][i] * CalculationDeterminant(new_matrix) * minus;
      minus *= -1;
    }
  }
  return res;
}

void S21Matrix::NewMatrixDeterminant(const S21Matrix &A,
                                     const S21Matrix &new_matrix,
                                     int number_column, int number_row) const{
  int pos_row = 0, pos_column = 0;
  for (int i = 0; i < new_matrix.rows_; i++) {
    if (number_column <= i)
      pos_column = 1;
    for (int j = 0; j < new_matrix.cols_; j++) {
      if (number_row <= j)
        pos_row = 1;
      new_matrix.matrix_[i][j] = A.matrix_[i + pos_column][j + pos_row];
    }
    pos_row = 0;
  }
}

double S21Matrix::FinalMatrixDeterminant(const S21Matrix &A) const{
  double result = 0;
  if (A.rows_ == 2) {
    result =
        A.matrix_[0][0] * A.matrix_[1][1] - A.matrix_[0][1] * A.matrix_[1][0];
  } else if (A.rows_ == 1) {
    result = A.matrix_[0][0];
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const{
  S21Matrix result(rows_, rows_);
  if (rows_ == cols_) {
    double res_deter = 0;
    int minus = 1;

    S21Matrix matrix(rows_ - 1, rows_ - 1);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < rows_; j++) {
        NewMatrixDeterminant(*this, matrix, i, j);
        res_deter = matrix.Determinant();
        minus = (i + j) % 2 == 0 ? 1 : -1;
        result.matrix_[i][j] = res_deter * minus;
      }
    }
  } else {
    throw std::invalid_argument("the matrix is not square");
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const{
  double determinant = Determinant();
  S21Matrix result(rows_, cols_);
  if (!EqDouble(determinant, 0)) {
    S21Matrix matrix = CalcComplements();
    result = matrix.Transpose();
    result.MulNumber(1.0 / determinant);
  } else {
    throw std::invalid_argument("the determinant of the matrix is 0");
  }
  return result;
}

void S21Matrix::ChangeSize(int rows_, int cols_) {
  if (rows_ > 0 && cols_ > 0) {
    if (this->rows_ > rows_)
      for (int i = rows_; i < this->rows_; i++)
        free(matrix_[i]);
    this->rows_ = rows_, this->cols_ = cols_;
    if (!(matrix_ = (double **)realloc(matrix_, rows_ * sizeof(double *))))
      throw std::bad_alloc();
    for (int i = 0; i < rows_; i++)
      if (!(matrix_[i] = (double *)realloc(matrix_[i], cols_ * sizeof(double))))
        throw std::bad_alloc();
  } else {
    throw std::invalid_argument("invalid matrix size");
  }
}
