#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <unordered_map>

std::string resloc = "try.txt";


std::vector <std::vector<int>> grid;

void print_grid()
{
	for (int y = 0; y<grid.size(); y++)
	{
		for (int x = 0; x<grid[y].size(); x++)
			std::cout << grid[y][x];
		std::cout << std::endl;
	}
}

void get_input()
{
	std::ifstream resfile(resloc);
	std::string cur_line;
	while (getline(resfile, cur_line))
	{
		grid.push_back(std::vector<int>());
		for (int i=0; i<cur_line.size(); i++)
		{
			grid[grid.size()-1].push_back(cur_line[i]-48);
		}
	}
}

////// Everything needed for dijkstra()

struct pos
{
	int y;
	int x;
};

struct dcell
{
	int risk;
	unsigned int distance = std::numeric_limits<unsigned int>::max();
	bool visited = false;
};

// Print a component of the dijkstra variables
void print_dcomp(std::vector<std::vector<dcell>> grid, std::string component, pos my_pos)
{
	for (int i = 0; i<grid.size(); i++)
	{
		for (int j = 0; j<grid[i].size(); j++)
		{
			if (i == my_pos.y && j == my_pos.x)
				std::cout << "\033[31m";
			if (component == "distance")
			{
				if (grid[i][j].distance < std::numeric_limits<unsigned int>::max())
					std::cout << grid[i][j].distance;
				else
					std::cout << "-";
			}
			std::cout << "\033[0m";
		}
		std::cout << std::endl;
	}
}

std::vector<std::vector<dcell>> make_dgrid (std::vector<std::vector<int>> nodes)
{
	std::vector<std::vector<dcell>> dgrid;
	for (int i = 0; i<nodes.size(); i++)
	{
		dgrid.push_back(std::vector<dcell>());
		for (int j = 0; j<nodes.size(); j++)
		{
			dgrid[dgrid.size()-1].push_back({nodes[i][j]});
		}
	}
	return dgrid;
}

void dijkstra (std::vector <std::vector<int>> nodes)
{
	// TODO: Watch https://www.youtube.com/watch?v=GazC3A4OQTE and implement the Dijkstra algorithm
	//
	// I know, I fucked up a little down there, .distance is useles, I think I need a vector containing all distances
	std::vector<std::vector<dcell>> dgrid = make_dgrid(nodes);
	pos my_pos = {0, 0};
	dgrid[my_pos.y][my_pos.x].distance = 0;
	 
	std::vector<pos> loop_pos = {{0,1},{1,0},{0,-1},{-1,0}};
	// Calculate the distances from the position
	for (pos this_pos : loop_pos)
	{
		std::cout << my_pos.y + this_pos.y << std::endl;
		if (my_pos.y + this_pos.y > 0 && my_pos.y + this_pos.y < dgrid.size()
			|| my_pos.x + this_pos.x > 0 && my_pos.x + this_pos.x < dgrid[0].size())
		{
			std::cout << "Hit" <<std::endl;
			dgrid[my_pos.y + this_pos.y][my_pos.x + this_pos.x].distance = dgrid[my_pos.y + this_pos.y][my_pos.x + this_pos.x].risk;
		}
	}
	// Get the next position to move to
	pos win_pos = {my_pos.y+loop_pos[0].y, my_pos.x+loop_pos[0].x};
	std::cout << win_pos.y << " " << win_pos.x << std::endl;
	for (pos tpos : loop_pos)
	{
		if (my_pos.y + tpos.y > 0 && my_pos.y + tpos.y < dgrid.size()
			|| my_pos.x + tpos.x > 0 && my_pos.x + tpos.x < dgrid[0].size())
		{
			if (dgrid[my_pos.y + tpos.y][my_pos.x + tpos.x].distance < dgrid[win_pos.y][win_pos.x].distance)
				win_pos = {my_pos.y + tpos.y, my_pos.x + tpos.x};
		}
	}
	std::cout << win_pos.y << " " << win_pos.x << std::endl;
	my_pos = win_pos;
	print_dcomp(dgrid, "distance", my_pos);
}

int main()
{
	get_input();
	print_grid();
	dijkstra(grid);
}
