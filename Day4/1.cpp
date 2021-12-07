#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

struct bingo_num
{
	int number;
	bool drawn = false;
};

std::vector <int> call_numbers;
std::vector < std::vector < std::vector < bingo_num > > > tables;



std::vector <int> str_vecint(std::string my_str, char sep_char)
{
	// Gets something like '12 75 58 21 87'
	std::vector <int> out_vector;
	std::string strnum;
	int pos = 0;
	while (pos < my_str.size())
	{
		while (my_str[pos] != sep_char && pos < my_str.size())
		{
			strnum += my_str[pos]; 
			pos++;
		}
		//std::cout << "strnum: " << strnum << "!" << std::endl;
		if (!strnum.empty())
		{
			out_vector.push_back(std::stoi(strnum));
			strnum = "";
		}
		pos++;
	}
	return out_vector;
}

std::vector <bingo_num> str_bingo_num(std::string my_str, char sep_char)
{
	// Gets something like '12 75 58 21 87'
	std::vector <bingo_num> out_vector;
	std::string strnum;
	int pos = 0;
	while (pos < my_str.size())
	{
		while (my_str[pos] != sep_char && pos < my_str.size())
		{
			strnum += my_str[pos]; 
			pos++;
		}
		std::cout << "strnum: " << strnum << "!" << std::endl;
		if (!strnum.empty())
		{
			bingo_num bin = {std::stoi(strnum), false};
			out_vector.push_back(bin);
			strnum = "";
		}
		pos++;
	}
	return out_vector;
}

void print_call_numbers()
{
	for (int i = 0; i<call_numbers.size(); i++)
	{
		std::cout << call_numbers[i] << " ";
	}
	std::cout << std::endl;
}

void print_tables(int to_show = 666)
{
	if (to_show == 666)
	{
		for (int i = 0; i<tables.size(); i++)
		{
			std::cout << "Table " << i << std::endl;
			for (int j=0; j<tables[i].size(); j++)
			{
				for (int k=0; k<tables[i][j].size(); k++)
					std::cout << tables[i][j][k].number << "," << tables[i][j][k].drawn << " ";
				std::cout <<std::endl;
			}
			std::cout << std::endl <<  std::endl;
		}
	}
	else
	{
		std::cout << "Table " << to_show << std::endl;
			for (int j=0; j<tables[to_show].size(); j++)
			{
				for (int k=0; k<tables[to_show][j].size(); k++)
					std::cout << tables[to_show][j][k].number 
						<< "," << tables[to_show][j][k].drawn << " ";
				std::cout <<std::endl;
			}
			std::cout << std::endl <<  std::endl;
	}
}

void get_data(bool show_dbg = false)
{
	std::ifstream resfile("Input.txt");
	std::string cur_line;
	int line = 0;
	while (std::getline(resfile, cur_line))
	{
		if (show_dbg)
			std::cout << "Loop" << std::endl;
		line++;
		if (line == 1)
			call_numbers = str_vecint(cur_line, ','); 
		else
		{
			if ((line -2)% 6 == 0)
			{
				tables.push_back(std::vector < std::vector <bingo_num> >());
				if (show_dbg)
					std::cout << "Creating new table on line " << line << std::endl;
			}
			else
			{
				if (show_dbg)
					std::cout << "Line: " << line << std::endl;
				tables[tables.size()-1].push_back(str_bingo_num(cur_line, ' '));
			}
		}
	}
	resfile.close();
}

std::vector <int> check_tables()
{
	std::vector <int> bingo_tables;
	for (int table = 0; table < tables.size(); table++)
	{
		for (int row = 0; row < tables[table].size(); row++)
		{
			int item = 0;
			for (item = 0; item < tables[0][0].size(); item++)
			{
				if (tables[table][row][item].drawn == false)
				{
					break;
				}
			}
			if (item == 5)
				bingo_tables.push_back(table); 
		}
		for (int item = 0; item < 5; item++)
		{
			int row = 0;
			for (row = 0; row < 5; row++)
			{
				if (tables[table][row][item].drawn)
					continue;
				else
				{ 
					break;
				}
			}
			if (row == 5)
				bingo_tables.push_back(table);
		}
	}
	return bingo_tables;
}

int main()
{
	/*std::vector <int> test = str_vecint("12 75 58 21 7\n");
	for (int i = 0; i<test.size(); i++)
		std::cout << "Entry " << i << ": " << test[i] << std::endl;
	*/
	
	get_data();
	print_call_numbers();
	 
	int completed_table = 0;
	int win_num = 0;
	std::cout << "Doing shit: " << std::endl;
	// Draw all numbers
	for (int drawn_num=0; drawn_num < call_numbers.size(); drawn_num++)
	{
		for (int table=0; table < tables.size(); table++)
		{
			for (int row=0; row < tables[table].size(); row++)
			{
				for (int item=0; item < tables[table][row].size(); item++)
				{
					//std::cout << tables[table][row][item].number << " = " << call_numbers[drawn_num] << std::endl;
					if (tables[table][row][item].number == call_numbers[drawn_num])
						tables[table][row][item].drawn = true;
				}
			}
		}
		auto bingo_tables = check_tables();
		if (bingo_tables.size() > 0)
		{
			std::cout << "Table " << bingo_tables[0] << " found ready on recursion " << drawn_num << std::endl;
			print_tables(bingo_tables[0]);
			win_num = call_numbers[drawn_num];
			completed_table = bingo_tables[0];
			break;
		}
	}

	int unm_sum = 0;
	for (int i = 0; i<tables[completed_table].size(); i++)
	{
		for (int j = 0; j<tables[completed_table][i].size(); j++)
		{
			if (tables[completed_table][i][j].drawn == false)
				unm_sum += tables[completed_table][i][j].number;
		}
	}
	std::cout << "Unmarked sum: " << unm_sum << std::endl;
	std::cout << "Winning number: " << win_num << std::endl;
	return 0;
}
