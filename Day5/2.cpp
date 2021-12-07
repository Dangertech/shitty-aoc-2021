#include <iostream>
#include <fstream>
#include <vector>

// Here, I try to break up the code in
// many small, toggleable functions
//
// This makes the code way easier to edit
// and adapt for part 2

struct pos // Describes any position
{
	int x;
	int y;
};

struct pipe // Describes the pipe endpoints
{
	struct pos begin;
	struct pos end;
};

void print_pipe( pipe my_pipe ) // Prints any pipe
{
	std::cout << "Begin: " << my_pipe.begin.x << ", " << my_pipe.begin.y << "; "
		<< "End: " << my_pipe.end.x << ", " << my_pipe.end.y << std::endl;
}

std::vector < pipe > plist; // List of all pipe endpoints, computed in get_input()

pipe getpoints( std::string my_str )
{
	// Receives something like '0,9 -> 5,9'
	 
	pipe out_pipe;
	std::string strnum;
	int i = 0;

	// find begin.x
	while (my_str[i] != ',')
	{
		strnum += my_str[i];
		i++;
	}
	out_pipe.begin.x = stoi(strnum);
	i++;
	strnum = "";

	// begin.y
	while (my_str[i] != ' ')
	{
		strnum += my_str[i];
		i++;
	}
	out_pipe.begin.y = stoi(strnum);
	strnum = "";

	// Jump to next digit to ignore the ' -> '
	while (!isdigit(my_str[i]))
	{
		i++;
	}
	// end.x
	while (my_str[i] != ',')
	{
		strnum += my_str[i];
		i++;
	}
	out_pipe.end.x = stoi(strnum);
	i++;
	strnum = "";

	// end.y
	while(i < my_str.size())
	{
		strnum += my_str[i];
		i++;
	}
	out_pipe.end.y = stoi(strnum);
	return out_pipe;
}

void get_input()
{
	std::ifstream resfile("user.txt");
	std::string cur_line;
	while (std::getline(resfile, cur_line))
	{
		plist.push_back(getpoints(cur_line)); 
	}
}

// Holds the number of pipe segments on the grid;
// Size set in setup_grid(), populated with 
// the plist in populate_grid()
std::vector < std::vector <int> > grid;


void print_grid(int until_x, int until_y)
{
	for (int y = 0; y < until_y; y++)
	{
		for (int x = 0; x < until_x; x++)
		{
			if (grid[y][x] == 0)
				std::cout << ".";
			else
				std::cout << grid[y][x];
		}
		std::cout << std::endl;
	}
}

void setup_grid()
{
	// Basically obsolete, I found out that the
	// sizes don't go over 1000, but now I have it
	 
	int longest_x = 0, longest_y = 0;
	int safe_margin = 5;
	for (int i = 0; i < plist.size(); i++)
	{
		if (plist[i].end.x > longest_x)
			longest_x = plist[i].end.x;
		if (plist[i].end.y > longest_y)
			longest_y = plist[i].end.y;
	}
	std::cout << "Longest x: " << longest_x << "; Longest y: " << longest_y << std::endl;
	for (int y = 0; y <= longest_y + safe_margin; y++)
	{
		grid.push_back(std::vector <int>());
		for (int x = 0; x <= longest_x + safe_margin; x++)
			grid[grid.size() -1].push_back(0);
	}
	std::cout << "grid is the y coord, grid[n] the x coord" << std::endl;
	std::cout << "grid.size: " << grid.size() << "; grid[0].size: " << grid[0].size() << std::endl;
}

void populate_grid()
{
	for (int pentry = 0; pentry < plist.size(); pentry++)
	{
		// Write vertical pipes
		if (plist[pentry].begin.x == plist[pentry].end.x)
		{
			if (plist[pentry].begin.y < plist[pentry].end.y)
			{
				for (int ycord = plist[pentry].begin.y; ycord <= plist[pentry].end.y; ycord++)
					grid[ycord][plist[pentry].begin.x] += 1;
			}
			else
			{
				for (int ycord = plist[pentry].begin.y; ycord >= plist[pentry].end.y; ycord--)
					grid[ycord][plist[pentry].begin.x] += 1;
			}
		}
		// Write horizontal pipes
		else if (plist[pentry].begin.y == plist[pentry].end.y)
		{
			if (plist[pentry].begin.x < plist[pentry].end.x)
			{
				for (int xcord = plist[pentry].begin.x; xcord <= plist[pentry].end.x; xcord++)
					grid[plist[pentry].begin.y][xcord] += 1;
			}
			else
			{
				for (int xcord = plist[pentry].begin.x; xcord >= plist[pentry].end.x; xcord--)
					grid[plist[pentry].begin.y][xcord] += 1;
			}
		}
		else
		{
			// Pipe runs diagonal, do part 2 shit
			int xcord = plist[pentry].begin.x;
			int ycord = plist[pentry].begin.y;
			if (plist[pentry].begin.x < plist[pentry].end.x
					&& plist[pentry].begin.y < plist[pentry].end.y)
			{
				while (xcord <= plist[pentry].end.x && ycord <= plist[pentry].end.y)
				{
					grid[ycord][xcord] += 1;
					xcord++;
					ycord++;
				}
			}
			else if (plist[pentry].begin.x > plist[pentry].end.x
					&& plist[pentry].begin.y > plist[pentry].end.y)
			{
				while (xcord >= plist[pentry].end.x && ycord >= plist[pentry].end.y)
				{
					grid[ycord][xcord] += 1;
					xcord--;
					ycord--;
				}
			}
			else if (plist[pentry].begin.x > plist[pentry].end.x
					&& plist[pentry].begin.y < plist[pentry].end.y)
			{
				while (xcord >= plist[pentry].end.x && ycord <= plist[pentry].end.y)
				{
					grid[ycord][xcord] += 1;
					xcord--;
					ycord++;
				}
			}
			else if (plist[pentry].begin.x < plist[pentry].end.x
					&& plist[pentry].begin.y > plist[pentry].end.y)
			{
				while (xcord <= plist[pentry].end.x && ycord >= plist[pentry].end.y)
				{
					grid[ycord][xcord] += 1;
					xcord++;
					ycord--;
				}
			}
		}
	}
}

// Gets the occurrences of all numbers in the grid
std::vector <int> find_occurrences()
{
	std::vector <int> out_occur;
	for (int y = 0; y<grid.size(); y++)
	{
		for (int x = 0; x<grid[y].size(); x++)
		{
			while (out_occur.size() <= grid[y][x])
				out_occur.push_back(0);
			out_occur[grid[y][x]]++;
		}
	}
	return out_occur;
}

int main()
{
	get_input();
	/*
	for (int i = 0; i<plist.size(); i++)
	{
		std::cout << "Pipe " << i << ":" << std::endl;
		print_pipe(plist[i]);
	}
	*/
	setup_grid();
	populate_grid();
	print_grid(475, grid.size());
	std::vector <int> occurrences = find_occurrences();
	for (int i = 0; i<occurrences.size(); i++)
		std::cout << "Occurrence[" << i << "]: " << occurrences[i] << std::endl;
}
