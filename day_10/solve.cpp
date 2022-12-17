#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define INPUT_FILE "./input.txt"


class Register;


class Instruction
{
	public:
		std::string name;
		int current_cycles;
		int total_cycles = 1;

		Instruction(std::string _name)
		{
			name = _name;
			current_cycles = 0;
		}

		bool increment_cycle()
		{
			current_cycles += 1;
			return (current_cycles >= get_total_cycles()) ? true : false;
		}

		virtual int get_total_cycles()
		{
			return total_cycles;
		};

		virtual bool on_complete(Register *reg) = 0;
};


class NoOp: public Instruction
{
	public:
		NoOp(std::string _name)
		: Instruction(_name) {};

		bool on_complete(Register *reg) override
		{
			return true;
		}
};

class AddX: public Instruction
{
	public:
		int to_add;
		int total_cycles = 2;

		AddX(std::string _name, int _to_add)
		: Instruction(_name), to_add(_to_add) {}

		int get_total_cycles() override
		{
			return total_cycles;
		}

		bool on_complete(Register *reg) override;
};


class Register
{
	public:
		int cycle;
		int value;
		bool in_use;
		Instruction *current_instruction;

		Register(int initial_value = 1)
		{
			value = initial_value;
			cycle = 1;
			in_use = false;
		}

		bool check_in_use()
		{
			return in_use;
		}

		void do_cycle()
		{
			if (in_use) {
				bool is_complete = current_instruction->increment_cycle();
				if (is_complete) {
					current_instruction->on_complete(this);
					in_use = false;
				}
			}
			cycle++;
		}

		void load_instruction(Instruction *instruction)
		{
			if (!in_use)
			{
				in_use = true;
				current_instruction = instruction;
			}
		}
};


bool AddX::on_complete(Register *reg)
{
	(*reg).value += to_add;
	return true;
}


void part_two()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	Register *reg = new Register();

	while (!input.eof())
	{
		//std::cout << reg->value << std::endl;
		if (std::abs(reg->value + 1 - (reg->cycle) % 40) < 2) {
			std::cout << "█";
		} else {
			std::cout << ".";
		}
		if (((reg->cycle) % 40) == 0) {
			std::cout << std::endl;
		}

		if (!reg->check_in_use()) {
			// Parse next instruction.
			std::getline(input, line);
			std::stringstream ss(line);
			std::string op;
			ss >> op;
			// Add instruction to register.
			Instruction *instruction;
			if (op == "addx") {
				int to_add;
				ss >> to_add;
				instruction = new AddX("test", to_add);
			} else {
				instruction = new NoOp("testnop");
			}
			reg->load_instruction(instruction);
		}

		reg->do_cycle();
	}
	input.close();
}


void part_one()
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	Register *reg = new Register();
	int result = 0;

	while (!input.eof())
	{
		if ((reg->cycle + 20) % 40 == 0) {
			int signal_strength = reg->cycle * reg->value;
			result += signal_strength;
		}

		if (!reg->check_in_use()) {
			// Parse next instruction.
			std::getline(input, line);
			std::stringstream ss(line);
			std::string op;
			ss >> op;
			// Add instruction to register.
			Instruction *instruction;
			if (op == "addx") {
				int to_add;
				ss >> to_add;
				instruction = new AddX("test", to_add);
			} else {
				instruction = new NoOp("testnop");
			}
			reg->load_instruction(instruction);
		}

		reg->do_cycle();
	}
	input.close();

	std::cout << result << std::endl;
}


int main()
{
	part_one();
	part_two();

	return 0;
}

