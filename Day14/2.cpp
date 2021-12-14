#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

std::string resloc = "try.txt";

// The reaction rules, e.g. NV -> H
std::unordered_map <std::string, char> rules;
// All Polymer pairs in the polymer string
std::unordered_map <std::string, int> polypairs;

int steps = 4;

void print_rules()
{
	for (const auto& i : rules)
		std::cout << i.first << " -> " << i.second << std::endl;
}

void print_pairs()
{
	for (const auto& i : polypairs)
		std::cout << i.first << ": " << i.second << " times" << std::endl;
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
		{
			for (int i = 0; i<cur_line.size()-1; i++)
			{
				std::string polycombi = std::string() + cur_line[i] + cur_line[i+1];
				polypairs[polycombi]++;
			}
		}
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

std::unordered_map <std::string, int> update_pairs(std::unordered_map <std::string, int> pairs)
{
	auto new_pairs = pairs;
	// For every pair
	for (const auto& ipair : pairs)
	{
		// You go through every rule
		for (const auto& irule : rules)
		{
			// And look if the pair is the same as the reaction rule
			if (ipair.first == irule.first && ipair.second > 0)
			{
				// CB becomes CHB because of CB -> H
				// Create two composite containers
				std::string first_comp, second_comp;
				first_comp = std::string() + ipair.first[0] + irule.second;
				second_comp = std::string()+ irule.second + ipair.first[1];
				new_pairs[ipair.first]--;
				new_pairs[first_comp]++;
				new_pairs[second_comp]++;
			}
		}
	}
	return new_pairs;
}


int main()
{
	get_input();
	print_rules();
	std::cout << "Polymer before insertions: " << std::endl;
	print_pairs(); 
	for (int i = 1; i<=steps; i++)
	{
		polypairs = update_pairs(polypairs);
		std::cout << std::endl << "After step " << i << std::endl;
		print_pairs();
	}

	std::unordered_map <char, int> frequency;
	for (const auto& ipair : polypairs)
	{
		frequency[ipair.first[0]] += ipair.second;
		frequency[ipair.first[1]] += ipair.second;
	}
	for (auto& ifreq : frequency)
		std::cout << ifreq.first << ": " << ifreq.second << std::endl;
}
