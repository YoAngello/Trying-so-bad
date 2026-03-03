#pragma once

#include <vector>

class OddEvenSeparator {
	std::vector<int> numbers;

public:

	OddEvenSeparator();
	void add_number(int num);
	void even();
	void odd();
};
