#include<fstream>
#include<iostream>

int increases = 0;

int main()
{
	std::ifstream resfile("Day1_1_Res.txt");
	std::string cur_line;
	int cur_int = 0, last_int = 0, calcs = 0;
	while (std::getline(resfile, cur_line))
	{
		int cur_int = stoi(cur_line);
		std::cout << cur_int;
		if (cur_int > last_int && calcs > 0)
		{
			increases++;
			std::cout << " (Increased)" << std::endl;
		}
		else
		{
			std::cout << " (Decreased)" << std::endl;
		}
		last_int = cur_int; 
		calcs++;
	}
	std::cout << increases << std::endl;
	return 0;
}
