//Biryuk Ilya, 11 Group
#include "Matrix.h"

template <typename T>
void print_vector(const std::vector<T> &v) {
	for (T i : v) {
		std::cout << i << ' ';
	}
	std::cout << '\n';
}

int main() {
	Matrix <3, 4> m({{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 19, 23, 40}});
	std::cout << "m:\n" << m << '\n';
	Matrix <3, 4> m2({{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 19, 23, 40}});
	std::cout << "m2 == m: " << (m2 == m) << '\n';
	Matrix <3, 3> sq;
	std::cout << "sq:\n" << sq << '\n';
	std::cout << "m + m:\n" << (m + m) << '\n';
	std::cout << "m - m:\n" << (m - m) << '\n';
	std::cout << "m * 3:\n" << (m * 3) << '\n';
	Matrix <4, 3> m3({{0, 1, 2}, {4, 5, 6}, {8, 19, 23}, {40, 41, 42}});
	std::cout << "m3:\n" << m3 << '\n';
	std::cout << "m * m3:\n" << (m * m3) << '\n';
	// std::cout << "m * m:\n" << (m * m) << '\n'; // do not compile
	// std::cout << "m + sq:\n" << (m + sq) << '\n'; // do not compile
	{
		Matrix t(m);
		std::cout << "t == m: " << (t == m) << '\n';
		std::cout << "t += m:\n" << (t += m) << '\n';
		std::cout << "t -= m:\n" << (t -= m) << '\n';
		std::cout << "t *= 3:\n" << (t *= 3) << '\n';
	}
	{
		Matrix t(sq);
		std::cout << "t == sq: " << (t == sq) << '\n';
		std::cout << "t *= sq:\n" << (t *= sq) << '\n';
	}
	// std::cout << "det(m): " << m.det() << '\n'; // do not compile
	std::cout << "det(sq): " << (sq.det()) << '\n';
	std::cout << "m.transposed:\n" << (m.transposed()) << '\n';
	// std::cout << "m.rank: " << m.rank() << '\n'; // do not compile
	std::cout << "m.rank: " << m.rank() << '\n'; // can't make
	{
		Matrix<3, 3> t({ {1, 0, 0}, {0, 1, 0}, {1, 1, 0} });
		std::cout << "t.rank: " << t.rank() << '\n';
	}
	// std::cout << "m.trace" << m.trace() << '\n'; // do not compile
	std::cout << "sq.trace" << (sq.trace()) << '\n';
	// std::cout << "m.inverted:\n" << (m.inverted()) << '\n'; // do not compile
	std::cout << "sq.inverted:\n" << (sq.inverted()) << '\n';
	{
		Matrix t(sq);
		std::cout << "t == sq: " << (t == sq) << '\n';
		std::cout << "t.invert():\n" << (t.invert()) << '\n';
	}
	std::cout << "m.getRow(0): ";
	print_vector(m.getRow(0));
	std::cout << '\n';
	std::cout << "m.getColumn(0): ";
	print_vector(m.getColumn(0));
	std::cout << '\n';
	std::cout << "m[0][0]: " << m[0][0] << '\n';
	m[0][0] = 8;
	std::cout << "m[0][0]: " << m[0][0] << '\n';
	{
		const Matrix t(m);
		std::cout << "t == m: " << (t == m) << '\n';
		std::cout << "t[0][0]: " << t[0][0] << '\n';
		// t[0][0] = 8; // do not compile 
	}
	{
		SquareMatrix<3> t;
		std::cout << "t from square:\n" << t << '\n';
	}
	return 0;
}