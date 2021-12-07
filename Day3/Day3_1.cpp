#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
	std::cout << "Zeros: " << zeros << " Ones: " << ones << std::endl;
	if (zeros > ones)
		return 0;
	else if (ones > zeros)
		return 1;
	std::cout << "ERROR! ERROR! ERROR!" << std::endl;
	return 0;
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

int main()
{
	// Get the data into a vector
	std::ifstream resfile("Day3_Res.txt");
	std::string cur_line;
	while (std::getline(resfile, cur_line))
	{
		resholder.push_back(cur_line); 
	}
	
	// Get Gamma
	std::vector < bool > gamma;
	for (int i = 0; i<resholder[0].size(); i++)
	{
		gamma.push_back(find_commons(i, resholder)); 
		std::cout << "Calculated gamma bit " << i << std::endl;
	}
	// Output Gamma
	for (int i = 0; i<gamma.size(); i++)
		std::cout << gamma[i];
	std::cout << std::endl;
	int gamma_int = bintodec(gamma);
	std::cout << "Gamma as an Integer: " << gamma_int << std::endl;

	// Get Epsilon
	std::vector < bool > epsilon;
	for (int i = 0; i<resholder[0].size(); i++)
	{
		epsilon.push_back(invert(find_commons(i, resholder)));
		std::cout << "Calculated Epsilon bit " << i << "; Is a " << epsilon[epsilon.size()]
			<< std::endl;
	}
	// show epsilon shit
	for (int i = 0; i<epsilon.size(); i++)
		std::cout << epsilon[i];
	std::cout << std::endl;
	int epsilon_int = bintodec(epsilon);
	std::cout << "Epsilon as an Integer: " << epsilon_int << std::endl;

	// Multiply them
	std::cout << std::endl << "Multiplied together, they are " << gamma_int * epsilon_int << std::endl;
}
