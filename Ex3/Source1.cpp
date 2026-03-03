#include "table.h"
#include <iostream>

int main() {
    // Создаем таблицу 3x4
    Table table(3, 4);

    // Заполняем таблицу значениями
    int value = 1;
    for (int i = 0; i < table.n_rows(); ++i) {
        for (int j = 0; j < table.n_cols(); ++j) {
            table.set_value(i, j, value++);
        }
    }

    // Читаем отдельную ячейку
    std::cout << "Значение в ячейке (1, 2): " << table.get_value(1, 2) << std::endl;
    std::cout << std::endl;

    // Выводим всю таблицу
    std::cout << "Таблица:" << std::endl;
    table.print();
    std::cout << std::endl;

    // Выводим размеры таблицы
    std::cout << "Строк: " << table.n_rows() << ", столбцов: " << table.n_cols() << std::endl;
    std::cout << std::endl;

    // Выводим среднее арифметическое
    std::cout << "Среднее арифметическое: " << table.average() << std::endl;

    return 0;
}