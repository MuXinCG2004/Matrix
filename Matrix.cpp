#include <iostream>
#include <cstring>
#include "Matrix.h"
template<typename T>
Matrix<T>::Matrix(int line, int row)
{
    this->line = line;
    this->row = row;
    this->size = row * line;
    this->element = new T[size];
    std::fill(element, element + size, T());
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs)
{
    Matrix<T> temp(this->line, this->row);
    if (rhs.line == this->line && rhs.row == this->row)
    {
        temp.size = this->size;
        temp.element = new T[this->size];
        for (int i = 0; i < this->size; i++)
            temp.element[i] = this->element[i] + rhs.element[i];
        return temp;
    }
    else
    {
        temp.line = 0;
        temp.row = 0;
        temp.size = 0;
        std::cerr << "Error plus!";
        return temp;
    } 
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & rhs)
{
    Matrix<T> temp;
    if (this->row == rhs.line)
    {
        temp.line = this->line;
        temp.row = rhs.row;
        temp.size = this->line * rhs.row;
        temp.element = new T[temp.size];
        for (int i = 0; i < this->line; i++)
        {
            for (int j = 0; j < rhs.row; j++)
            {
                temp.element[i * temp.row + j] = 0;
                for (int k = 0; k < this->row; k++)
                    temp.element[i * temp.row + j] += this->element[i * this->row + k] * rhs.element[k * rhs.row + j];
            }
        }
    }
    return temp;
}

template<typename U>
std::istream & operator>>(std::istream & is, Matrix<U> & rhs)
{
    for (int i = 0; i < rhs.size; i++)
        is >> rhs.element[i];
    return is;
}

template<typename U>
std::ostream & operator<<(std::ostream & os, const Matrix<U> & rhs)
{
    for (int i = 0; i < rhs.size; i++)
    {
        os << rhs.element[i] << " ";
        if ((i + 1) % rhs.row == 0)
            os << std::endl;
    }
    return os;
}

template<typename T>
Matrix<T>::~Matrix()
{
    delete[] element;
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T> & rhs)
{
    if (rhs.line == this->line && rhs.row == this->row)
    {
        for (int i = 0; i < this->size; i++)
            this->element[i] += rhs.element[i];
    }
    else
        std::cerr << "Error plus!";
}

template<typename T>
void Matrix<T>::operator*=(const Matrix<T> & rhs)
{
    if (this->row == rhs.line)
    {
        Matrix<T> temp;
        temp.line = this->line;
        temp.row = rhs.row;
        temp.size = this->line * rhs.row;
        temp.element = new T[temp.size];
        for (int i = 0; i < this->line; i++)
        {
            for (int j = 0; j < rhs.row; j++)
            {
                temp.element[i * temp.row + j] = 0;
                for (int k = 0; k < this->row; k++)
                    temp.element[i * temp.row + j] += this->element[i * this->row + k] * rhs.element[k * rhs.row + j];
            }
        }
        *this = temp;
    }
    else
        std::cerr << "Error multiply!";
}

template<typename T>
T Matrix<T>::determinant()
{
    T result = 0;
    if (this->line == this->row)
    {
        if (this->line == 1)
            return this->element[0];
        else
        {
            for (int i = 0; i < this->row; i++)
            {
                Matrix<T> temp(this->line - 1, this->row - 1);
                for (int j = 1; j < this->line; j++)
                {
                    for (int k = 0; k < this->row; k++)
                    {
                        if (k < i)
                            temp.element[(j - 1) * temp.row + k] = this->element[j * this->row + k];
                        else if (k > i)
                            temp.element[(j - 1) * temp.row + k - 1] = this->element[j * this->row + k];
                    }
                }
                if (i % 2 == 0)
                    result += this->element[i] * temp.determinant();
                else
                    result -= this->element[i] * temp.determinant();
            }
            return result;
        }
    }
    else
    {
        std::cerr << "Error determinant!";
        return 0;
    }
}

template<typename T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix<T> temp(this->row, this->line);
    for (int i = 0; i < this->line; i++)
    {
        for (int j = 0; j < this->row; j++)
            temp.element[j * temp.row + i] = this->element[i * this->row + j];
    }
    return temp;
}

template<typename T>
Matrix<T> operator*(const T & rhs)
{
    Matrix<T> temp(rhs.line, rhs.row);
    for (int i = 0; i < rhs.size; i++)
        temp.element[i] = rhs * rhs.element[i];
    return temp;
}

template<typename U>
Matrix<U> operator*(const U & lhs, const Matrix<U> & rhs)
{
    Matrix<U> temp(rhs.line, rhs.row);
    for (int i = 0; i < rhs.size; i++)
        temp.element[i] = lhs * rhs.element[i];
    return temp;
}

template<typename T>
Matrix<T> Matrix<T>::adjoint()
{
    Matrix<T> temp(this->line, this->row);
    if (this->line == this->row)
    {
        temp.line = this->line;
        temp.row = this->row;
        temp.size = this->size;
        temp.element = new T[temp.size];
        for (int i = 0; i < this->line; i++)
        {
            for (int j = 0; j < this->row; j++)
            {
                Matrix<T> temp1(this->line - 1, this->row - 1);
                for (int k = 0; k < this->line; k++)
                {
                    if (k < i)
                    {
                        for (int l = 0; l < this->row; l++)
                        {
                            if (l < j)
                                temp1.element[k * temp1.row + l] = this->element[k * this->row + l];
                            else if (l > j)
                                temp1.element[k * temp1.row + l - 1] = this->element[k * this->row + l];
                        }
                    }
                    else if (k > i)
                    {
                        for (int l = 0; l < this->row; l++)
                        {
                            if (l < j)
                                temp1.element[(k - 1) * temp1.row + l] = this->element[k * this->row + l];
                            else if (l > j)
                                temp1.element[(k - 1) * temp1.row + l - 1] = this->element[k * this->row + l];
                        }
                    }
                }
                if ((i + j) % 2 == 0)
                    temp.element[i * temp.row + j] = temp1.determinant();
                else
                    temp.element[i * temp.row + j] = -temp1.determinant();
            }
        }
        return temp;
    }
    else
    {
        std::cerr << "Error adjoint!";
        return temp;
    }
}

template<typename T>
Matrix<T> Matrix<T>::inverse()
{
    Matrix<T> temp(this->line, this->row);
    if (this->line == this->row)
    {
        T det = this->determinant();
        if (det == 0)
        {
            std::cerr << "Error inverse!";
            return temp;
        }
        else
        {
            temp = this->adjoint().transpose();
            temp = (1 / det) * temp;
            return temp;
        }
    }
    else
    {
        std::cerr << "Error inverse!";
        return temp;
    }
}