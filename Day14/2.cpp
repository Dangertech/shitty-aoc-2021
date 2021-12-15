#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

std::string resloc = "input.txt";

// The reaction rules, e.g. NV -> H
std::unordered_map <std::string, char> rules;
// All Polymer pairs in the polymer string
std::unordered_map <std::string, unsigned long> polypairs;
char first_el, last_el;

int steps = 40;

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
			first_el = cur_line[0];
			last_el = cur_line[cur_line.size()-1];
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

std::unordered_map <std::string, unsigned long> update_pairs(std::unordered_map <std::string, unsigned long> pairs)
{
	auto new_pairs = pairs;
	for (auto& ipair : pairs)
	{
		new_pairs.find(ipair.first)->second -= ipair.second;
		char middle = rules.find(ipair.first)->second;
		auto p1 = new_pairs.insert({{ipair.first[0], middle}, ipair.second});
		auto p2 = new_pairs.insert({{middle, ipair.first[1]}, ipair.second});
		if (!p1.second)
			p1.first->second += ipair.second;
		if (!p2.second)
			p2.first->second += ipair.second;
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

	std::unordered_map <char, unsigned long> frequency;
	for (const auto& ipair : polypairs)
	{
		frequency[ipair.first[0]] += ipair.second;
		frequency[ipair.first[1]] += ipair.second;
	}
	frequency[first_el]++;
	frequency[last_el]++;
	for (auto& ifreq : frequency)
	{
		frequency[ifreq.first] /= 2;
	}
	for (auto& ifreq : frequency)
		std::cout << ifreq.first << ": " << ifreq.second << std::endl;
}
