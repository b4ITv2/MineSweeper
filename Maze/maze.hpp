#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cctype>

#define Maze_HPP
#define beginner 9
#define intermediate 16
#define bomb -1
#define modconst 7

class Maze
{
	int n, m, nbomb, nunseen;
	std::vector<std::vector<int>> matr;
	std::vector<std::vector<bool>> seen;
	void reveal_zero(int, int);
public:
	Maze(const Maze&);
	Maze(int diff);
	Maze();
	std::ostream& print(std::ostream&) const;
	bool check(int, int);
	bool flag(int, int);
	bool handle(const std::string&);
};

Maze::Maze(const Maze& M) : n(M.n), m(M.m), nbomb(M.nbomb), nunseen(M.nunseen), matr(M.matr), seen(M.seen) {} 

Maze::Maze(int diff)
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
	n = diff; m = diff, nbomb = 0, nunseen = diff * diff;
	matr = std::vector<std::vector<int>>(diff, std::vector<int>(diff, 0));
	seen = std::vector<std::vector<bool>>(diff, std::vector<bool>(diff, false));
	srand(time(nullptr));
	int o, s, ni, nj, i ,j;
	for(i = 0; i < n; ++i)
	{
		for(j = 0; j < m; ++j)
		{
			if(!(rand() % modconst))
			{
				matr[i][j] = bomb;
				++nbomb;
				for(s = -1; s <= 1; ++s)
				{
					for(o = -1; o <= 1; ++o)
					{
						ni = i + s; nj = j + o;
						if(ni >= 0 && nj >= 0 && ni < n && nj < m && matr[ni][nj] != bomb)
						{
							++matr[ni][nj];
						}
					}
				}
			}
		}
	}
}

Maze::Maze() : Maze(beginner)
{
	std::cout << "Beginner applied.\n";
}

std::ostream& Maze::print(std::ostream& s) const
{
	s << ((n < 10) ? "  " : "   ");
	for(int j = 0; j < m; ++j)
	{
		s << j + 1 << ((n > 9) ? ((j > 8) ? " " : "  ") : " ");
	}
	s << '\n';	
	for(int i = 0; i < n; ++i)
	{
	 	s << i + 1 << ((n > 9) ? ((i > 8) ? ":" : " :") : ":"); // i + 1 is printed not i so i > 8
		for(int j = 0; j < m; ++j)
		{
			if(seen[i][j])
			{
				switch(matr[i][j])
				{
					case -2: 
					{
						s << ((n > 9) ? "⚑  " : "⚑ ");
						break;
					}
					case 0:
	  				{
						s << ((n > 9) ? "   " : "  ");
						break;
					}
					default:
	  				{
						s << matr[i][j] << ((n > 9) ? "  " : " ");
						break;
					}
				}
			}
			else
			{
				if(j - 1 >= 0 && j + 1 < m && (seen[i][j - 1] || !seen[i][j - 1]) && seen[i][j + 1])
				{
					s << ((n > 9) ? "█  " : "█ ");
				}
				else
				{
					s << ((n > 9) ? "███" : "██");
				}
			}
		}
		s << '\n';
	}
	return s;
}

std::ostream& operator<<(std::ostream& s, const Maze& m)
{
	return m.print(s);
}

void Maze::reveal_zero(int i, int j)
{
	if(i < 0 || j < 0 || i >= n || j >= m)
	{
		return;
	}
	if(seen[i][j])
	{
		return;
	}
	seen[i][j] = true;
	--nunseen;
	if(matr[i][j])
	{
		return;
	}
	for(int s = -1; s <= 1; ++s)
	{
		for(int o = -1; o <= 1; ++o)
		{
			if(s || o)
			{
				reveal_zero(i + s, j + o);
			}
		}
	}
}

bool Maze::check(int i, int j)
{
	if(i < 0 || j < 0  || i >= n || j >= m)
	{
		return false;
	}
	if(seen[i][j])
	{
		return false;
	}
	if(matr[i][j] == bomb)
	{
		throw "BOOM!";
	}
	reveal_zero(i, j);
	if(nbomb == nunseen)
	{
		throw "Well Played!";
	}
	return true;
}

bool Maze::flag(int i, int j)
{
	if(i < 0 || j < 0  || i >= n || j >= m)
	{
		return false;
	}
	if(seen[i][j])
	{
		return false;
	}
	seen[i][j] = true;
	matr[i][j] = -2;
	return true;
}

bool Maze::handle(const std::string& s)
{
	int len = s.length();
	int num[2] = {0, 0};
	int j = 0, i = 0;
	for(; i < len && j < 2; ++i)
	{
		if(!isdigit(s[i]) && s[i] != ' ')
		{
			return false;
		}
		if(s[i] != ' ')
		{
			num[j] *= 10;
			num[j] += s[i] - '0';
		}
	 	else
		{
			++j;
		}
	}
	--num[0]; --num[1];
	if(!isdigit(s[len - 1]))
	{
		if(s[len - 1] == 'f')
		{
			if(!Maze::flag(num[0], num[1]))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if(!Maze::check(num[0], num[1]))
	{
		return false;
	}
	return true;
}
