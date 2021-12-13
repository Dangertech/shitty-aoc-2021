#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

std::string resloc = "try.txt";


struct cave
{
	std::string name;
	bool big = false;
	std::vector <std::string> links;
};



std::vector <cave> all_caves; // Every cave, listed by it's
// first appearance in the input file

void print_system()
{
	
	for (int node = 0; node<all_caves.size(); node++)
	{
		std::cout << "Name: " << all_caves[node].name << std::endl
				  << "Big : " << all_caves[node].big << std::endl;
		std::cout << "This cave has links to the following caves: " << std::endl;
		for (int link = 0; link<all_caves[node].links.size(); link++)
		{
			std::cout << "\t" << "> " << all_caves[node].links[link] << std::endl;
		}
		std::cout << std::endl;
	}
	
}

// Find cave By Name
int fbn(std::string cave_name)
{
	for (int i = 0; i<all_caves.size(); i++)
	{
		if (all_caves[i].name == cave_name)
			return i;
	}
	std::cout << "ERROR! NAME: " << cave_name << " NOT FOUND, RETURNING -1!!!" << std::endl;
	return -1;
}

bool check_upper(std::string str)
{
	if (str[0] >= 'A' && str[0] <= 'Z')
		return true;
	else if (str[0] >= 'a' && str[0] <= 'z')
		return false;
	std::cout << "ERROR! STRING IS NOT A NAME!" << std::endl;
	return false;
}

void get_input()
{
	std::ifstream resfile(resloc);
	std::string cur_line;
	while (getline(resfile, cur_line))
	{
		std::string link_from, link_to;
		bool is_link_to = false;
		for (int i = 0; i<cur_line.size(); i++)
		{
			if (cur_line[i] == '-')
				is_link_to = true;
			else
			{
				if (is_link_to == false)
					link_from += cur_line[i];
				else
					link_to += cur_line[i];
			}
		}
		is_link_to = false;
		// You now have extracted the link_from and link_to
		//
		// Make sure that both caves exist in the list
		if (fbn(link_from) == -1)
		{
			cave my_cave = {link_from, check_upper(link_from), {}};
			all_caves.push_back(my_cave);
		}
		if (fbn(link_to) == -1)
		{
			cave my_cave = {link_to, check_upper(link_to), {}};
			all_caves.push_back(my_cave);
		}
		std::cout << fbn(link_to) << std::endl;
		all_caves[fbn(link_from)].links.push_back(link_to);
		all_caves[fbn(link_to)].links.push_back(link_from);
	}
}

bool intinvec(int my_int, std::vector <int> vec)
{
	for (int i = 0; i<vec.size(); i++)
	{
		if (vec[i] == my_int)
			return true;
	}
	return false;
}

bool hasbiglinks(cave my_cave)
{
	for (int i = 0; i<my_cave.links.size(); i++)
	{
		if (all_caves[fbn(my_cave.links[i])].big)
			return true;
	}
	return false;
}

int find_paths(std::vector <cave> caves)
{
	int path_num = 0;
	std::vector <int> visited_smalls;
	int i = 0;
	int link  = 0;
	int iter = 0;
	while (iter < 10)
	{
		std::cout << "Starting iteration " << iter << std::endl;
		i = fbn("start");
		while (caves[i].name != "end")
		{
			std::cout << "\t" << caves[i].name << std::endl;
			srand(time(0));
			// Loop to find the next link to move to
			link = rand() % caves[i].links.size();
			while (1 == 1)
			{
				if ( hasbiglinks(caves[ fbn(caves[i].links[link]) ]) == false 
						&& caves[fbn(caves[i].links[link])].links.size() < 2)
				{
					link = rand() % (caves[i].links.size());
					continue;
				}
				if (intinvec(fbn(caves[i].links[link]), visited_smalls))
				{
					link = rand() % (caves[i].links.size());
					continue;
				}
				else if (!caves[link].big)
				{
					std::cout << "Here" << std::endl;
					visited_smalls.push_back(link);
					break;
				}
				 
				if (caves[fbn(caves[i].links[link])].big)
					break;
				link = rand() % (caves[i].links.size());
			}
			i = fbn(caves[i].links[link]);
		}
		std::cout << "End found: " << caves[i].name << std::endl;
		visited_smalls.clear();
		iter++;
	}
	return path_num;
}

int main()
{
	get_input();
	// This works, but minitry.txt doesn't. WHY!?!?!
	/*
	cave end = {"end", 0, {}};
	cave middle = {"middle", 0, {}};
	cave start = {"start", 0, {}};
	all_caves.push_back(start);
	all_caves.push_back(middle);
	all_caves.push_back(end);
	all_caves[fbn("start")].links.push_back(&all_caves[fbn("middle")]);
	all_caves[fbn("middle")].links.push_back(&all_caves[fbn("start")]);
	all_caves[fbn("middle")].links.push_back(&all_caves[fbn("end")]);
	all_caves[fbn("end")].links.push_back(&all_caves[fbn("middle")]);
	*/
	print_system();
	int path_num = find_paths(all_caves);
	std::cout << "Number of pathes: " << path_num << std::endl;
}
