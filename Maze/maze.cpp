#include "maze.hpp"

int main(int argc, const char *argv[])
{
	int n = atoi(argv[1]);
	// int n = 16;
	Maze m(n);
	std::cout << m;
	try
	{
		std::string in;
		while(true)
		{
			std::getline(std::cin, in);
			if(!m.handle(in))
			{
				std::cout << "Wrong input, try again:\n"; 
				continue;
			}

			std::cout << m;
		}
	}
	catch(const char* s)
	{
		std::cout << s << '\n';
	}
	return 0;
}
