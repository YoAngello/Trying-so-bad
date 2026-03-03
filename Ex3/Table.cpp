#include "table.h"
#include <iostream>
#include <iomanip>

Table::Table(int rows, int cols) : rows(rows), cols(cols) {
	data.resize(rows, std::vector<int>(cols, 0));
}

int Table::get_value(int row, int col) const {
	return data[row][col];
}

void Table::set_value(int row, int col, int value) {
	data[row][col] = value;
}

void Table::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(4) << data[i][j];
        }
        std::cout << std::endl;
    }
}

double Table::average() const {
    if (rows == 0 || cols == 0) {
        return 0.0;
    }

    long long sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += data[i][j];
        }
    }

    return static_cast<double>(sum) / (rows * cols);
}
