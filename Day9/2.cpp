#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

std::string resloc = "input.txt";

struct cell
{
	int height;
	int basin = 0; // Unique index for each basin
};

std::vector < std::vector < struct cell > > grid;

void get_input()
{
	std::ifstream resfile(resloc);
	char cur_char;
	grid.push_back(std::vector<struct cell>());
	while (resfile.get(cur_char))
	{
		if (cur_char == '\n')
			grid.push_back(std::vector <struct cell>());
		else
		{
			struct cell new_cell = {cur_char -48, 0};
			grid[grid.size()-1].push_back(new_cell);
		}
	}
}

void print_grid()
{
	for (int y=0; y<grid.size(); y++)
	{
		for (int x=0; x<grid[y].size(); x++)
		{
			if (grid[y][x].basin > 0)
				std::cout << "\033[31m";
			if (grid[y][x].basin > 9)
				std::cout << "!";
			else
				std::cout << grid[y][x].basin;
			std::cout << "\033[0m";
		}
		std::cout << std::endl;
	}
}

bool smallest_int(int to_comp, std::vector<cell> vec)
{
	for (int i=0; i<vec.size(); i++)
	{
		if (vec[i].height <= to_comp)
			return false;
	}
	return true;
}

std::vector <struct cell> get_adjacents(int y, int x)
{
	std::vector <struct cell> adjacents;
	if (x < grid[y].size() -1)
		adjacents.push_back(grid[y][x+1]); // right
	if (x > 0)
		adjacents.push_back(grid[y][x-1]); // left
	if (y < grid.size() -2)
		adjacents.push_back(grid[y+1][x]); // down
	if (y > 0)
		adjacents.push_back(grid[y-1][x]); // up
	return adjacents;
}

void flood_fill(int y, int x, int fill_basin)
{
	if (y < 0 || y >= grid.size() || x < 0 || x >= grid[y].size())
		return;
	 
	if (grid[y][x].basin != 0)
		return;

	if (grid[y][x].height == 9)
		return;

	grid[y][x].basin = fill_basin;
	//OOOOOOOHHHH Shit, recursion!
	// Can I work at Google now?
	flood_fill(y+1, x, fill_basin);
	flood_fill(y-1, x, fill_basin);
	flood_fill(y, x+1, fill_basin);
	flood_fill(y, x-1, fill_basin);
}

int main()
{
	get_input();

	int basin_count = 0;
	for (int y=0; y<grid.size(); y++)
	{
		for (int x=0; x<grid[y].size(); x++)
		{
			if (grid[y][x].height != 9)
			{
				auto adjacents = get_adjacents(y, x);
				
				// start from the unique lowest point of the basin
				if (smallest_int(grid[y][x].height, adjacents))
				{
					int my_basin = ++basin_count;
					// Use the flood fill algorithm to fill the whole basin
					flood_fill(y, x, my_basin);
				}
			}
		}
	}
	std::cout << "Total basins: " << basin_count << std::endl;
	print_grid();
	 
	std::vector <int> basin_distrib(basin_count+1);
	for (int y = 0; y<grid.size(); y++)
	{
		for(int x=0; x<grid[y].size(); x++)
		{
			basin_distrib[grid[y][x].basin]++; 
		}
	}

	for (int i=0; i<basin_distrib.size(); i++)
		std::cout << "[" << i << "]: " << basin_distrib[i] << std::endl;
	std::cout << std::endl;

	// Remove the 0s
	basin_distrib.erase(basin_distrib.begin(), basin_distrib.begin()+1);
	std::cout << "Sorting array... ";
	std::sort(basin_distrib.begin(), basin_distrib.end(), std::greater<int>());
	std::cout << "Done!" << std::endl; // Just a nice lil' touch

	for (int i=0; i<basin_distrib.size(); i++)
		std::cout << "[" << i << "]: " << basin_distrib[i] << std::endl;
	std::cout << std::endl;
	 
	std::cout << "Solution: " << basin_distrib[0] * basin_distrib[1] * basin_distrib[2] << std::endl;
}
