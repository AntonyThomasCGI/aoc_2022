#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

#define INPUT_FILE "./input.txt"


void part_two()
{
	std::ifstream input(INPUT_FILE);

	std::string line;
	int calorie_sum = 0;
	int first_top_cal, second_top_cal, third_top_cal;
	
	std::tuple<int, int, int> top_calorie_sums;
	top_calorie_sums = std::make_tuple(0, 0, 0);
	
	while (std::getline(input, line))
	{
		if (!line.empty()) {
			int cal = std::stoi(line);
			calorie_sum += cal;
		}

		// Empty line or end of file represents end of this aliens data.
		if (line.empty() || input.peek() == EOF) {
			if (calorie_sum > std::get<2>(top_calorie_sums)) {
				if (calorie_sum > std::get<1>(top_calorie_sums)) {
					if (calorie_sum > std::get<0>(top_calorie_sums)) {
						std::swap(std::get<0>(top_calorie_sums), calorie_sum);
					}
					std::swap(std::get<1>(top_calorie_sums), calorie_sum);
				}
				std::swap(std::get<2>(top_calorie_sums), calorie_sum);
			}
			calorie_sum = 0;
		}
	}

	std::cout << std::get<0>(top_calorie_sums) + 
			     std::get<1>(top_calorie_sums) + 
				 std::get<2>(top_calorie_sums) << std::endl;
}

void part_one()
{
	std::ifstream input(INPUT_FILE);

	std::string line;
	int calorie_sum = 0, max_calorie_sum = 0;

	while (std::getline(input, line))
	{
		if (!line.empty()) {
			int cal = std::stoi(line);
			calorie_sum += cal;
		}

		// Empty line or end of file represents end of this aliens data.
		if (line.empty() || input.peek() == EOF) {
			if (calorie_sum > max_calorie_sum) {
				max_calorie_sum = calorie_sum;
			}
			calorie_sum = 0;
		} 
	}

	std::cout << max_calorie_sum << std::endl;
}


int main()
{
	part_one();
	part_two();

	return 0;
}

