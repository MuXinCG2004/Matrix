#ifndef _MATRIX_
#define _MATRIX_
#include <iostream>
template<typename T>
class Matrix
{
    template<typename U>
    friend std::istream & operator>>(std::istream & is, Matrix<U> & rhs);
    template<typename U>
    friend std::ostream & operator<<(std::ostream & os, const Matrix<U> & rhs);
    template<typename U>
    friend Matrix<U> operator*(const U & lhs, const Matrix<U> & rhs);
private:
    int line, row;
    int size;
    T * element;
public:
    Matrix() : line(0), row(0), size(0) {};
    Matrix(int line, int row);
    Matrix(const Matrix<T> & rhs);
    Matrix<T> operator+(const Matrix<T> & rhs);
    Matrix<T> operator*(const Matrix<T> & rhs);
    void operator+=(const Matrix<T> & rhs);
    void operator*=(const Matrix<T> & rhs);
    T determinant();
    Matrix<T> inverse();
    Matrix<T> transpose();
    Matrix<T> operator*(const T & rhs);
    Matrix<T> adjoint();
    ~Matrix();
};

#include "Matrix.cpp"
#endif
