#include <iostream>
#include <fstream>
#include <vector>

std::string resloc = "input.txt";
std::vector <std::string> bits;

void print_bits()
{
	for (int i = 0; i<bits.size(); i++)
	{
		for (int j = 0; j<bits[i].size(); j++)
			std::cout << bits[i][j];
		std::cout << std::endl;
	}
}

void print_stringvec(std::vector<std::string> str)
{
	for (int i = 0; i<str.size(); i++)
		std::cout << i << ": " << str[i] << std::endl;
}

void get_input()
{
	std::ifstream resfile(resloc);
	std::string cur_line;
	while (getline(resfile, cur_line))
	{
		bits.push_back(cur_line);
	}
}

char get_common_bit(std::string str)
{
	int zeros = 0, ones = 0;
	for (int i = 0; i<str.size(); i++)
	{
		if (str[i] == '0')
			zeros++;
		else if (str[i] == '1')
			ones++;
		else
			std::cout << "get_common_bit: Error, Invalid character in string" << std::endl;
	}
	if (zeros > ones)
		return '0';
	else if (ones > zeros)
		return '1';
	else
		return '-';
}

std::vector <std::string> extract_numbers (int pos, char decider, 
		std::vector <std::string> to_extract)
{
	for (int i = 0; i<to_extract.size(); i++)
	{
		if (to_extract[i][pos] != decider)
		{
			to_extract.erase(to_extract.begin() + i);
			i--;
		}
	}
	return to_extract;
}

int bintodec(std::string str) 
{
	int val = 0;
	int temp = 1;
	int len = str.length();
	for (int i = len - 1; i >= 0; i--) 
	{
		if (str[i] == '1')
			val += temp;
		temp = temp * 2;
	}
	return val;
}

int get_oxy_rating(std::vector <std::string> alive_numbers)
{
	std::cout << "Before Oxygen Manipulation: " << std::endl;
	print_stringvec(alive_numbers);
	int pos = 0;
	while (alive_numbers.size() > 1)
	{
		std::string y_comp; // Composite of all numbers in a column
		for (int number = 0; number<alive_numbers.size(); number++)
		{
			y_comp += alive_numbers[number][pos];
		}
		char common_bit = get_common_bit(y_comp);
		if (common_bit == '-')
			common_bit = '1';
		std::cout << "Most common bit: " << common_bit << std::endl;
		alive_numbers = extract_numbers(pos, common_bit, alive_numbers);
		std::cout << "Oxygen Rating: " << std::endl;
		print_stringvec(alive_numbers);
		pos++;
	}
	return bintodec(alive_numbers[0]);
}

int get_scrubber_rating(std::vector <std::string> alive_numbers)
{
	std::cout << "Before Scrubber Manipulation: " << std::endl;
	print_stringvec(alive_numbers);
	int pos = 0;
	while (alive_numbers.size() > 1)
	{
		std::string y_comp; // Composite of all numbers in a column
		for (int number = 0; number<alive_numbers.size(); number++)
		{
			y_comp += alive_numbers[number][pos];
		}
		char common_bit = get_common_bit(y_comp);
		if (common_bit == '-')
			common_bit = '0';
		else if (common_bit == '1')
			common_bit = '0';
		else if (common_bit == '0')
			common_bit = '1';
		std::cout << "Least common bit: " << common_bit << " on position " << pos <<std::endl;
		alive_numbers = extract_numbers(pos, common_bit, alive_numbers);
		std::cout << "CO2 Scrubber Rating: " << std::endl;
		print_stringvec(alive_numbers);
		pos++;
	}
	return bintodec(alive_numbers[0]);
}


int main()
{
	get_input();
	print_bits();
	int oxy_rating = get_oxy_rating(bits);
	int scrubber_rating = get_scrubber_rating(bits);
	std::cout << "Oxy-Rating: " << oxy_rating << std::endl
			  << "CO2-Scrubber Rating: " << scrubber_rating << std::endl
			  << "\tMultiplied: " << oxy_rating * scrubber_rating << std::endl;
}
