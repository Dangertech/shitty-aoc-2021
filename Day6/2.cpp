#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// TODO: Don't simulate each fish, group them by their 'time', idiote

std::vector <unsigned long long> fish(9);

void get_input(std::string file)
{
	std::ifstream resfile(file);
	char cur_char;
	while (resfile.get(cur_char))
	{
		if (cur_char != ',' && cur_char != '\n')
			fish[int(cur_char - 48)]++; 
	}
	resfile.close();
}

void print_fish()
{
	for (int i = 0; i<fish.size(); i++)
	{
		std::cout << "Fish with the 'time' of " << i << ": " << fish[i] << std::endl;
	}
	std::cout << std::endl;
}

std::vector <unsigned long long> sim_growth (std::vector <unsigned long long> gvector)
{
	// TODO: Rewrite sim_growth according to the new algo
	
	unsigned long long zero_start = gvector[0];
	 
	gvector[0] = gvector[1];
	gvector[1] = gvector[2];
	gvector[2] = gvector[3];
	gvector[3] = gvector[4];
	gvector[4] = gvector[5];
	gvector[5] = gvector[6];
	gvector[6] = gvector[7] + zero_start;
	gvector[7] = gvector[8];
	gvector[8] = zero_start;

	return gvector;
}

int main()
{
	get_input("input.txt");
	std::cout << "Initial State: " << std::endl;
	print_fish();
	
	for (int days = 0; days<300; days++)
	{
		fish = sim_growth(fish);
		std::cout << "Day " << days << ":" << std::endl;
		print_fish();
	}
	std::cout << "Lanternfish now: ";
	unsigned long long fish_count = 0;
	for (int i = 0; i<fish.size(); i++)
	{
		fish_count += fish[i];
	}
	std::cout << fish_count << std::endl;
	const unsigned long long ocean_volume = 1370000000000000000;
	std::cout.precision(50);
	std::cout << "Those fish would take a volume of " << std::fixed << 0.00018*fish_count << " cubic meters, assuming "
		<< "180 cubic centimeters per fish. Assuming a volume of 1,370,000,000,000,000,000 cubic meters "
		<< "as the world's oceans entire volume, this would be " << ((0.00018*fish_count)/ocean_volume)*100
		<< "\%." << std::endl;
	
}
