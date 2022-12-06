#include <deque>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define INPUT_FILE "./input.txt"


void part_two()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	// Peek first line to determine number of stacks.
	std::getline(input, line);
	int n = (line.length() + 1) / 4;
	input.seekg(std::ios_base::beg);

	std::vector<std::deque<char>> stacks(n);

	// Parse crate arrangement.
	while (!input.eof())
	{
		std::getline(input, line);

		// Catch end of crate input and break.
		if (line.rfind(" 1", 0) == 0) { break; };

		int stack_num = 0;
		for (int i = 0; i < line.length(); i += 4) {
			char crate = line[i + 1];
			// Check for crate.
			if (crate != ' ') {
				stacks[stack_num].push_back(crate);
			}
			stack_num++;
		}
	}

	// Skip blank line after crate input.
	input.ignore(1, '\n');
	
	while(std::getline(input, line).good())
	{
		// Parse instructions.
		std::stringstream line_ss(line);

		int instructions[3];
		for (int i = 0; i < 6; i++) {
			std::string token;
			std::getline(line_ss, token, ' ');
			if (i % 2 == 1) {
				int token_i = std::stoi(token);
				instructions[i / 2] = token_i;
			}
		}
		int move = instructions[0];
		// Instructions are 1 indexed, we want 0 indexed.
		int from = instructions[1] - 1;
		int to = instructions[2] - 1;

		// Apply instructions.
		std::vector<char> crate_group;
		for (int j = 0; j < move; j++) {
			crate_group.push_back(stacks[from].front());
			stacks[from].pop_front();
		}
		std::reverse(crate_group.begin(), crate_group.end());
		for (char transit_crate : crate_group) {
			stacks[to].push_front(transit_crate);
		}
	}

	input.close();

	for (auto stack : stacks) {
		std::cout << stack.front();
	}
	std::cout << std::endl;
}


void part_one()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	// Peek first line to determine number of stacks.
	std::getline(input, line);
	int n = (line.length() + 1) / 4;
	input.seekg(std::ios_base::beg);

	std::vector<std::deque<char>> stacks(n);

	// Parse crate arrangement.
	while (!input.eof())
	{
		std::getline(input, line);

		// Catch end of crate input and break.
		if (line.rfind(" 1", 0) == 0) { break; };

		int stack_num = 0;
		for (int i = 0; i < line.length(); i += 4) {
			char crate = line[i + 1];
			// Check for crate.
			if (crate != ' ') {
				stacks[stack_num].push_back(crate);
			}
			stack_num++;
		}
	}

	// Skip blank line after crate input.
	input.ignore(1, '\n');
	
	while(std::getline(input, line).good())
	{
		// Parse instructions.
		std::stringstream line_ss(line);

		int instructions[3];
		for (int i = 0; i < 6; i++) {
			std::string token;
			std::getline(line_ss, token, ' ');
			if (i % 2 == 1) {
				int token_i = std::stoi(token);
				instructions[i / 2] = token_i;
			}
		}
		int move = instructions[0];
		// Instructions are 1 indexed, we want 0 indexed.
		int from = instructions[1] - 1;
		int to = instructions[2] - 1;

		// Apply instructions.
		for (int j = 0; j < move; j++) {
			char transit_crate = stacks[from].front();
			stacks[from].pop_front();
			stacks[to].push_front(transit_crate);
		}
	}

	input.close();

	for (auto stack : stacks) {
		std::cout << stack.front();
	}
	std::cout << std::endl;
}


int main()
{
	part_one();
	part_two();

	return 0;
}

