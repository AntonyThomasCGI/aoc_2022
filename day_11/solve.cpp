#include <fstream>
#include <iostream>
#include <vector>

//#define USE_EXAMPLE
#define USE_INPUT

using Lambda = std::function<long(long)>;

class Monkey
{
	public:
		long id;
		std::vector<long> items;
		Lambda worry_fn;
		Lambda test_fn;
		long inspect_count;

		Monkey(
			long _id,
			std::vector<long> _items,
			Lambda _worry_fn,
			Lambda _test_fn
		) {
			id = _id;
			items = _items;
			worry_fn = _worry_fn;
			test_fn = _test_fn;
			inspect_count = 0;
		}

		void calculate_worry(Lambda worry_less)
		{
			for (auto &item : items) {
				item = worry_less(worry_fn(item));
				inspect_count++;
			}
		}
};

# if defined (USE_EXAMPLE)
// Monkey zero
Monkey monkey_0(
	0,
	std::vector<long>{79, 98},
	[](long old){ return old * 19; },
	[](long x){ return x % 23 == 0 ? 2 : 3; }
);
// Monkey one
Monkey monkey_1(
	1,
	std::vector<long>{54, 65, 75, 74},
	[](long old){ return old + 6; },
	[](long x){ return x % 19 == 0 ? 2 : 0; }
);
// Monkey two
Monkey monkey_2(
	2,
	std::vector<long>{79, 60, 97},
	[](long old){ return old * old; },
	[](long x){ return x % 13 == 0 ? 1 : 3; }
);
// Monkey three
Monkey monkey_3(
	3,
	std::vector<long>{74},
	[](long old){ return old + 3; },
	[](long x){ return x % 17 == 0 ? 0 : 1; }
);

long monkey_product = 23 * 19 * 13 * 17;

std::vector<Monkey> monkeys{
	monkey_0,
	monkey_1,
	monkey_2,
	monkey_3
};

#elif defined(USE_INPUT)
// Monkey zero
Monkey monkey_0(
	0,
	std::vector<long>{98, 97, 98, 55, 56, 72},
	[](long old){ return old * 13; },
	[](long x){ return x % 11 == 0 ? 4 : 7; }
);
// Monkey one
Monkey monkey_1(
	1,
	std::vector<long>{73, 99, 55, 54, 88, 50, 55},
	[](long old){ return old + 4; },
	[](long x){ return x % 17 == 0 ? 2 : 6; }
);
// Monkey two
Monkey monkey_2(
	2,
	std::vector<long>{67, 98},
	[](long old){ return old * 11; },
	[](long x){ return x % 5 == 0 ? 6 : 5; }
);
// Monkey three
Monkey monkey_3(
	3,
	std::vector<long>{82, 91, 92, 53, 99},
	[](long old){ return old + 8; },
	[](long x){ return x % 13 == 0 ? 1 : 2; }
);
// Monkey four
Monkey monkey_4(
	4,
	std::vector<long>{52, 62, 94, 96, 52, 87, 53, 60},
	[](long old){ return old * old; },
	[](long x){ return x % 19 == 0 ? 3 : 1; }
);
// Monkey five
Monkey monkey_5(
	5,
	std::vector<long>{94, 80, 84, 79},
	[](long old){ return old + 5; },
	[](long x){ return x % 2 == 0 ? 7 : 0; }
);
// Monkey six
Monkey monkey_6(
	6,
	std::vector<long>{89},
	[](long old){ return old + 1; },
	[](long x){ return x % 3 == 0 ? 0 : 5; }
);
// Monkey seven
Monkey monkey_7(
	7,
	std::vector<long>{70, 59, 63},
	[](long old){ return old + 3; },
	[](long x){ return x % 7 == 0 ? 4 : 3; }
);

long monkey_product = 11 * 17 * 5 * 13 * 19 * 2 * 3 * 7;

std::vector<Monkey> monkeys{
	monkey_0,
	monkey_1,
	monkey_2,
	monkey_3,
	monkey_4,
	monkey_5,
	monkey_6,
	monkey_7
};

#endif


void part_two()
{
	Lambda worry_fn = [](long x){ return x % monkey_product; };

	for (long i = 0; i < 10000; i++) {
		for (auto &monkey : monkeys) {
			monkey.calculate_worry(worry_fn);

			// Throw items.
			std::vector<long>::iterator iter = monkey.items.begin();
			while(iter != monkey.items.end())
			{
				long item = *iter;
				long toss_id = monkey.test_fn(item);
				monkeys[toss_id].items.push_back(item);
				iter = monkey.items.erase(iter);
			}
		}
	}
	long max_inspect = -1;
	long second_max_inspect = -1;
	for (auto &monkey : monkeys) {
		if (monkey.inspect_count > max_inspect) {
			second_max_inspect = max_inspect;
			max_inspect = monkey.inspect_count;
		} else if (monkey.inspect_count > second_max_inspect) {
			second_max_inspect = monkey.inspect_count;
		}
	}
	std::cout << max_inspect * second_max_inspect << std::endl;
}


void part_one()
{
	Lambda worry_fn = [](long x){ return x / 3; };

	for (long i = 0; i < 20; i++) {
		for (auto &monkey : monkeys) {
			monkey.calculate_worry(worry_fn);

			// Throw items.
			std::vector<long>::iterator iter = monkey.items.begin();
			while(iter != monkey.items.end())
			{
				long item = *iter;
				long toss_id = monkey.test_fn(item);
				monkeys[toss_id].items.push_back(item);
				iter = monkey.items.erase(iter);
			}
		}
	}
	long max_inspect = -1;
	long second_max_inspect = -1;
	for (auto &monkey : monkeys) {
		if (monkey.inspect_count > max_inspect) {
			second_max_inspect = max_inspect;
			max_inspect = monkey.inspect_count;
		} else if (monkey.inspect_count > second_max_inspect) {
			second_max_inspect = monkey.inspect_count;
		}
	}
	std::cout << max_inspect * second_max_inspect << std::endl;
}


int main()
{
	//part_one();
	part_two();

	return 0;
}

