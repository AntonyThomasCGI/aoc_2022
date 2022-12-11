#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


//#define USE_EXAMPLE
#define USE_INPUT

#if defined(USE_EXAMPLE)
	#define INPUT_FILE "./example.txt"
	#define WIDTH 5
	#define HEIGHT 5
#elif defined(USE_INPUT)
	#define INPUT_FILE "./input.txt"
	#define WIDTH 99
	#define HEIGHT 99
#endif


// Builds 2d array of boolean values representing if a tree is visbile
// from North/East/South/West.
bool** build_visible_tree_array(int forest[][HEIGHT])
{
	bool **result = new bool*[WIDTH];
	int curr_max;
	
	// Loop width then height to check east and west directions.
	for (int x = 0; x < WIDTH; x++) {
		// Initialize array.
		result[x] = new bool[HEIGHT];
		// Check East.
		curr_max = -1;
		for (int y = 0; y < HEIGHT; y++) {
			bool visible = (forest[x][y] > curr_max) ? true : false;
			if (visible)
				curr_max = forest[x][y];
			result[x][y] = visible;
		}
		// Check West.
		curr_max = -1;
		for (int y = HEIGHT - 1; y >= 0; y--) {
			bool visible = (forest[x][y] > curr_max) ? true : false;
			if (visible)
				curr_max = forest[x][y];
			result[x][y] = result[x][y] | visible;
		}
	}
	// Loop height then width to check south and north directions.
	for (int y = 0; y < HEIGHT; y++) {
		// Check South.
		curr_max = -1;
		for (int x = 0; x < WIDTH; x++) {
			bool visible = (forest[x][y] > curr_max) ? true : false;
			if (visible)
				curr_max = forest[x][y];
			result[x][y] = result[x][y] | visible;
		}
		// Check North.
		curr_max = -1;
		for (int x = WIDTH- 1; x >= 0; x--) {
			bool visible = (forest[x][y] > curr_max) ? true : false;
			if (visible)
				curr_max = forest[x][y];
			result[x][y] = result[x][y] | visible;
		}
	}

	return result;
}


int calculate_scenic_score(int forest[][WIDTH], int w, int h)
{
	int tree = forest[w][h];

	// Check East.
	int east_score = 0;
	for (int x = w + 1; x < WIDTH; x++) {
		east_score += 1;
		if (forest[x][h] >= tree) {
			break;
		}
	}
	// Check West.
	int west_score = 0;
	for (int x = w - 1; x >= 0; x--) {
		west_score += 1;
		if (forest[x][h] >= tree) {
			break;
		}
	}
	// Check South.
	int south_score = 0;
	for (int y = h + 1; y < HEIGHT; y++) {
		south_score += 1;
		if (forest[w][y] >= tree) {
			break;
		}
	}
	// Check North.
	int north_score = 0;
	for (int y = h - 1; y >= 0; y--) {
		north_score += 1;
		if (forest[w][y] >= tree) {
			break;
		}
	}

	return north_score * south_score * east_score * west_score;
}


void part_two()
{
	std::ifstream input(INPUT_FILE);
	int forest[WIDTH][HEIGHT];

	// Parse input.
	std::string line;
	for (int x = 0; x < WIDTH; x++)
	{
		input >> line;
		std::stringstream ss(line);
		for (int y = 0; y < HEIGHT; y++)
		{
			char tree;
			ss.get(tree);
			// char 0-9 decimal value = 48-57.
			forest[x][y] = tree - 48;
		}
	}

	// Calculate result.
	int max_score = 0;
	for (int x = 1; x < WIDTH - 1; x++)
	{
		for (int y = 1; y < HEIGHT - 1; y++) {
			int scenic_score = calculate_scenic_score(forest, x, y);
			max_score = std::max(max_score, scenic_score);
		}
	}
	std::cout << max_score << std::endl;
}


void part_one()
{
	std::ifstream input(INPUT_FILE);

	int forest[WIDTH][HEIGHT];

	// Parse input.
	std::string line;
	for (int x = 0; x < WIDTH; x++)
	{
		input >> line;
		std::stringstream ss(line);
		for (int y = 0; y < WIDTH; y++)
		{
			char tree;
			ss.get(tree);
			// char 0-9 decimal value = 48-57.
			forest[x][y] = tree - 48;
		}
	}

    bool **visible_trees = build_visible_tree_array(forest);

	// Combine arrays and get result.
	int result = 0;
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < WIDTH; y++) {
			result += visible_trees[x][y];
		}
	}
	std::cout << result << std::endl;
}


int main()
{
	part_one();
	part_two();

	return 0;
}

