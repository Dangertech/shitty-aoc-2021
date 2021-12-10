#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

std::string resloc = "input.txt";

std::vector <std::string> navlines;

std::unordered_map<char, char> cormap
{
	{'(', ')'},
	{'[', ']'},
	{'{', '}'},
	{'<', '>'}
};

// Container for all characters that should still
// be in that line
std::vector <char> expected_brackets;

void get_input()
{
	std::ifstream resfile(resloc);
	std::string cur_line;
	while (getline(resfile, cur_line))
	{
		navlines.push_back(cur_line);
	}
}

int charin( char my_char, std::vector <char> char_list)
{
	for (int i = 0; i<char_list.size(); i++)
	{
		if (char_list[i] == my_char)
			return i;
	}
	return -1;
}

char get_falsechars (std::string instr)
{
	std::vector <char> next_closer;
	int depth = 0;
	for (int i = 0; i<instr.size(); i++)
	{
		if (charin(instr[i], {'(', '[', '{', '<'}) != -1)
		{
				depth++;
				next_closer.push_back(cormap[instr[i]]);
		}


		if (charin(instr[i], {')', ']', '}', '>'}) != -1)
		{
			if (instr[i] == next_closer[next_closer.size()-1])
				next_closer.erase(next_closer.end()-1);
			else
				return instr[i];
		}
	}
	return 0;
	// Oops, did I do it for "incomplete" lines?
	/*
	for (int i = 0; i<instr.size(); i++)
	{
		if (instr[i] == '(')
			expected_brackets.push_back(')');
		else if (instr[i] == '[')
			expected_brackets.push_back(']');
		else if (instr[i] == '{')
			expected_brackets.push_back('}');
		else if (instr[i] == '<')
			expected_brackets.push_back('>');
		 
		int check_char = charin(instr[i], expected_brackets);
		if (check_char != -1)
			expected_brackets.erase(expected_brackets.begin() + check_char);
	}
	if (expected_brackets.size() != 0)
		return expected_brackets[0];
	return 0;
	*/
}

int main()
{
	get_input();
	std::vector <char> char_collector;
	for (int i = 0; i<navlines.size(); i++)
	{
		std::cout << "Looking up line " << i << ":" << std::endl
				  << navlines[i] << std::endl;
		char incorrect_char = get_falsechars(navlines[i]);
		if (incorrect_char != 0)
		{
			std::cout << "\033[31m" << incorrect_char << " is invalid!" << "\033[0m" << std::endl;
			char_collector.push_back(incorrect_char);
		}
	}

	std::cout << "All wrong chars: " << std::endl;
	int syntax_points = 0;
	for (int i = 0; i<char_collector.size(); i++)
	{
		std::cout << "\033[31m" << char_collector[i];
		if (char_collector[i] == ')')
			syntax_points += 3;
		else if (char_collector[i] == ']')
			syntax_points += 57;
		else if (char_collector[i] == '}')
			syntax_points += 1197;
		else if (char_collector[i] == '>')
			syntax_points += 25137;
	}
	std::cout << "\033[0m" << std::endl
		<< "Total syntax error points: " << syntax_points << std::endl;
}
