#pragma once
#include <iostream>
#include <vector>
#include "Rational.h"

template <size_t N, size_t M, typename Field = Rational>
class Matrix {
public:
	template <size_t Q, size_t I, typename F>
	bool operator==(Matrix<Q, I, F> rhs) const {
		return false;
	}
	template <>
	bool operator==<N, M, Field>(Matrix<N, M, Field> rhs) const;
	Matrix<N, M, Field>(std::vector<std::vector<Field>> v); //you have to enter size
	Matrix<N, M, Field> operator+(Matrix<N, M, Field> rhs) const;
	Matrix<N, M, Field> operator-(Matrix<N, M, Field> rhs) const;
	Matrix<N, M, Field>& operator+=(Matrix<N, M, Field> rhs);
	Matrix<N, M, Field>& operator-=(Matrix<N, M, Field> rhs);
	Field det() const; //kolhoz
	Matrix<M, N, Field> transposed() const;
	size_t rank() const;
	template <size_t Q, typename F = Field>
	Matrix<Q, Q, Field> inverted() const;
	template <size_t Q, typename F = Field>
	Matrix<Q, Q, Field>& invert();
	//trace
	std::vector<Field> getRow(size_t i) const;
	std::vector<Field> getColumn(size_t i) const;
	std::vector<Field>& operator[](size_t Row);
	const std::vector<Field>& operator[](size_t Row) const;
	template <size_t Q, size_t I, typename F>
	friend std::ostream& operator<<(std::ostream& os, Matrix<Q, I, F> obj);
protected:
	Matrix(); //Only squareMatrix
	std::vector<std::vector<Field>> v;
};

template <size_t N, typename Field = Rational>
class Matrix : Matrix<N, N, Field> {

};

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field>::Matrix() {

}

template<size_t N, size_t M, typename Field>
Matrix<N, M, Field>::Matrix(std::vector<std::vector<Field>> v) : v(v)
{

}

template<size_t N, size_t M, typename Field>
inline Matrix<N, M, Field>& Matrix<N, M, Field>::operator+=(Matrix<N, M, Field> rhs)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			v[i][j] += rhs.v[i][j];
		}
	}
	return *this;
}

template<size_t N, size_t M, typename Field>
inline Matrix<N, M, Field> Matrix<N, M, Field>::operator-(Matrix<N, M, Field> rhs) const
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			v[i][j] -= rhs.v[i][j];
		}
	}
	return *this;
}

template<size_t N, size_t M, typename Field>
inline Matrix<N, M, Field>& Matrix<N, M, Field>::operator-=(Matrix<N, M, Field> rhs)
{
	Matrix r(*this);
	return (r -= rhs);
}

template<size_t N, size_t M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator+(Matrix<N, M, Field> rhs) const
{
	Matrix r(*this);
	return (r += rhs);
}

template <size_t N, typename Field = Rational>
struct SquareMatrix : Matrix<N, N, Field> {
	SquareMatrix();
};

template <size_t N, typename Field>
SquareMatrix<N, Field>::SquareMatrix() : Matrix<N, N, Field>() {

}