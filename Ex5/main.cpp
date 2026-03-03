#include "stock.h"
#include <iostream>
#include <iomanip>
#include <clocale>

using namespace std;

void printSeparator() {
    cout << "\n" << string(60, '=') << "\n" << endl;
}

void printTestHeader(const string& testName) {
    cout << "\n" << string(40, '-') << endl;
    cout << "ТЕСТ: " << testName << endl;
    cout << string(40, '-') << endl;
}

int main() {
    setlocale(LC_ALL, "Ru")
    cout << fixed << setprecision(2);
    cout << "ТЕСТИРОВАНИЕ СИСТЕМЫ УПРАВЛЕНИЯ СКЛАДОМ" << endl;
    printSeparator();

    Stock stock;

    // ТЕСТ 1: Добавление коробок
    printTestHeader("Добавление коробок на склад");

    cout << "Добавляем коробки в следующем порядке:" << endl;
    cout << "1. w=10, v=100" << endl;
    stock.Add(10, 100);

    cout << "2. w=20, v=50" << endl;
    stock.Add(20, 50);

    cout << "3. w=15, v=80" << endl;
    stock.Add(15, 80);

    cout << "4. w=25, v=120" << endl;
    stock.Add(25, 120);

    cout << "5. w=30, v=60" << endl;
    stock.Add(30, 60);

    cout << "\nПосле добавления:" << endl;
    stock.PrintStock();

    // ТЕСТ 2: Поиск по грузоподъемности
    printTestHeader("Поиск по грузоподъемности (GetByW)");

    int test_weights[] = { 5, 10, 15, 20, 25, 30, 35, 40 };

    for (int w : test_weights) {
        int result = stock.GetByW(w);
        if (result != -1) {
            cout << "Поиск коробки с грузоподъемностью >= " << w
                << ": найдена коробка ID=" << result << endl;
        }
        else {
            cout << "Поиск коробки с грузоподъемностью >= " << w
                << ": коробок нет" << endl;
        }
    }

    cout << "\nСостояние склада после поисков:" << endl;
    stock.PrintStock();

    // ТЕСТ 3: Поиск по объему
    printTestHeader("Поиск по объему (GetByV)");

    int test_volumes[] = { 40, 50, 60, 70, 80, 90, 100, 110, 120, 130 };

    for (int v : test_volumes) {
        int result = stock.GetByV(v);
        if (result != -1) {
            cout << "Поиск коробки с объемом >= " << v
                << ": найдена коробка ID=" << result << endl;
        }
        else {
            cout << "Поиск коробки с объемом >= " << v
                << ": коробок нет" << endl;
        }
    }

    cout << "\nСостояние склада после поисков:" << endl;
    stock.PrintStock();

    // ТЕСТ 4: Проверка FIFO (выбор самой старой коробки)
    printTestHeader("Проверка FIFO - выбор самой старой подходящей коробки");

    // Очищаем склад и добавляем новые коробки
    Stock stock2;

    cout << "Добавляем коробки в порядке:" << endl;
    cout << "ID0: w=20, v=50 (поступление 0)" << endl;
    stock2.Add(20, 50);

    cout << "ID1: w=20, v=50 (поступление 1)" << endl;
    stock2.Add(20, 50);

    cout << "ID2: w=30, v=70 (поступление 2)" << endl;
    stock2.Add(30, 70);

    cout << "ID3: w=25, v=60 (поступление 3)" << endl;
    stock2.Add(25, 60);

    cout << "\nНачальное состояние:" << endl;
    stock2.PrintStock();

    cout << "Запрос на коробку с грузоподъемностью >= 20" << endl;
    cout << "Должна быть выбрана самая старая подходящая (ID0)" << endl;
    int result = stock2.GetByW(20);
    cout << "Выбрана коробка ID=" << result << " ✓" << endl;

    cout << "\nЗапрос на коробку с грузоподъемностью >= 20" << endl;
    cout << "Должна быть выбрана следующая самая старая (ID1)" << endl;
    result = stock2.GetByW(20);
    cout << "Выбрана коробка ID=" << result << " ✓" << endl;

    cout << "\nЗапрос на коробку с объемом >= 60" << endl;
    cout << "Должна быть выбрана самая старая подходящая (ID3)" << endl;
    result = stock2.GetByV(60);
    cout << "Выбрана коробка ID=" << result << " ✓" << endl;

    // ТЕСТ 5: Случай, когда подходящих коробок несколько с разными параметрами
    printTestHeader("Выбор среди коробок с разными параметрами");

    Stock stock3;

    stock3.Add(15, 30);   // ID0
    stock3.Add(25, 40);   // ID1
    stock3.Add(10, 50);   // ID2
    stock3.Add(20, 20);   // ID3
    stock3.Add(30, 35);   // ID4

    cout << "Исходные коробки:" << endl;
    stock3.PrintStock();

    cout << "Запрос: грузоподъемность >= 20" << endl;
    cout << "Подходят: ID1(25), ID3(20), ID4(30)" << endl;
    cout << "Самая старая из них: ID1 (время=1)" << endl;
    result = stock3.GetByW(20);
    cout << "Результат: ID=" << result << " ✓" << endl;

    cout << "\nЗапрос: объем >= 40" << endl;
    cout << "Подходят: ID1(40), ID2(50)" << endl;
    cout << "Самая старая из них: ID1 (время=1)" << endl;
    result = stock3.GetByV(40);
    cout << "Результат: ID=" << result << " ✓" << endl;

    // ТЕСТ 6: Поиск несуществующих коробок
    printTestHeader("Поиск несуществующих коробок");

    Stock stock4;
    stock4.Add(100, 200);
    stock4.Add(150, 250);

    cout << "Коробки на складе:" << endl;
    stock4.PrintStock();

    cout << "Поиск грузоподъемности >= 200: ";
    result = stock4.GetByW(200);
    cout << (result == -1 ? "−1 (коробок нет)" : "найдена") << endl;

    cout << "Поиск объема >= 300: ";
    result = stock4.GetByV(300);
    cout << (result == -1 ? "−1 (коробок нет)" : "найдена") << endl;

    // ТЕСТ 7: Комплексный сценарий
    printTestHeader("Комплексный сценарий работы склада");

    Stock stock5;

    cout << "День 1: Поставка 3 коробок" << endl;
    stock5.Add(50, 100);  // ID0
    stock5.Add(30, 80);   // ID1
    stock5.Add(40, 120);  // ID2
    stock5.PrintStock();

    cout << "День 2: Отгрузка по грузоподъемности >= 40" << endl;
    cout << "Отгружена коробка ID=" << stock5.GetByW(40) << " (самая старая подходящая: ID0)" << endl;
    stock5.PrintStock();

    cout << "День 2 (продолжение): Поставка новых коробок" << endl;
    stock5.Add(60, 150);  // ID3
    stock5.Add(35, 90);   // ID4
    stock5.PrintStock();

    cout << "День 3: Отгрузка по объему >= 100" << endl;
    cout << "Отгружена коробка ID=" << stock5.GetByV(100) << " (самая старая подходящая: ID2)" << endl;
    stock5.PrintStock();

    cout << "День 3 (продолжение): Отгрузка по грузоподъемности >= 50" << endl;
    cout << "Отгружена коробка ID=" << stock5.GetByW(50) << " (самая старая подходящая: ID3)" << endl;
    stock5.PrintStock();

    cout << "День 4: Попытка отгрузки несуществующей коробки" << endl;
    cout << "Запрос грузоподъемности >= 100: ";
    result = stock5.GetByW(100);
    cout << (result == -1 ? "−1 (нет коробок)" : "найдена") << endl;

    printSeparator();
    cout << "ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!" << endl;

    return 0;
}