#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define INPUT_FILE "./input.txt"


struct Point {
	int x;
	int y;
};


void part_two()
{
	std::ifstream input(INPUT_FILE);

	char direction;
	int step;

	Point head = {0, 0};
	std::vector<Point> knots;
	for (int i = 0; i < 9; i++) {
		Point knot = {0, 0};
		knots.push_back(knot);
	}
	
	std::vector<Point> tail_positions;
	tail_positions.push_back(Point{0, 0});

	int loops = 0;
	while (input >> direction >> step)
	{
		for (int i = 0; i < step; i++) {
			// Move head.
			switch (direction) {
				case 'U':
					head.y += 1;
					break;
				case 'D':
					head.y -= 1;
					break;
				case 'L':
					head.x -= 1;
					break;
				case 'R':
					head.x += 1;
					break;
			}
			Point current_head = head;
			for (Point &knot : knots) {
				// Move knot towards current head if out of range.
				int delta_x = current_head.x - knot.x;
				int delta_y = current_head.y - knot.y;
				if (std::abs(delta_x) > 1 || std::abs(delta_y) > 1) {
					if (delta_x != 0) {
						knot.x += (delta_x > 0) ? 1 : -1;
					}
					if (delta_y != 0) {
						knot.y += (delta_y > 0) ? 1 : -1;
					}
				}
				current_head = knot;
			}
			// Track unique tail 9 positions.
			Point tail = knots.back();
			bool exists = false;
			for (Point tail_position : tail_positions) {
				if (tail_position.x == tail.x && tail_position.y == tail.y) {
					exists = true;
					break;
				}
			}
			if (!exists) {
				tail_positions.push_back(tail);
			}
		}
	}
	input.close();

	std::cout << tail_positions.size() << std::endl;
}


void part_one()
{
	std::ifstream input(INPUT_FILE);

	char direction;
	int step;

	Point head = {0, 0};
	Point tail = {0, 0};
	
	std::vector<Point> tail_positions;
	tail_positions.push_back(tail);

	while (input >> direction >> step)
	{
		for (int i = 0; i < step; i++) {
			// Store previous position of head.
			Point prev_head = {head.x, head.y};
			// Move head.
			switch (direction) {
				case 'U':
					head.y += 1;
					break;
				case 'D':
					head.y -= 1;
					break;
				case 'L':
					head.x -= 1;
					break;
				case 'R':
					head.x += 1;
					break;
			}
			// If tail is out of range, move to previous position of head.
			if (std::abs(head.x - tail.x) > 1 || std::abs(head.y - tail.y) > 1) {
				tail = prev_head;
				bool exists = false;
				for (Point tail_position : tail_positions) {
					if (tail_position.x == tail.x && tail_position.y == tail.y) {
						exists = true;
						break;
					}
				}
				if (!exists) {
					tail_positions.push_back(tail);
				}
			}
		}
	}
	input.close();

	std::cout << tail_positions.size() << std::endl;
}


int main()
{
	part_one();
	part_two();

	return 0;
}

