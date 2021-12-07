#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int hor_pos = 0, depth = 0, aim = 0;

std::vector<std::string> struntil(std::string to_until, char sep_char)
{
	std::vector <std::string> cuts(2);
	bool second_state = false;
	for (int i = 0; i<to_until.size(); i++)
	{
		if (!second_state)
			cuts[0].push_back(to_until[i]);
		else
			cuts[1].push_back(to_until[i]);
		if (to_until[i] == sep_char)
		{
			second_state = true;
		}
	}
	return cuts;
}

int main()
{
	std::ifstream resfile("Day2_Res.txt");
	std::string cur_line;
	std::string command;
	int times;
	while (std::getline(resfile, cur_line))
	{
		command = struntil(cur_line, ' ')[0]; 
		times = stoi(struntil(cur_line, ' ')[1]);
		if (command == "forward ")
		{
			hor_pos += times;
			depth += aim * times;
		}
		else if (command == "up ")
		{
			aim -= times;
		}
		else if (command == "down ")
		{
			aim += times;
		}
	}
	std::cout << "Depth: " << depth << ", Horizontal Position: " << hor_pos << std::endl;
	int multiplied = depth * hor_pos;
	std::cout << "Multiplied together, they are: " << multiplied << std::endl;
}
