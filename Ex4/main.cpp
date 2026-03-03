#include "complex.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Вспомогательная функция для печати разделителя
void printSeparator() {
    cout << "\n" << string(50, '-') << "\n" << endl;
}

// Функция для тестирования одного комплексного числа
void testComplex(const Complex& z, const string& name) {
    cout << "Число " << name << ":" << endl;
    cout << "  Алгебраическая форма: " << z.to_string() << endl;
    cout << "  Тригонометрическая форма: " << z.to_string_trig() << endl;
    cout << "  Показательная форма: " << z.to_string_exp() << endl;
    cout << "  Модуль: " << z.abs() << endl;
    cout << "  Аргумент: " << z.arg() << " рад (" << z.arg() * 180.0 / M_PI << "°)" << endl;
}

int main() {
    // Устанавливаем формат вывода чисел
    cout << fixed << setprecision(3);

    cout << "ТЕСТИРОВАНИЕ КЛАССА COMPLEX" << endl;
    printSeparator();

    // Тест 1: Создание чисел
    cout << "ТЕСТ 1: Создание комплексных чисел" << endl;

    Complex z1;                    // 0 + 0i
    Complex z2(3, 4);              // 3 + 4i
    Complex z3(1, -1);             // 1 - i
    Complex z4(-2, 3);             // -2 + 3i
    Complex z5(-1, -2);            // -1 - 2i

    cout << "z1 (по умолчанию): " << z1.to_string() << endl;
    cout << "z2 (3, 4): " << z2.to_string() << endl;
    cout << "z3 (1, -1): " << z3.to_string() << endl;
    cout << "z4 (-2, 3): " << z4.to_string() << endl;
    cout << "z5 (-1, -2): " << z5.to_string() << endl;

    printSeparator();

    // Тест 2: Геттеры и сеттеры
    cout << "ТЕСТ 2: Геттеры и сеттеры" << endl;

    Complex z6;
    cout << "Изначально: " << z6.to_string() << endl;

    z6.set_re(5.5);
    z6.set_im(-2.5);
    cout << "После set_re(5.5) и set_im(-2.5): " << z6.to_string() << endl;
    cout << "get_re() = " << z6.get_re() << ", get_im() = " << z6.get_im() << endl;

    printSeparator();

    // Тест 3: Подробное тестирование разных чисел
    testComplex(z2, "z2 (3+4i)");
    printSeparator();

    testComplex(z3, "z3 (1-i)");
    printSeparator();

    testComplex(z4, "z4 (-2+3i)");
    printSeparator();

    testComplex(z5, "z5 (-1-2i)");
    printSeparator();

    // Тест 4: Арифметические операции
    cout << "ТЕСТ 4: Арифметические операции" << endl;
    cout << "z2 = " << z2.to_string() << endl;
    cout << "z3 = " << z3.to_string() << endl;

    Complex sum = z2.add(z3);
    cout << "z2 + z3 = " << sum.to_string() << endl;

    Complex diff = z2.sub(z3);
    cout << "z2 - z3 = " << diff.to_string() << endl;

    Complex prod = z2.mult(z3);
    cout << "z2 * z3 = " << prod.to_string() << endl;

    Complex quot = z2.div(z3);
    cout << "z2 / z3 = " << quot.to_string() << endl;

    printSeparator();

    // Тест 5: Проверка на единичной окружности
    cout << "ТЕСТ 5: Числа на единичной окружности" << endl;

    Complex unit1(1, 0);     // 1 (угол 0°)
    Complex unit2(0, 1);     // i (угол 90°)
    Complex unit3(-1, 0);    // -1 (угол 180°)
    Complex unit4(0, -1);    // -i (угол 270°)

    cout << "1: модуль=" << unit1.abs() << ", аргумент=" << unit1.arg() * 180.0 / M_PI << "°" << endl;
    cout << "i: модуль=" << unit2.abs() << ", аргумент=" << unit2.arg() * 180.0 / M_PI << "°" << endl;
    cout << "-1: модуль=" << unit3.abs() << ", аргумент=" << unit3.arg() * 180.0 / M_PI << "°" << endl;
    cout << "-i: модуль=" << unit4.abs() << ", аргумент=" << unit4.arg() * 180.0 / M_PI << "°" << endl;

    printSeparator();

    // Тест 6: Ассоциативность операций
    cout << "ТЕСТ 6: Проверка свойств" << endl;

    Complex a(2, 3);
    Complex b(1, -2);
    Complex c(3, 1);

    cout << "a = " << a.to_string() << endl;
    cout << "b = " << b.to_string() << endl;
    cout << "c = " << c.to_string() << endl;

    // (a + b) + c == a + (b + c)
    Complex left1 = a.add(b).add(c);
    Complex right1 = a.add(b.add(c));
    cout << "(a + b) + c = " << left1.to_string() << endl;
    cout << "a + (b + c) = " << right1.to_string() << endl;

    // (a * b) * c == a * (b * c)
    Complex left2 = a.mult(b).mult(c);
    Complex right2 = a.mult(b.mult(c));
    cout << "(a * b) * c = " << left2.to_string() << endl;
    cout << "a * (b * c) = " << right2.to_string() << endl;

    printSeparator();

    // Тест 7: Деление и умножение (проверка)
    cout << "ТЕСТ 7: Проверка: (a / b) * b == a" << endl;

    Complex divResult = a.div(b);
    Complex checkResult = divResult.mult(b);

    cout << "a = " << a.to_string() << endl;
    cout << "b = " << b.to_string() << endl;
    cout << "a / b = " << divResult.to_string() << endl;
    cout << "(a / b) * b = " << checkResult.to_string() << " (должно быть " << a.to_string() << ")" << endl;

    return 0;
}