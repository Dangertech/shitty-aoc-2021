#include<fstream>
#include<iostream>
#include<vector>

int increases = 0;

int main()
{
	std::ifstream resfile("Day1_1_Res.txt");
	std::string cur_line;
	std::vector < int > tmsw;
	int cur_int = 0, calcs = 0;
	int cur_result = 0, last_result = 0;
	while (std::getline(resfile, cur_line))
	{
		int cur_int = stoi(cur_line);
		tmsw.push_back(cur_int);
		if (tmsw.size() == 3)
		{
			cur_result = tmsw[0] + tmsw[1] + tmsw[2];
			std::cout << "TMSW: " << tmsw[0] << "; " << tmsw[1] << "; " << tmsw[2] << std::endl;
			std::cout << "Result: " << cur_result << std::endl;
			tmsw.erase(tmsw.begin());
		}
		std::cout << last_result << std::endl;
		if (last_result < cur_result && calcs > 2)
		{
			increases++;
			std::cout << "(Increased)" << std::endl;
		}
		else
			std::cout << "(Decreased/Stagnates)" << std::endl;
		last_result = cur_result;
		calcs++;
	}
	std::cout << increases << std::endl;
	return 0;
}
