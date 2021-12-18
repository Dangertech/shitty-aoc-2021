#include <iostream>
#include <fstream>
#include <vector>

std::string resloc = "try.txt";
// The main string on which calculation will be performed on
// by just walking through it and doing stuff
// If I observed the task correctly, there is no
// need for fancy data structures or anything
std::vector<std::string> task;

void get_input()
{
	std::ifstream resfile(resloc);
	std::string cur_line;
	while (getline(resfile, cur_line))
	{
		task.push_back(cur_line);
	}
}

void print_task()
{
	for (int i = 0; i<task.size(); i++)
	{
		std::cout << "Snailfish number " << i << ":" << std::endl
			<< task[i] << std::endl << std::endl;
	}
}

// Gets something like "[4,[[5, 7], 8]]"
// Divides them into "4", "[[5, 7], 8]"
std::pair<std::string, std::string> getops(std::string str, int pos)
{
	std::pair<std::string, std::string> ops;
	bool second = false;
	int minidepth = 0;
	while (1 == 1)
	{
		if (str[pos] == ']' && minidepth == 1)
			break;
		 
		if (str[pos] == ',')
			second = true;
		else if (!second && minidepth >= 1)
			ops.first += str[pos];
		else if (second && minidepth >= 1)
			ops.second += str[pos];
		 
		if (str[pos] == '[')
		{
			minidepth++;
		}
		else if (str[pos] == ']')
			minidepth--;
		 
		pos++;
	}
	return ops;
}

bool isnumber (std::string str)
{
	if (str == "" || str == " ")
		return false;
	for (int i = 0; i<str.size(); i++)
	{
		if (isdigit(str[i]) == 0)
			return false;
	}
	return true;
}

// Explodes ONCE
// Returns true if it could explode, false if it couldn't
bool explode (std::string& str)
{
	int depth = 0;
	for (int i = 0; i<str.size(); i++)
	{
		if (str[i] == '[')
			depth++;
		else if (str[i] == ']')
			depth--;
		 
		if (depth > 4)
		{
			auto ops = getops(str, i);
			if (isnumber(ops.first) && isnumber(ops.second))
			{
				// Try to explode numbers now
				// Remove the string to be exploded
				str.erase(str.begin() + i, str.begin() + i + ops.second.size() + 4);
				//std::cout << str << std::endl;
				int pos = i;
				bool can_explode = true;
				// Move first item to the left
				while (isdigit(str[pos]) == 0)
				{
					pos--;
					if (pos < 0)
					{
						can_explode = false;
						break;
					}
				}
				if (can_explode)
				{
					int add_with = str[pos]-48;
					str.erase(str.begin() + pos);
					//std::cout << "Pos: " << pos << "; I: " << i << std::endl;
					str.insert(pos, std::to_string(add_with + std::stoi(ops.first)));
					//std::cout << str << std::endl;
					int to_place;
					if (str.find(",]") < str.size())
						to_place = str.find(",]")+1;
					else if (str.find("[,") < str.size())
						to_place = str.find("[,")+1;
					str.insert(to_place, "0");
				}
				else
					str.insert(i, "0");
				 
				// Move second item to the right
				// Set pos and i to the ] of "[7,]", for example^
				i += 2;
				pos = i;
				can_explode = true;
				while (isdigit(str[pos]) == 0)
				{
					pos++;
					if (pos > str.size())
					{
						can_explode = false;
						break;
					}
				}
				if (can_explode)
				{
					int add_with = str[pos]-48;
					str.erase(str.begin() + pos);
					str.insert(pos, std::to_string(add_with + std::stoi(ops.second)));
				}
				/*
				else
					str.insert(i, "0");
					*/
				//std::cout << str << std::endl;
				return true;
			}
		}
	}
	return false;
}

bool split(std::string& str)
{
	int numsinrow = 0;
	for (int i = 0; i<str.size(); i++)
	{
		if (isdigit(str[i]))
			numsinrow++;
		else
			numsinrow = 0;
		
		if (numsinrow >= 2)
		{
			// Split dat shit
			//
			// Create the combi to split to
			i -= numsinrow-1;
			std::string strnum;
			for (int j = 0; j<numsinrow; j++)
				strnum += str[i+j];
			int num = std::stoi(strnum);
			int num_one = num/2, num_two = num - num_one;
			std::cout << "First: " << num_one << ", second: " << num_two << std::endl;
			std::string combi = "[" + std::to_string(num_one) + "," + std::to_string(num_two) + "]";
			 
			// Erase and fill in
			str.erase(str.begin() + i, str.begin() + i + numsinrow);
			str.insert(i, combi);
			return true;
		}
	}
	return false;
}

std::string add(std::string a_one, std::string a_two)
{
	std::string added;
	// Just smush them together in a new pair
	added = '[' + a_one + ',' + a_two + ']';
	std::cout << "Naively added: " << added << std::endl
		<< "Refactoring through reduction; " << std::endl;
	while (explode(added))
	{
		std::cout << "Exploded something; String is now: " << std::endl
			<< added << std::endl;
		if (split(added) == true)
			std::cout << "Split something; String is now: " << std::endl
			<< added << std::endl;
	}
	return added;
}

int main()
{
	get_input();
	print_task();
	/*
	std::string test = "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]";
	explode (test);
	std::cout << test << std::endl;
	*/
	std::string added = task[0];
	for (int i = 1; i<task.size(); i++)
	{
		added = add(added, task[i]);
	}
	std::cout << "This is the final snailtask: " << std::endl << added << std::endl;
}
