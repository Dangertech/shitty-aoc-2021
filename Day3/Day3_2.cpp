#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>
#include <cmath>

// Container of the input
std::vector < std::string > resholder;

bool find_commons(int pos, std::vector < std::string > com_str)
{
	int zeros = 0, ones = 0;
	for (long unsigned int i = 0; i<com_str.size(); i++)
	{
		char cur_bin = com_str[i][pos];
		if (cur_bin == '0')
			zeros++;
		else if (cur_bin == '1')
			ones++;
	}
	//std::cout << "Zeros: " << zeros << " Ones: " << ones << std::endl;
	if (zeros > ones)
		return 0;
	else if (ones > zeros)
		return 1;
	std::cout << "ERROR! ERROR! ERROR!" << std::endl;
	return 0;
}

bool find_bool_commons(int pos, std::vector < std::vector < bool > > com_str)
{
	int zeros = 0, ones = 0;
	for (long unsigned int i = 0; i<com_str.size(); i++)
	{
		char cur_bin = com_str[i][pos];
		if (cur_bin == 0)
			zeros++;
		else if (cur_bin == 1)
			ones++;
	}
	std::cout << "Zeros: " << zeros << " Ones: " << ones << std::endl;
	if (zeros > ones)
		return 0;
	else if (ones > zeros)
		return 1;
	std::cout << "They are equally as common, giving one!" << std::endl;
	return 1;
}

int bintodec(std::vector <bool> bin)
{
	int dec = 0;
	int down_from = bin.size() - 1;
	for (int i = 0; i<bin.size(); i++)
	{
		dec += bin[i] * pow(2, down_from);
		down_from--;
	}
	return dec;
}

bool invert(bool to_invert)
{
	if (to_invert == false)
		return true;
	else
		return false;
}

std::vector <bool> str_to_boolvec( std::string boolstr)
{
	std::vector <bool> out_bool;
	for (int i=0; i < boolstr.size(); i++)
	{
		if (boolstr[i] == '0')
			out_bool.push_back(0);
		else if (boolstr[i] == '1')
			out_bool.push_back(1);
	}
	return out_bool;
}

std::vector < bool > commons;
std::vector < std::vector < bool > > chosen_bits;
std::vector < std::vector < bool > > cotwo_bits;

void print_chosen_bits()
{
	for (int num = 0; num<cotwo_bits.size(); num++)
	{
		std::cout << "CO2 bit " << num << ": ";
		for (int sub = 0; sub<cotwo_bits[num].size(); sub++)
		{
			std::cout << cotwo_bits[num][sub];
		}
		std::cout << std::endl;
	}
}

int main()
{
	// Get the data into a vector
	std::ifstream resfile("Day3_Res.txt");
	std::string cur_line;
	while (std::getline(resfile, cur_line))
	{
		resholder.push_back(cur_line); 
	}
	
	// Push everythinng into both vectors
	for (int i = 0; i<resholder.size(); i++)
	{
		chosen_bits.push_back(str_to_boolvec(resholder[i]));
		cotwo_bits.push_back(str_to_boolvec(resholder[i]));
	}
	
	 
	bool test_chosen = true, test_cotwo = true;
	// Reiterate through the chosen bits
	for (int col = 0; col<resholder[0].size(); col++)
	{
		bool most_common = find_bool_commons(col, chosen_bits);
		std::cout << "Calculating column " << col << ", most common bit is " << most_common << std::endl;
		if (test_chosen)
		{
			for (int i = 0; i<chosen_bits.size(); i++)
			{
				if (chosen_bits[i][col] != most_common)
				{
					chosen_bits.erase(chosen_bits.begin() + i); 
					i = 0;
				}
			}
		}
		if (test_cotwo)
		{
			for (int i= 0; i<cotwo_bits.size(); i++)
			{
				if (cotwo_bits[i][col] == most_common)
				{
					cotwo_bits.erase(cotwo_bits.begin() + i);
					i = 0;
				}
			}
		}
		if (chosen_bits.size() < 2)
			test_chosen = false;
		if (cotwo_bits.size() < 2)
			test_cotwo = false;
		print_chosen_bits();
	}
	print_chosen_bits();
	 
	std::vector < bool > oxygen_generator_rating = chosen_bits[0]; 
	std::vector < bool > cotwo_scrubber_rating = cotwo_bits[0];

	std::cout << "Oxygen generator rating: " << std::endl;
	for (int i = 0; i<oxygen_generator_rating.size(); i++)
		std::cout << oxygen_generator_rating[i];
	std::cout << std::endl;
	 
	std::cout << "CO2 scrubber rating: " << std::endl;
	for (int i = 0; i<cotwo_scrubber_rating.size(); i++)
		std::cout << cotwo_scrubber_rating[i];
	std::cout << std::endl;
	 
	std::cout << bintodec(oxygen_generator_rating) * bintodec(cotwo_scrubber_rating) << std::endl;
}
