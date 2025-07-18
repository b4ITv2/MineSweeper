#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

#define MATRIX_HPP
#define beginner 9
#define intermediate 16
#define bomb -1
#define modconst 7

class Matrix
{
	int n, m;
	std::vector<std::vector<int>> matr;
	std::vector<std::vector<bool>> seen;
public:
	Matrix(const Matrix&);
	Matrix(int diff);
	Matrix();
	std::ostream& print(std::ostream&) const;
};

Matrix::Matrix(const Matrix& M) : n(M.n), m(M.m), matr(M.matr), seen(M.seen) {} 

Matrix::Matrix(int diff)
{
	if(diff != beginner && diff != intermediate)
	{
		std::cout << "Wrong difficulty provided.\nBeginner applied.\n";
		diff = beginner;
	}
	else if(diff == beginner)
	{
		std::cout << "Beginner applied.\n";
	}
	if(diff == intermediate)
	{
		std::cout << "Intermediate applied.\n";
	}
	n = diff; m = diff;
	matr = std::vector<std::vector<int>>(diff, std::vector<int>(diff, 0));
	seen = std::vector<std::vector<bool>>(diff, std::vector<bool>(diff, 0));
	srand(time(nullptr));
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			if(!(rand() % modconst))
			{
				matr[i][j] = bomb;
			}
		}
	}
}

Matrix::Matrix() : Matrix(beginner)
{
	std::cout << "Beginner applied.\n";
}

std::ostream& Matrix::print(std::ostream& s) const
{
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			if(seen[i][j])
			{
				s << std::setw(3) << seen[i][j];
			}
			else
			{
				s << std::setw(3) << '0';
			}
		}
		s << '\n';
	}
	return s;
}

std::ostream& operator<<(std::ostream& s, const Matrix& m)
{
	return m.print(s);
}
