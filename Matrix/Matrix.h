#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Rational.h"

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
class MatrixBase {
public:
	bool operator==(const MatrixBase<N, M, Field, Child>& rhs) const;
	Child<N, M, Field> operator+(Child<N, M, Field> rhs) const;
	Child<N, M, Field> operator-(Child<N, M, Field> rhs) const;
	Child<N, M, Field>& operator+=(Child<N, M, Field> rhs);
	Child<N, M, Field>& operator-=(Child<N, M, Field> rhs);
	template <size_t A>
	Child<N, A, Field> operator*(const Child<M, A, Field>& rhs);
	Child<N, M, Field> operator*(const Field& rhs);
	Child<N, M, Field>& operator*=(const Field& rhs);
	Child<M, N, Field> transposed() const;
	size_t rank() const; // can't
	std::vector<Field> getRow(size_t i) const;
	std::vector<Field> getColumn(size_t i) const;
	std::vector<Field>& operator[](size_t Row);
	const std::vector<Field>& operator[](size_t Row) const;
	template <size_t Q, size_t I, typename F, template <size_t, size_t, typename> typename Ch>
	friend std::ostream& operator<<(std::ostream& os, MatrixBase<Q, I, F, Ch> obj);
protected:
	MatrixBase(); //Only for sons
	MatrixBase(std::vector<std::vector<Field>> v); //you have to enter size
	std::vector<std::vector<Field>> v;
};

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field>& MatrixBase<N, M, Field, Child>::operator*=(const Field& rhs) {
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			v[i][j] *= rhs;
		}
	}
	return *(static_cast<Child<N, M, Field>*>(this));
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field> MatrixBase<N, M, Field, Child>::operator*(const Field& rhs) {
	return Child(*(static_cast<Child<N, M, Field>*>(this))) *= rhs;
}

template <size_t Q, size_t I, typename F, template <size_t, size_t, typename> typename Child>
std::ostream& operator<<(std::ostream& os, MatrixBase<Q, I, F, Child> obj) {
	for (size_t i = 0; i < Q; i++)
	{
		for (size_t j = 0; j < I; j++)
		{
			os << obj[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}

// template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
// size_t MatrixBase<N, M, Field, Child>::rank() const {
// 	size_t res = 0;
// 	for (size_t i = 0; i < std::min(N, M); i++) {
		
// 	}
// 	return res;
// }

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<M, N, Field> MatrixBase<N, M, Field, Child>::transposed() const {
	Child<M, N, Field> res(std::vector<std::vector<Field>>(M, std::vector<Field>(N)));
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			res[j][i] = v[i][j];
		}
	}
	return res;
}


template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
MatrixBase<N, M, Field, Child>::MatrixBase() {
	v.resize(N);
	for (size_t i = 0; i < N; i++)
	{
		v[i].resize(M);
	}
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
bool MatrixBase<N, M, Field, Child>::operator==(const MatrixBase<N, M, Field, Child>& rhs) const {
	return v == rhs.v;
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
template <size_t A>
Child<N, A, Field> MatrixBase<N, M, Field, Child>::operator*(const Child<M, A, Field>& rhs) {
	Child<N, A, Field> res;
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < A; j++)
		{
			res[i][j] = 0;
			for (size_t k = 0; k < M; k++)
			{
				res[i][j] += v[i][k] * rhs[k][j];
			}
		}
	}
	return res;
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
std::vector<Field> MatrixBase<N, M, Field, Child>::getRow(size_t i) const {
	return v[i];
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
std::vector<Field> MatrixBase<N, M, Field, Child>::getColumn(size_t i) const {
	std::vector<Field> res;
	for (size_t j = 0; j < N; j++)
	{
		res.push_back(v[j][i]);
	}
	return res;
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
const std::vector<Field>& MatrixBase<N, M, Field, Child>::operator[](size_t Row) const {
	return v[Row];
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
std::vector<Field>& MatrixBase<N, M, Field, Child>::operator[](size_t Row) {
	return v[Row];
}

template <size_t N, size_t M, typename Field = Rational>
struct Matrix : public MatrixBase<N, M, Field, Matrix> {
	Matrix(std::vector<std::vector<Field>> v);
protected:
	Matrix();
	friend MatrixBase<N, M, Field, Matrix>;
};

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field>::Matrix(std::vector<std::vector<Field>> v) : MatrixBase<N, M, Field, Matrix>(v)
{

}

template <size_t N, size_t M, typename Field>
Matrix<N, M, Field>::Matrix() : MatrixBase<N, M, Field, Matrix>()
{

}

template <size_t N, typename Field>
struct Matrix<N, N, Field> : public MatrixBase<N, N, Field, Matrix> {
	Matrix<N, N, Field> inverted() const;
	Matrix<N, N, Field>& invert();
	Field trace() const;
	Matrix<N, N, Field>& operator*=(const Matrix<N, N, Field>& rhs);
	Field det() const;
	Matrix();
	Matrix(std::vector<std::vector<Field>> v);
protected:
	friend MatrixBase<N, N, Field, Matrix>;
	size_t inversions(std::vector<size_t> ind) const {
		size_t res = 0;
		for (auto i = ind.begin(); i != ind.end(); i++) {
			for (auto j = i + 1; j != ind.end(); j++) {
				if (*i > *j) {
					res++;
				}
			}
		}
		return res;
	}
};

template <size_t N, typename Field>
Matrix<N, N, Field>::Matrix() : MatrixBase<N, N, Field, Matrix>() {
	for (size_t i = 0; i < N; i++)
	{
		this->v[i][i] = Field(1);
	}
	
}

template <size_t N, typename Field>
Matrix<N, N, Field>::Matrix(std::vector<std::vector<Field>> v) : MatrixBase<N, N, Field, Matrix>(v) {

}

template <size_t N, typename Field>
Matrix<N, N, Field> Matrix<N, N, Field>::inverted() const {
	Matrix<N, N, Field> res(this->transposed());
	Field det = this->det();
	det = Field(1) / det;
	res.MatrixBase<N, N, Field, Matrix>::operator*=(det);
	return res;
}

template <size_t N, typename Field>
Matrix<N, N, Field>& Matrix<N, N, Field>::invert() {
	*this = inverted();
	return *this;
}

template <size_t N, typename Field>
Field Matrix<N, N, Field>::trace() const {
	Field res = 0;
	for (size_t i = 0; i < N; i++)
	{
		res += this->v[i][i];
	}
	return res;
}

template <size_t N, typename Field>
Matrix<N, N, Field>& Matrix<N, N, Field>::operator*=(const Matrix<N, N, Field>& rhs) {
	Matrix<N, N, Field> res(*this);
	*this = res * rhs;
	return *this;
}

template <size_t N, typename Field>
Field Matrix<N, N, Field>::det() const {
	Field res = 0; //neutral element
	std::vector<size_t> ind;
	for (size_t i = 0; i < N; i++)
	{
		ind.push_back(i);
	}
	do
	{
		Field ress = 1;
		for (size_t j = 0; j < N; j++) {
			ress *= this->v[j][ind[j]];
		}
		ress *= (this->inversions(ind) % 2 == 0 ? 1 : -1);
		res += ress;
	} while (std::next_permutation(ind.begin(), ind.end()));
	return res;
}

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
MatrixBase<N, M, Field, Child>::MatrixBase(std::vector<std::vector<Field>> v) : v(v)
{

}

template<size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field>& MatrixBase<N, M, Field, Child>::operator+=(Child<N, M, Field> rhs)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			v[i][j] += rhs.v[i][j];
		}
	}
	return *(static_cast<Child<N, M, Field>*>(this));
}

template<size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field>& MatrixBase<N, M, Field, Child>::operator-=(Child<N, M, Field> rhs)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			v[i][j] -= rhs.v[i][j];
		}
	}
	return *(static_cast<Child<N, M, Field>*>(this));
}

template<size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field> MatrixBase<N, M, Field, Child>::operator-(Child<N, M, Field> rhs) const
{
	MatrixBase r(*this);
	return (r -= rhs);
}

template<size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Child<N, M, Field> MatrixBase<N, M, Field, Child>::operator+(Child<N, M, Field> rhs) const
{
	MatrixBase r(*this);
	return (r += rhs);
}

// template<size_t N, typename Field>
// MatrixBase<N, N, Field> MatrixBase<N, N, Field>::operator+(MatrixBase<N, N, Field> rhs) const
// {
// 	MatrixBase r(*this);
// 	return r;
// }

template <size_t N, typename Field = Rational>
struct SquareMatrix : Matrix<N, N, Field> {
	SquareMatrix();
};

template <size_t N, typename Field>
SquareMatrix<N, Field>::SquareMatrix() : Matrix<N, N, Field>() {

}