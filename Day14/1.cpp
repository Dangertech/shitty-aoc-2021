//
//
///// NAIVE SOLUTION, NOT VIABLE FOR MORE THAN 15 STEPS
//
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

std::string resloc = "input.txt";
std::string polymer;
std::unordered_map <std::string, char> rules;

int steps = 40;

void print_rules()
{
	for (const auto& i : rules)
		std::cout << i.first << " -> " << i.second << std::endl;
}

// Fills polymer and rules
void get_input()
{
	std::ifstream resfile(resloc);
	std::string cur_line;
	int line = 1;
	while (getline(resfile, cur_line))
	{
		if (line == 1)
			polymer = cur_line;
		else if (line >= 3)
		{
			std::string ref;
			char inserted;
			bool gives_inserter = false;
			for (int i = 0; i<cur_line.size(); i++)
			{
				if (cur_line[i] == '-' || cur_line[i] == '>' || cur_line[i] == ' ')
					gives_inserter = true;
				else if (gives_inserter == false)
					ref += cur_line[i];
				else
					inserted = cur_line[i];
			}
			rules[ref] = inserted;
		}
		line++;
	}
}

int find_pair_loc(char first_part, char second_part, std::string str)
{
	for (int i = 0; i<str.size(); i++)
	{
		if (str[i] == first_part && str[i+1] == second_part)
			return i+1;
	}
	std::cout << "find_pair_loc: ERROR PAIR COULD NOT BE FOUND" << std::endl;
	return 0;
}

std::string insert_polymer(std::string reference)
{
	std::string updater = reference;
	int times_updated = 0;
	// For every character in references
	for (int my_char = 0; my_char < reference.size(); my_char++)
	{
		// Check every rule with this character and the next one
		for (const auto& my_rule : rules)
		{
			// std::string() is needed to stop making the compiler think that integers are added
			std::string to_compare = std::string() + reference[my_char] + reference[my_char+1];
			if (to_compare == my_rule.first)
			{
				// Exclude the already searched chars from the find_pair_loc() search
				updater.insert(my_char+1+times_updated, &my_rule.second);
				times_updated++;
				continue;
			}
		}
	}
	return updater;
}

int main()
{
	get_input();
	print_rules();
	std::cout << "Polymer before insertions: " << std::endl
		<< polymer << std::endl;
	for (int i = 0; i<steps; i++)
	{
		std::cout << "Step: " << i << std::endl;
		polymer = insert_polymer(polymer);
		std::cout << "After step " << i << std::endl
			<< polymer << std::endl;
	}

	// Calculate polymer solution
	std::unordered_map<char, int> map;
	for (int i = 0; i<polymer.size(); i++)
	{
		if (map.find(polymer[i]) == map.end())
				map.insert(std::make_pair(polymer[i], 1));
		else
			map[polymer[i]]++;
	}
	for (auto& my_freq : map)
	{
		std::cout << my_freq.first << ": " << my_freq.second << std::endl;
	}
}
