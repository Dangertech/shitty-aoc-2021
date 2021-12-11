#include <iostream>
#include <fstream>
#include <vector>

std::string resloc = "input.txt";

struct dumbo
{
	int state;
	bool has_flashed;
};
std::vector < std::vector <dumbo> > octopi;

void get_input()
{
	std::ifstream resfile(resloc);
	std::string cur_line;
	while (getline(resfile, cur_line))
	{
		octopi.push_back(std::vector<dumbo>());
		for (int i = 0; i<cur_line.length(); i++)
		{
			octopi[octopi.size()-1].push_back({cur_line[i]-48, false});
		}
	}
}

void print_2dint(std::vector <std::vector<dumbo>> vec)
{
	for (int i = 0; i<vec.size(); i++)
	{
		for (int j = 0; j<vec[i].size(); j++)
		{
			if (vec[i][j].state == 0)
				std::cout << "\033[31m";
			std::cout << vec[i][j].state << "\033[0m";
		}
		std::cout << std::endl;
	}
}

void safe_increase (int y, int x, std::vector<std::vector<dumbo>>& vec)
{
	if (y < vec.size() && y >= 0)
	{
		if (x < vec[y].size() && x >= 0)
			vec[y][x].state++;
	}
}


// Modify the cell states according to the dumbo octopus rules
int cell_step(std::vector <std::vector<dumbo>>& vec)
{
	// Tracker of flashes this step
	int flashes = 0;
	// Increase the state of every cell by one
	for (int i = 0; i<vec.size(); i++)
	{
		for (int j = 0; j<vec[i].size(); j++)
			vec[i][j].state++;
	}

	bool has_flashers = true;
	while (has_flashers)
	{
		// Flash every cell with a state higher than 9
		for (int y = 0; y<vec.size(); y++)
		{
			for (int x = 0; x<vec[y].size(); x++)
			{
				if (vec[y][x].state > 9 && vec[y][x].has_flashed == false)
				{
					safe_increase(y, x-1, vec);
					safe_increase(y-1, x-1, vec);
					safe_increase(y-1, x, vec);
					safe_increase(y-1, x+1, vec);
					safe_increase(y, x+1, vec);
					safe_increase(y+1, x+1, vec);
					safe_increase(y+1, x, vec);
					safe_increase(y+1, x-1, vec);
					vec[y][x].has_flashed = true;
					flashes++;
				}
			}
		}

		// Check if there are still flashers
		bool flashers = false;
		for (int i = 0; i<vec.size(); i++)
		{
			for (int j = 0; j<vec[i].size(); j++)
			{
				if (vec[i][j].state > 9 && vec[i][j].has_flashed == false)
				{
					flashers = true;
				}
			}
		}
		if (flashers == false)
			has_flashers = false;
	}

	for (int y = 0; y<vec.size(); y++)
	{
		for (int x = 0; x<vec[y].size(); x++)
		{
			if (vec[y][x].state > 9 && vec[y][x].has_flashed == true)
			{
				vec[y][x].state = 0;
				vec[y][x].has_flashed = false;
			}
		}
	}
	return flashes;
}


int main()
{
	get_input();
	std::cout << "Before any steps: " << std::endl;
	print_2dint(octopi);

	int total_flashes = 0;
	int step = 0;
	int these_flashes = 0;
	while (these_flashes < octopi.size() * octopi[0].size())
	{
		step++;
		these_flashes = 0;
		 
		these_flashes = cell_step(octopi);
		total_flashes += these_flashes;
		 
		std::cout << std::endl << "After step " << step << ":" << std::endl;
		print_2dint(octopi);
		std::cout << "Flashes this step: " << these_flashes << std::endl;
		std::cout << "Flashes now in total: " << total_flashes << std::endl;
	}
	std::cout << "All flashed on step " << step << "!" << std::endl;
}
