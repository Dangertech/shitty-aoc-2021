#include <iostream>
#include <fstream>
#include <vector>

std::string resloc = "input.txt";

void get_input()
{
	std::ifstream resfile(resloc);
	std::string cur_line;
	while (getline(resfile, cur_line))
	{

	}
}

int main()
{
	get_input();
}
