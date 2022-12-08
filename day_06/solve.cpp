#include <fstream>
#include <iostream>
#include <string>

#define INPUT_FILE "./input.txt"


void part_two()
{
	std::ifstream input(INPUT_FILE);
}


bool has_duplicates(std::string s)
{
	for (int i = 0; i < s.length(); i++) {
		char marker = s[i];
		std::string rest = s.substr(i + 1);
		std::size_t found = rest.find(marker);
		if (found != std::string::npos) {
			return true;
		}
	}
	return false;
}


void part_one()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	input >> line;

	for (int i = 0; i < line.length(); i++) {
		std::string sub_str = line.substr(i, 14);
		if (!has_duplicates(sub_str)) {
			std::cout << i + 14 << std::endl;
			break;
		}
	}
}


int main()
{
	part_one();
	// part_two();

	return 0;
}

