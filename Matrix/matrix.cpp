#include "matrix.hpp"

int main(int argc, const char *argv[])
{
	int n = atoi(argv[1]);
	Matrix m(n);
	std::cout << m;
	return 0;
}
