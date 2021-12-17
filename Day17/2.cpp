#include <iostream>
#include <fstream>
#include <vector>

struct area
{
	int start_x, end_x;
	int start_y, end_y;
};
struct area target = {56, 76, -162, -134};
//struct area target = {20, 30, -10, -5};

bool posinarea(int x_pos, int y_pos, struct area my_area)
{
	if (x_pos >= my_area.start_x && x_pos <= my_area.end_x)
	{
		if (my_area.start_y < my_area.end_y)
		{
			if (y_pos >= my_area.start_y && y_pos <= my_area.end_y)
				return true;
			return false;
		}
		else
		{
			if (y_pos <= my_area.start_y && y_pos >= my_area.end_y)
				return true;
			return false;
		}
	}
	return false;
}

int shoot_probe(int x_vel, int y_vel)
{
	int x_pos = 0, y_pos = 0;
	int max_y = 0;
	while (!posinarea(x_pos, y_pos, target) && y_pos > target.start_y -1 && x_pos < target.end_x + 1)
	{
		if (y_pos > max_y)
			max_y = y_pos;
		std::cout << x_pos << ", " << y_pos << " not in target area" << std::endl;
		x_pos += x_vel;
		y_pos += y_vel;
		if (x_vel > 0)
			x_vel--;
		else if (x_vel < 0)
			x_vel++;
		y_vel--;
	}
	if (y_pos > target.start_y-1 && x_pos < target.end_x + 1)
	{
		std::cout << "Found " << x_pos << ", " << y_pos << " to be in target area" << std::endl;
		return max_y;
	}
	else
	{
		std::cout << "Stopped calculation at y=" << target.start_y-1 << " because the shot doesn't appear to "
			<< "hit the target area" << std::endl;
		return -666;
	}
}

int find_largest(std::vector<int> vec)
{
	int largest = 0;
	for (int i = 0; i<vec.size(); i++)
	{
		if (vec[i] > largest)
			largest = vec[i];
	}
	return largest;
}

int main()
{
	int try_x = 1, try_y = 0;
	std::vector <int> max_ys;
	int total_working = 0;
	while (try_x < target.end_x + 1)
	{
		std::cout << "Shooting probe with initial velocities of " << try_x << ", " << try_y << std::endl;
		int my_highest_y = shoot_probe(try_x, try_y);
		if (my_highest_y != -666)
		{
			if (my_highest_y != 0)
			{
				std::cout << "Highest y position in this iteration: " << my_highest_y << std::endl;
				max_ys.push_back(my_highest_y);
			}
			total_working++;
		}
		 
		try_y++;
		// Just guessing random values that might work
		if (try_y > 550)
		{
			try_y = -std::abs(target.start_y);
			try_x++;
		}
	}
	std::cout << "The highest recorded positions were: " << std::endl;
	for (int i = 0; i<max_ys.size(); i++)
		std::cout << max_ys[i] << " ";
	std::cout << std::endl << "There, the absolute highest position is " 
		<< find_largest(max_ys) << std::endl;
	std::cout << "In total, there are " << total_working << " solutions." << std::endl;
}
