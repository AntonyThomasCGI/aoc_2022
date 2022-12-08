#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define INPUT_FILE "./input.txt"
#define DISK_SPACE 70000000
#define UPDATE_SIZE 30000000


struct File
{
	std::string name;
	int size;
};


struct Dir
{
	std::string name;
	int size;
	Dir *parent;
	std::vector<File> files;
	std::vector<Dir*> subdirs;
	Dir(std::string, Dir*);
};

Dir::Dir(std::string _name, Dir *_parent) {
	this->name = _name;
	this->parent = _parent;
	this->size = 0;
}


void parse_ls_output(std::ifstream &input, Dir *current_dir)
{
	std::string line;

	while(input.peek() != EOF)
	{
		int pos = input.tellg();

		std::getline(input, line);

		if (line[0] == '$') {  // End of ls output.
			input.seekg(pos, std::ios_base::beg);
			return;
		}

		std::stringstream line_ss(line);
		std::string type, name;
		line_ss >> type >> name;
		
		if (type == "dir") {
			Dir *dir = new Dir{name, current_dir};
			current_dir->subdirs.push_back(dir);
		} else {
			int size = std::stoi(type);
			File file = {name, size};
			current_dir->files.push_back(file);
		}
	}
}


Dir* parse_dirs(std::ifstream &input)
{
	std::string line;
	
	Dir *root = new Dir{"/", nullptr};
	Dir *current_dir = root;

	// Ignore first cd /
	std::getline(input, line);

	while (!input.eof())
	{
		std::getline(input, line);

		if (line == "$ ls") {  // ls command.
			parse_ls_output(input, current_dir);
		} else {  // cd command.
			std::stringstream line_ss(line);
			std::string new_dir;

			// Skip "cd" part.
			line_ss.ignore(4, '>');

			line_ss >> new_dir;
			if (new_dir == "..") {
				current_dir = current_dir->parent;
			}
			else {
				bool exists = false;
				// Check if directory already exists.
				for (Dir *subdir : current_dir->subdirs) {
					if (subdir->name == new_dir) {
						current_dir = subdir;
						exists = true;
						break;
					}
				}
				if (!exists) {  // Create if not.
					Dir *dir = new Dir(new_dir, current_dir);
					current_dir->subdirs.push_back(dir);
					current_dir = dir;
				}
			}
		}
	}
	return root;
}


int calculate_sizes(Dir *root)
{
	for (File file : root->files) {
		root->size += file.size;
	}
	for (Dir *subdir : root->subdirs) {
		int subdir_size = calculate_sizes(subdir);
		root->size += subdir_size;
	}
	return root->size;
}


void get_at_most_100000(Dir *root, std::vector<Dir*> &result)
{
	if (root->size <= 100000) {
		result.push_back(root);
	}
	for (Dir *subdir : root->subdirs) {
		get_at_most_100000(subdir, result);
	}
}


void part_two()
{
	std::ifstream input(INPUT_FILE);
	Dir *root = parse_dirs(input);
	input.close();

	calculate_sizes(root);

	int available_size = DISK_SPACE - root->size;
	int need_to_clean = UPDATE_SIZE - available_size;

	int smallest = root->size;
	std::vector<Dir*> stack;
	stack.push_back(root);
	while (!stack.empty())
	{
		Dir* dir = stack.back();
		stack.pop_back();

		if (dir->size > need_to_clean && dir->size < smallest) {
			smallest = dir->size;
		}
		for (Dir *subdir : dir->subdirs) {
			stack.push_back(subdir);
		}
	}
	std::cout << smallest << std::endl;
}


void part_one()
{
	std::ifstream input(INPUT_FILE);
	Dir *root = parse_dirs(input);
	input.close();

	calculate_sizes(root);

	std::vector<Dir*> at_most_100000;
	get_at_most_100000(root, at_most_100000);

	int result = 0;
	for (Dir *dir : at_most_100000) {
		result += dir->size;
	}
	std::cout << result << std::endl;
}


int main()
{
	part_one();
	part_two();

	return 0;
}

