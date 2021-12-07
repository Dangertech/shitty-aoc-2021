#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector <int> in_pos;

void get_input()
{
	std::ifstream resfile("input.txt");
	std::string cur_num;
	char cur_char;
	while (resfile.get(cur_char))
	{
		if (cur_char == ',' || cur_char == '\n')
		{
			in_pos.push_back(stoi(cur_num)); 
			cur_num = "";
		}
		else
		{
			cur_num += cur_char;
		}
	}
}

void print_intvec(std::vector <int> my_vec)
{
	for (int i=0; i<my_vec.size(); i++)
		std::cout << my_vec[i] << ",";
	std::cout << std::endl;
}

std::vector <int> calc_fuelcost(std::vector<int> in_pos, int endpoint)
{
	std::vector <int> cost;
	for (int i=0; i<in_pos.size(); i++)
	{
		if (in_pos[i] > endpoint)
			cost.push_back(in_pos[i] - endpoint);
		else if (in_pos[i] < endpoint)
			cost.push_back(endpoint - in_pos[i]);
		else if (in_pos[i] == endpoint)
			cost.push_back(0);
	}
	return cost;
}

int main()
{
	get_input();
	std::cout << "Initial Crab positions:" << std::endl;
	print_intvec(in_pos);
	std::cout << std::endl << std::endl;

	// Get the Median
	std::sort(in_pos.begin(), in_pos.end());
	print_intvec(in_pos);
	int average = in_pos[in_pos.size()/2];
	std::cout << "Median: " << average << std::endl;

	std::vector <int> fuel_costs = calc_fuelcost(in_pos, average);
	print_intvec(fuel_costs);
	int combined_costs = 0;
	for (int i=0; i<fuel_costs.size(); i++)
		combined_costs += fuel_costs[i]; 
	std::cout << "Combined fuel costs: " << combined_costs << std::endl;
}
