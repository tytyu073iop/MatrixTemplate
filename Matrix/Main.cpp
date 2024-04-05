//Biryuk Ilya, 11 Group
#include "Matrix.h"

int main() {
	{
		Matrix<8, 8, int> m;
		m.det();
		//m + m;
	}
	{
		SquareMatrix<8> q;
		SquareMatrix<8, int> m;
		m.det();
	}
	{
		//Matrix<8,9> m; //no construct
		//but
		//Matrix<8,8> m; //too
		//Matrix<8> m; //not
	}
	
	// {
	// 	std::cout << "Enter the size of the matrix: ";
	// 	int n;
	// 	std::cin >> n;
	// 	Matrix<n, n> m;
	// } //do not work
	return 0;
}