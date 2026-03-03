#include "odd_even_separator.h"

int main() {
    OddEvenSeparator separator;

    separator.add_number(1);
    separator.add_number(2);
    separator.add_number(3);
    separator.add_number(4);
    separator.add_number(5);
    separator.add_number(6);
    separator.add_number(7);
    separator.add_number(8);
    separator.add_number(9);
    separator.add_number(10);

    std::cout << "Чётные числа: ";
    separator.even();

    std::cout << "Нечётные числа: ";
    separator.odd();

    return 0;
}