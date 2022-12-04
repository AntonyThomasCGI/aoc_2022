#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

#define INPUT_FILE "./input.txt"

const int WIN = 6, LOSS = 0, DRAW = 3;


enum Weapon { ROCK=1, PAPER=2, SCISSORS=3 };

std::map<std::string, Weapon> id_map = {
	{"A", Weapon::ROCK},
	{"B", Weapon::PAPER},
	{"C", Weapon::SCISSORS},
	{"X", Weapon::ROCK},
	{"Y", Weapon::PAPER},
	{"Z", Weapon::SCISSORS}
};

std::map<std::string, const int> outcome_map = {
	{"X", LOSS},
	{"Y", DRAW},
	{"Z", WIN}
};


// play_game returns the amount of points we would recieve from playing.
int play_game(Weapon opponent, Weapon response)
{
	if (opponent == response) { return DRAW; };

	switch(opponent) {
		case ROCK: return response == PAPER ? WIN : LOSS;
		case PAPER: return response == SCISSORS ? WIN : LOSS;
		case SCISSORS: return response == ROCK ? WIN : LOSS;
	}
}


// calculate_response returns the weapon you would need to play for a given outcome.
int calculate_response(Weapon opponent, const int outcome)
{
	if (outcome == DRAW) { return opponent; };

	switch(opponent) {
		case ROCK: return outcome == WIN ? PAPER : SCISSORS;
		case PAPER: return outcome == WIN ? SCISSORS : ROCK;
		case SCISSORS: return outcome == WIN ? ROCK : PAPER;
	}
}


void part_two()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	int total_points = 0;

	while (std::getline(input,line))
	{
		std::stringstream line_ss(line);
		std::string opponent, outcome;

		std::getline(line_ss, opponent, ' ');
		std::getline(line_ss, outcome, ' ');

		int result = outcome_map[outcome];

		int response = calculate_response(id_map[opponent], result);
		int round_points = response + result;

		total_points += round_points;
	}

	std::cout << total_points;
}

void part_one()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	int total_points = 0;

	while (std::getline(input, line))
	{
		std::stringstream line_ss(line);
		std::string opponent, response;

		std::getline(line_ss, opponent, ' ');
		std::getline(line_ss, response, ' '); 

		int result = play_game(id_map[opponent], id_map[response]);
		int round_points = result + id_map[response];

		total_points += round_points;
	}

	std::cout << total_points;
}


int main()
{
	// part_one();
	part_two();

	return 0;
}

