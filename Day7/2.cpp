#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

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
	{
		std::cout << my_vec[i];
		if (i < my_vec.size() -1)
			std::cout << ",";
	}
	std::cout << std::endl;
}

std::vector <int> calc_fuelcost(std::vector<int> in_pos, int endpoint)
{
	std::vector <int> cost;
	for (int i=0; i<in_pos.size(); i++)
	{
		int standard_cost=0;
		if (in_pos[i] > endpoint)
			//cost.push_back(in_pos[i] - endpoint);
			standard_cost = in_pos[i] - endpoint;
		else if (in_pos[i] < endpoint)
			//cost.push_back(endpoint - in_pos[i]);
			standard_cost = endpoint - in_pos[i];
		// https://en.wikipedia.org/wiki/Arithmetic_progression
		// I don't really understand it, but it works
		// Gauss was a cool guy
		cost.push_back((standard_cost * (standard_cost+1))/2);
	}
	return cost;
}

int main()
{
	// Get the input
	get_input();
	std::cout << "Initial Crab positions:" << std::endl;
	print_intvec(in_pos);
	std::cout << std::endl << std::endl;

	// Get the Mean
	int combined_values = 0;
	for (int i = 0; i<in_pos.size(); i++)
		combined_values += in_pos[i];
	float average = float(combined_values)/float(in_pos.size());
	std::cout << "Mean: " << average << std::endl;
	// Rounding is not possible, I have to check both the lower and the higher integer
	int i_avg = round(average);

	std::vector <int> fuel_costs = calc_fuelcost(in_pos, i_avg);
	print_intvec(fuel_costs);
	int combined_costs = 0;
	for (int i=0; i<fuel_costs.size(); i++)
		combined_costs += fuel_costs[i]; 
	std::cout << "Combined fuel costs: " << combined_costs << std::endl;
}
