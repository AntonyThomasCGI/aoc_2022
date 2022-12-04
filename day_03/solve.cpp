#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#define INPUT_FILE "./input.txt"
#define ELVES_PER_GROUP 3

const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


bool shortest(std::string a, std::string b)
{
	return a.length() < b.length();
}

void part_two()
{
	std::ifstream input(INPUT_FILE);

	int total_priority = 0;
	std::vector<std::string> elf_group;

	while (input.peek() != EOF)
	{
		// Reset elf group.
		elf_group.erase(elf_group.begin(), elf_group.end());

		// Create group.
		for (int i = 0; i < ELVES_PER_GROUP; i++) {
			std::string elf;
			std::getline(input, elf);

			elf_group.push_back(elf);
		}
		
		// Find the shortest string for slight optimization.
		std::string least_items = *std::min_element(elf_group.begin(), elf_group.end(), shortest);
		elf_group.erase(std::find(elf_group.begin(), elf_group.end(), least_items));

		// Do the search.
		for (int j = 0; j < least_items.length(); j++) {
			char item = least_items[j]; 
			bool missing_item = false;
			for (std::string elf : elf_group) {
				std::size_t found = elf.find(item);
				if (found == std::string::npos) {
					missing_item = true;
					break;
				}
			}
			if (!missing_item) {
				total_priority += alphabet.find(item) + 1;
				break;
			}
		}
	}

	std::cout << total_priority << std::endl;
}


void part_one()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	int total_priority = 0;
	
	while (input >> line)
	{
		size_t split_at = line.length() / 2;
		std::string compart_one = line.substr(0, split_at);
		std::string compart_two = line.erase(0, split_at);

		for (int i = 0; i < split_at; i++) {
			char item = compart_one[i];
			std::size_t found = compart_two.find(item);
			if (found != std::string::npos) {
				total_priority += alphabet.find(item) + 1;
				break;
			}
		}
	}

	std::cout << total_priority << std::endl;
}


int main()
{
	// part_one();
	part_two();

	return 0;
}

