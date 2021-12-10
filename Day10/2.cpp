#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>

// Big list of includes today

std::string resloc = "input.txt";

std::vector <std::string> navlines;

std::unordered_map<char, char> cormap
{
	{'(', ')'},
	{'[', ']'},
	{'{', '}'},
	{'<', '>'}
};

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

char get_corruptchars (std::string instr)
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
}

std::vector <char> get_incompchars (std::string instr)
{
	std::deque <char> next_closer;
	int depth = 0;
	for (int i = 0; i<instr.size(); i++)
	{
		if (charin(instr[i], {'(', '[', '{', '<'}) != -1)
		{
				depth++;
				next_closer.push_front(cormap[instr[i]]);
		}
		 
		int check_char = charin(instr[i], {')', ']', '}', '>'});
		if (check_char != -1)
		{
			next_closer.erase(next_closer.begin());
		}
	}
	std::vector <char> to_vector;
	for (int i = 0; i<next_closer.size(); i++)
		to_vector.push_back(next_closer[i]);
	return to_vector;
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
	std::vector < std::vector <char> > char_collector;
	for (int i = 0; i<navlines.size(); i++)
	{
		std::cout << "Looking up line " << i << ":" << std::endl
				  << navlines[i] << std::endl;
		// Use only lines that are not corrupt anyways
		if (get_corruptchars(navlines[i]) == 0)
		{
			std::vector <char> incorrect_chars = get_incompchars(navlines[i]);
			if (incorrect_chars.size() > 0)
			{
				std::cout << "\033[31mReceived incomplete string, can be completed by: " << std::endl;
				for (int j = 0; j<incorrect_chars.size(); j++)
				{
					std::cout << "\033[31m" << incorrect_chars[j] << "\033[0m";
				}
				char_collector.push_back(incorrect_chars);
				std::cout << std::endl;
			}
		}
	}

	std::cout << std::endl << "All wrong chars: " << std::endl;
	std::vector <long> score_collector;
	for (int i = 0; i<char_collector.size(); i++)
	{
		long score = 0;
		for (int j = 0; j<char_collector[i].size(); j++)
		{
			score *= 5;
			std::cout << "\033[31m" << char_collector[i][j];
			if (char_collector[i][j] == ')')
				score += 1;
			else if (char_collector[i][j] == ']')
				score += 2;
			else if (char_collector[i][j] == '}')
				score += 3;
			else if (char_collector[i][j] == '>')
				score += 4;
		}
		std::cout << std::endl <<  "Score for wrong line " << i << ": " << score << std::endl;
		score_collector.push_back(score);
	}

	std::sort(score_collector.begin(), score_collector.end());
	std::cout << "Middle score is: " << score_collector[score_collector.size()/2] << std::endl;
}
