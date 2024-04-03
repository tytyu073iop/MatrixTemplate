#pragma once
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
	bool operator==<N, M, Field>(Matrix<Q, I, F> rhs) const;
	template <size_t Q, typename F = Field>
	Matrix<Q, Q, F>(); //E //!think about forbid non-sqare
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
protected:
	template <size_t Q, size_t I, typename F>
	Matrix<Q, I, F>();
};