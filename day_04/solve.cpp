#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#define INPUT_FILE "./input.txt"


struct Range
{
	int min;
	int max;
};


Range parse_range(std::stringstream &line_ss)
{
	std::string min_val, max_val;

	std::getline(line_ss, min_val, '-');
	std::getline(line_ss, max_val, ',');

	int min, max;
	min = std::stoi(min_val);
	max = std::stoi(max_val);

	Range range = {min, max};
	return range;
}


bool fully_contains(Range range_a, Range range_b)
{
	return range_b.min >= range_a.min && range_b.max <= range_a.max;
}


bool contains(Range range_a, Range range_b)
{
	return range_b.min <= range_a.max && range_b.max >= range_a.min;
}


void part_two()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	int count = 0;

	while (input >> line)
	{
		std::stringstream line_ss(line);

		Range elf_a = parse_range(line_ss);
		Range elf_b = parse_range(line_ss);

		if (contains(elf_a, elf_b) || contains(elf_b, elf_a)) {
			count += 1;
		}
	}

	std::cout << count << std::endl;
}


void part_one()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	int count = 0;

	while (input >> line)
	{
		std::stringstream line_ss(line);

		Range elf_a = parse_range(line_ss);
		Range elf_b = parse_range(line_ss);

		if (fully_contains(elf_a, elf_b) || fully_contains(elf_b, elf_a)) {
			count += 1;
		}
	}

	std::cout << count << std::endl;
}


int main()
{
	part_one();
	part_two();

	return 0;
}

