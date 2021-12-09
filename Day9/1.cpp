#include <iostream>
#include <fstream>
#include <vector>

std::string resloc = "input.txt";
std::vector < std::vector < int > > grid;

void get_input()
{
	std::ifstream resfile(resloc);
	char cur_char;
	grid.push_back(std::vector<int>());
	while (resfile.get(cur_char))
	{
		if (cur_char == '\n')
			grid.push_back(std::vector <int>());
		else
			grid[grid.size()-1].push_back(cur_char - 48);
	}
}

void print_grid()
{
	for (int y=0; y<grid.size(); y++)
	{
		for (int x=0; x<grid[y].size(); x++)
			std::cout << grid[y][x];
		std::cout << std::endl;
	}
}

bool smallest_int(int to_comp, std::vector<int> vec)
{
	for (int i=0; i<vec.size(); i++)
	{
		if (vec[i] <= to_comp)
			return false;
	}
	return true;
}

int main()
{
	get_input();
	print_grid();

	int combined_risk = 0;
	for (int y=0; y<grid.size(); y++)
	{
		for (int x=0; x<grid[y].size(); x++)
		{
			std::vector <int> adjacents;
			 
			if (x < grid[y].size() -1)
				adjacents.push_back(grid[y][x+1]); // right
			if (x > 0)
				adjacents.push_back(grid[y][x-1]); // left
			if (y < grid.size() -2)
				adjacents.push_back(grid[y+1][x]); // down
			if (y > 0)
				adjacents.push_back(grid[y-1][x]); // up
			 
			for (int i = 0; i<adjacents.size(); i++)
				std::cout << adjacents[i];
			std::cout << std::endl;

			if (smallest_int(grid[y][x], adjacents))
			{
				combined_risk += 1+grid[y][x];
			}
		}
	}
	std::cout << "Combined Risk: " << combined_risk << std::endl;
}
