#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
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
	struct MatrixVector : std::vector<Field> {
		MatrixVector() : std::vector<Field>() {}
		MatrixVector(const std::vector<Field>& v) : std::vector<Field>(v) {}
		MatrixVector& operator+=(const MatrixVector& rhs) {
			for (size_t i = 0; i < this->size(); i++)
			{
				this->at(i) += rhs.at(i);
			}
			return *this;
		}
		MatrixVector& operator-=(const MatrixVector& rhs) {
			return (*this += (rhs * -1));
		}
		MatrixVector operator*(const Field& rhs) const {
			MatrixVector res;
			for (size_t i = 0; i < this->size(); i++)
			{
				res.push_back(this->at(i) * rhs);
			}
			return res;
		}
		MatrixVector operator/(const Field& rhs) const {
			return *this * (1 / rhs);
		}
	};
	MatrixBase(); //Only for sons
	MatrixBase(std::vector<std::vector<Field>> v); //you have to enter size
	std::vector<std::vector<Field>> v;
	bool NextSet(std::vector<size_t>& a, size_t m) const
	{
		int n = a.size();
		int k = m;
		for (int i = k - 1; i >= 0; --i)
			if (a[i] < n - k + i /*+ 1*/)
			{
				++a[i];
				for (int j = i + 1; j < k; ++j)
					a[j] = a[j - 1] + 1;
				return true;
			}
		return false;
	}
	Field detAsF(const std::vector<std::vector<Field>>& v) const;
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
	
};

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
size_t MatrixBase<N, M, Field, Child>::rank() const {
	// size_t res = 0;
	// size_t Q = std::min(N, M);
	// for (size_t i = 1; i <= Q; i++)
	// {
	// 	bool b = true;
	// 	std::vector<size_t> rows;
	// 	for (size_t j = 0; j < M; j++)
	// 	{
	// 		rows.push_back(j);
	// 	}
	// 	do {
	// 		std::vector<size_t> cols;
	// 		for (size_t j = 0; j < N; j++)
	// 		{
	// 			cols.push_back(j);
	// 		}
	// 		do {
	// 			std::vector<std::vector<Field>> tmp(i, std::vector<Field>(i));
	// 			for (size_t j = 0; j < i; j++) {
	// 				for (size_t k = 0; k < i; k++)
	// 				{
	// 					tmp[k][j] = v[cols[k]][rows[j]];
	// 				}
	// 			}
	// 			if (this->detAsF(tmp) != Field(0)) {
	// 				res++;
	// 				b = false;
	// 				break;
	// 			}
	// 		} while (NextSet(cols, i));
	// 		if (!b)
	// 		{
	// 			break;
	// 		}
	// 	} while (NextSet(rows, i));
	// 	if (b) {
	// 		break;
	// 	}
	// }
	// return res;
	size_t s = N <= M ? N : M;
	std::vector<MatrixVector> tv;
	if (N <= M) {
		for (size_t i = 0; i < s; i++)
		{
			tv.push_back(v[i]);
		}
	} else {
		for (size_t i = 0; i < M; i++)
		{
			MatrixVector q;
			for (size_t j = 0; j < N; j++)
			{
				q.push_back(v[j][i]);
			}
			tv.push_back(q);
		}
	}
	//auto tmp = N <= M ? *this : this->transposed();
	//auto tv = tmp.v
	
	for (size_t i = 0; i < s; i++)
	{
		if (tv[i][i] == Field(0)) {
			bool iz = true;
			for (size_t j = i + 1; j < s; j++)
			{
				if (tv[j][i] != Field(0)) {
					std::swap(tv[i], tv[j]);
					iz = false;
					break;
				}
			}
			if (iz) {
				s--;
				for (size_t j = i; j < s; j++) {
					std::swap(tv[i][j], tv[i][s]);
				}
				i--;
				continue;
			}
		}
		for (size_t j = i + 1; j < s; j++)
		{
			auto t = tv[j][i] / tv[i][i];
			tv[j] -= tv[i] * t;
		}
	}
	return s;
}

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

template <size_t N, size_t M, typename Field, template <size_t, size_t, typename> typename Child>
Field MatrixBase<N, M, Field, Child>::detAsF(const std::vector<std::vector<Field>>& wer) const {
	// Field res = 0; //neutral element
	// std::vector<size_t> ind;
	// for (size_t i = 0; i < v.size(); i++)
	// {
	// 	ind.push_back(i);
	// }
	// do
	// {
	// 	Field ress = 1;
	// 	for (size_t j = 0; j < v.size(); j++) {
	// 		ress *= v[j][ind[j]];
	// 	}
	// 	ress *= (this->inversions(ind) % 2 == 0 ? 1 : -1);
	// 	res += ress;
	// } while (std::next_permutation(ind.begin(), ind.end()));
	// return res;
	std::vector<MatrixVector> v;
	for (size_t i = 0; i < wer.size(); i++)
	{
		v.push_back(MatrixVector(wer[i]));
	}
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i][i] == Field(0)) {
			return Field(0);
		}
		for (size_t j = i + 1; j < v.size(); j++) {
			Field tmp = v[j][i] / v[i][i];
			v[j] -= (v[i] * tmp);
		}
	}
	Field res = 1;
	for (size_t i = 0; i < v.size(); i++)
	{
		res *= v[i][i];
	}
	return res;

}

template <size_t N, typename Field>
Field Matrix<N, N, Field>::det() const {
	return this->detAsF(this->v);
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