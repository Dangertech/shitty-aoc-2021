#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

std::string resloc = "input.txt";

std::vector < std::vector < std::string > > output_vals;
std::vector < std::vector < std::string > > signals;



void cut_segments(std::string my_str)
{
	std::vector <std::string> my_output_vals;
	std::vector <std::string> my_signals;
	std::string cur_combo;
	bool sec_part = false;
	for (int i = 0; i<my_str.size(); i++)
	{
		if (my_str[i] == '|')
		{
			sec_part = true;
			my_signals.push_back(cur_combo);
			cur_combo = "";
		}
		else if (my_str[i] == ' ' && cur_combo != "")
		{
			if (!sec_part)
				my_signals.push_back(cur_combo);
			else
				my_output_vals.push_back(cur_combo);
			cur_combo = "";
		}
		else if (my_str[i] != ' ')
			cur_combo += my_str[i];
	}
	// Push back the last combo that wasn't registered
	// by the if statement
	my_output_vals.push_back(cur_combo);
	output_vals.push_back(my_output_vals);
	signals.push_back(my_signals);
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

int contains (std::string to_comp, std::string chars)
{
	int containers = 0;
	for (int i = 0; i<to_comp.size(); i++)
	{
		for (int j = 0; j<chars.size(); j++)
		{
			if (to_comp[i] == chars[j])
				containers ++;
		}
	}
	return containers;
}

// Returns true only if the strings are an exact mixed combination 
// of each other
bool iscombo (std::string to_comp, std::string combo)
{
	if (to_comp.size() != combo.size())
		return false;
	 
	for (int i = 0; i<to_comp.size(); i++)
	{
		bool has_match = false;
		for (int j=0; j<combo.size(); j++)
		{
			if (to_comp[i] == combo[j])
				has_match = true;
		}
		if (has_match == false)
			return false;
	}
	return true;
}

int main()
{
	get_input();
	print_dvector(output_vals);
	print_dvector(signals);
	//
	// Holder of all outputs added together
	int combined_outputs = 0;
	// For each separate line
	for (int puzzle = 0; puzzle < signals.size() && puzzle < output_vals.size(); puzzle++)
	{
		std::unordered_map<int, std::string> valmap
		{
			{0, "!"},
			{1, "!"},
			{2, "!"},
			{3, "!"},
			{4, "!"},
			{5, "!"},
			{6, "!"},
			{7, "!"},
			{8, "!"},
			{9, "!"}
		};
		 
		// Loop a few times to make sure that everything gets assigned
		// I know, this could be solved better, but I don't care
		for (int rep = 0; rep < 4; rep++)
		{
			// Traverse through every signal;
			for (int this_sig = 0; this_sig < signals[puzzle].size(); this_sig++)
			{
				auto test_sig = signals[puzzle][this_sig];
				if (test_sig.size() == 2)
					valmap[1] = test_sig;
				else if (test_sig.size() == 3)
					valmap[7] = test_sig;
				else if (test_sig.size() == 4)
					valmap[4] = test_sig;
				else if (test_sig.size() == 7)
					valmap[8] = test_sig;

				// Determine 0, 6 and 9 based on who contains both 1 characters
				if (test_sig.size() == 6)
				{
					if (contains(test_sig, valmap.at(1)) == 2)
					{
						// Either 0 or 9
						if (contains(test_sig, valmap.at(4)) == 4)
							valmap[9] = test_sig;
						else
							valmap[0] = test_sig;
					}
					else
						valmap[6] = test_sig;
				}

				// Determine 2, 3, and 5
				if (test_sig.size() == 5)
				{
					if (contains(test_sig, valmap.at(1)) == 2)
						valmap[3] = test_sig;
					else
					{
						// Either 2 or 5
						if (contains(test_sig, valmap.at(6)) == 5)
							valmap[5] = test_sig;
						else if (contains(test_sig, valmap.at(6)) == 4)
							valmap[2] = test_sig;
					}
				}
			}
		}
		 
		for(int i = 0; i<valmap.size(); i++)
		{
			std::cout << i << " " << valmap.at(i) << std::endl;
		}
		 
		std::string combi_str;
		// Compute out_value combination
		for (int val = 0; val < output_vals[puzzle].size(); val++)
		{
			int cor_val = 0;
			while(!iscombo(output_vals[puzzle][val], valmap.at(cor_val) ))
				cor_val++;
			combi_str += std::to_string(cor_val);
			std::cout << cor_val;
		}
		combined_outputs += stoi(combi_str);
		std::cout << std::endl << std::endl;;
	}
	std::cout << "Combined outputs: " << combined_outputs << std::endl;
}
