#pragma once

#include <vector>

class Table {
	std::vector<std::vector<int>> data;
	int rows;
	int cols;

public:

	Table(int rows, int cols);
	int get_value(int row, int col) const;
	void set_value(int row, int col, int value);
	int n_rows() const;
	int n_cols() const;
	void print() const;
	double average() const;
};