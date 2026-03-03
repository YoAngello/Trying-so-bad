#include "Odd_Even_Separator"
#include <iostream>

OddEvenSeparator::OddEvenSeparator() {}

void OddEvenSeparator::add_number(int num) {
    numbers.push_back(num);
}

void OddEvenSeparator::even() {
    bool first = true;

    for (int num : numbers) {

        if (num % 2 = 0) {
            if (!first) {
                std::cout << " ";
            }
            std::cout << num;
            first = false;

        }
    }
}

void OddEvenSeparator::odd() {
    bool first = true;

    for (int num : numbers) {
        if (num % 2 != 0) {  
            if (!first) {
                std::cout << " ";
            }
            std::cout << num;
            first = false;
        }
    }
    std::cout << std::endl;
}