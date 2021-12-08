#include <iostream>
#include <fstream>
#include <vector>

std::string resloc = "input.txt";

std::vector < std::vector < std::string > > output_vals;

void cut_segments(std::string my_str)
{
	std::vector <std::string> my_output_vals;
	std::string cur_combo;
	bool sec_part = false;
	for (int i = 0; i<my_str.size(); i++)
	{
		if (my_str[i] == '|')
			sec_part = true;
		else if (sec_part && my_str[i] == ' ' && cur_combo != "")
		{
			my_output_vals.push_back(cur_combo);
			cur_combo = "";
		}
		else if (sec_part && my_str[i] != ' ')
			cur_combo += my_str[i];
	}
	// Push back the last combo that wasn't registered
	// by the if statement
	my_output_vals.push_back(cur_combo);
	output_vals.push_back(my_output_vals);
}

void get_input()
{
	std::ifstream resfile(resloc);
	std::string cur_line;
	while (getline(resfile, cur_line))
	{
		cut_segments(cur_line);
	}
}

void print_dvector(std::vector < std::vector < std::string > > my_vec)
{
	for (int i = 0; i<my_vec.size(); i++)
	{
		for (int j=0; j<my_vec[i].size(); j++)
			std::cout << my_vec[i][j] << " ";
		std::cout << std::endl;
	}
}

bool intinvec(int my_int, std::vector <int> my_vec)
{
	for (int i = 0; i<my_vec.size(); i++)
	{
		if (my_int == my_vec[i])
			return true;
	}
	return false;
}

int main()
{
	get_input();
	print_dvector(output_vals);
	
	int obv_nums = 0;
	for (int i = 0; i<output_vals.size(); i++)
	{
		for (int j=0; j<output_vals[i].size(); j++)
		{
			if (intinvec(output_vals[i][j].size(), {2, 3, 4, 7}))
				obv_nums += 1;
		}
	}
	std::cout << obv_nums << std::endl;
	
}
