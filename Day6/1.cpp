#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector <int> fish;

void get_input(std::string file)
{
	std::ifstream resfile(file);
	char cur_char;
	while (resfile.get(cur_char))
	{
		if (cur_char != ',' && cur_char != '\n')
			fish.push_back(int(cur_char - 48)); 
	}
	resfile.close();
}

void print_fish()
{
	for (int i = 0; i<fish.size(); i++)
	{
		std::cout << fish[i];
		if (i < fish.size() -1)
			std::cout << ",";
	}
	std::cout << std::endl;
}

std::vector <int> sim_growth (std::vector <int> gvector)
{
	for (int entry = 0; entry<gvector.size(); entry++)
		gvector[entry]--;
	for (int entry = 0; entry<gvector.size(); entry++)
	{
		if (gvector[entry] < 0)
		{
			gvector[entry] = 6;
			gvector.push_back(8);
		}
	}
	return gvector;
}

int main()
{
	get_input("input.txt");
	std::cout << "Initial State: ";
	print_fish();
	for (int days = 0; days<80; days++)
	{
		fish = sim_growth(fish);
		std::cout << "After " << days << " days, there are " << fish.size() << " fish." << std::endl;
		//print_fish();
	}
	std::cout << "Lanternfish now: " << fish.size() << std::endl;
}
