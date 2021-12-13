#include <iostream>
#include <fstream>
#include <vector>

std::string resloc = "input.txt";

int y_size = 895, x_size = 1311;
std::vector < std::vector<bool> > dots(y_size, std::vector<bool> (x_size, false));

void print_dots()
{
	for (int y = 0; y<dots.size(); y++)
	{
		for (int x = 0; x<dots[y].size(); x++)
		{
			if (dots[y][x])
				std::cout << "#";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}
}


struct instruction
{
	char dir;
	int loc;
};
std::vector <instruction> list;

void print_list()
{
	for (int i = 0; i<list.size(); i++)
		std::cout << list[i].dir << "=" << list[i].loc << std::endl;;
}

void get_input()
{
	int biggest_y = 0, biggest_x = 0;
	std::ifstream resfile(resloc);
	std::string cur_line;
	bool instructions = false;
	while (getline(resfile, cur_line))
	{
		if (cur_line == "")
			instructions = true;
		else if (!instructions)
		{
			bool x = true;
			std::string y_str, x_str;
			for (int i = 0; i<cur_line.size(); i++)
			{
				if (cur_line[i] == ',')
					x = false;
				else if (!x)
					y_str += cur_line[i];
				else if (x)
					x_str += cur_line[i];
			}
			int y_coord = stoi(y_str), x_coord = stoi(x_str); 
			if (y_coord > biggest_y)
				biggest_y = y_coord;
			if (x_coord > biggest_x)
				biggest_x = x_coord;
			dots[y_coord][x_coord] = true;
		}
		else
		{
			char dir;
			bool collect_loc = false;
			std::string loc_str;
			for (int i = 0; i<cur_line.size(); i++)
			{
				if (cur_line[i] == '=')
				{
					dir = cur_line[i-1];
					collect_loc = true;
				}
				else if (collect_loc)
					loc_str += cur_line[i];
			}
			int loc = stoi(loc_str);
			list.push_back({dir, loc});
		}
	}
	std::cout << biggest_y << ", "  << biggest_x << std::endl;
	resfile.close();
}

void fold(char dir, int loc)
{
	if (dir == 'y')
	{
		for (int y = loc; y<dots.size(); y++)
		{
			for (int x = 0; x<dots[y].size(); x++)
			{
				if (dots[y][x])
				{
					int new_y = loc - (y-loc);
					dots[new_y][x] = true;
					dots[y][x] = false;
				}
			}
		}
	}
	else if (dir == 'x')
	{
		for (int y = 0; y<dots.size(); y++)
		{
			for (int x = loc; x<dots[y].size(); x++)
			{
				if (dots[y][x])
				{
					int new_x = loc - (x-loc);
					dots[y][new_x] = true;
					//std::cout << "Y: " << y << "; X: " << x << " folded to " << y << "; " << new_x << std::endl;
					dots[y][x] = false;
				}
			}
		}
	}
}

int count_dots()
{
	int my_dots = 0;
	for (int y = 0; y<dots.size(); y++)
	{
		for (int x = 0; x<dots[y].size(); x++)
		{
			if (dots[y][x])
				my_dots++;
		}
	}
	return my_dots;
}

int main()
{

	get_input();
	//print_dots();
	print_list();
	for (int i = 0; i<list.size(); i++)
		fold(list[i].dir, list[i].loc);
	int all_dots = count_dots();
	std::cout << all_dots << std::endl;
	// Print the dots in smaller (I figured these values out by hand)
	// I'm cheating, I know
	for (int y = 0; y<6; y++)
	{
		for (int x = 0; x<39; x++)
		{
			if (dots[y][x])
				std::cout << "#";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}
}
