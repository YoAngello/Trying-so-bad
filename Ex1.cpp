#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

enum percent {
    PERCENT_5 = 5,
    PERCENT_10 = 10,
    PERCENT_15 = 15,
    PERCENT_20 = 20,
    PERCENT_30 = 30,
    PERCENT_35 = 35
};

enum class section {
    FOOD,
    DRINKS,
    CEREALS,
    CLOTH,
    FURNITURE,
    KITCHENWARE,
    SPORTS_SHOP
};

struct storage {
    string name;
    int price;
    int count;
    section section_name;
    percent discount_percent;

    void print() const {
        cout << "Name: " << name
            << ", Price: " << price
            << ", Count: " << count
            << ", Discount: " << static_cast<int>(discount_percent) << "%" << endl;
    }
};

section stringToSection(const string& str) {
    if (str == "FOOD")
        return section::FOOD;
    if (str == "DRINKS")
        return section::DRINKS;
    if (str == "CEREALS")
        return section::CEREALS;
    if (str == "CLOTH")
        return section::CLOTH;
    if (str == "FURNITURE")
        return section::FURNITURE;
    if (str == "KITCHENWARE")
        return  section::KITCHENWARE;
    if (str == "SPORTS_SHOP")
        return section::SPORTS_SHOP;

    throw invalid_argument("Unknown section: " + str);
}

percent stringToPercent(const string& str) {
    int value = stoi(str);

    switch (value) {
    case 5: return PERCENT_5;
    case 10: return PERCENT_10;
    case 15: return PERCENT_15;
    case 20: return PERCENT_20;
    case 30: return PERCENT_30;
    case 35: return PERCENT_35;
    default:
        throw invalid_argument("Unacceptable discount percentage: " + str);
    }
};

string sectionToString(section s) {
    switch (s) {
    case section::FOOD: return "FOOD";
    case section::DRINKS: return "DRINKS";
    case section::CEREALS: return "CEREALS";
    case section::CLOTH: return "CLOTH";
    case section::FURNITURE: return "FURNITURE";
    case section::KITCHENWARE: return "KITCHENWARE";
    case section::SPORTS_SHOP: return "SPORTS_SHOP";
    default: return "UNKNOWN";
    }
}

// Функция для чтения данных из файла и заполнения массива
storage* fillArrayFromFile(string& filename, int& count) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "File opening error: " << filename << std::endl;
        count = 0;
        return nullptr;
    }

    vector<string> lines;
    string line;

    // получаем строки с проверкой
    while (getline(file, line)) {
        if (!line.empty() && line[0] != '#') {
            lines.push_back(line);
        }
    }

    file.close();

    // проверка на пустоту
    if (lines.empty()) {
        cerr << "The file is empty or contains only comments!" << endl;
        count = 0;
        return nullptr;
    }

    // создаем массив
    storage* storageArray = new storage[lines.size()];

    for (size_t i = 0; i < lines.size(); i++) {
        stringstream ss(lines[i]);
        vector<string> tokens;
        string token;

        // проходимся по строке до знака и включаем в массив
        while (getline(ss, token, ';')) {
            tokens.push_back(token);
        }

        // проверка на наличие 5 элементов
        if (tokens.size() != 5) {
            cerr << "Error in line " << i + 1
                << ": 5 fields expected, received " << tokens.size()
                << " Line: " << lines[i] << endl;
            continue;
        }

        try {
            storageArray[i].name = tokens[0];
            storageArray[i].price = stoi(tokens[1]);
            storageArray[i].count = stoi(tokens[2]);
            storageArray[i].section_name = stringToSection(tokens[3]);
            storageArray[i].discount_percent = stringToPercent(tokens[4]);
        }
        catch (const exception& e) {
            cerr << "Error parsing line " << i + 1 << ": " << e.what() << endl;
            // Устанавливаем значения по умолчанию
            storageArray[i].name = "ERROR";
            storageArray[i].price = 0;
            storageArray[i].count = 0;
            storageArray[i].section_name = section::FOOD;
            storageArray[i].discount_percent = PERCENT_5;
        }
    }

    count = static_cast<int>(lines.size());
    return storageArray;
}

// поиск по названию в вектор
vector<int> findByName(const storage* arr, int size, const string& name) {
    vector<int> results;

    for (int i = 0; i < size; i++) {
        if (arr[i].name == name) {
            results.push_back(i);
        }
    }

    return results;
}

// поиск по цене(больше указанной)
vector<int> findByPriceGreater(const storage* arr, int size, int price) {
    vector<int> results;

    for (int i = 0; i < size; i++) {
        if (arr[i].price > price) {
            results.push_back(i);
        }
    }

    return results;
}

// поиск по цене(меньше указанной)
vector<int> findByPriceLess(const storage* arr, int size, int price) {
    vector<int> results;

    for (int i = 0; i < size; i++) {
        if (arr[i].price < price) {
            results.push_back(i);
        }
    }

    return results;
}

// создание тестового файла
void createTestFile(const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        file << "# Format: name;price;count;section;discount\n";
        file << "Bread;50;100;FOOD;5\n";
        file << "Milk;80;50;DRINKS;10\n";
        file << "Rice;120;200;CEREALS;15\n";
        file << "T-Shirt;500;30;CLOTH;20\n";
        file << "Chair;1500;10;FURNITURE;30\n";
        file << "Pan;800;25;KITCHENWARE;35\n";
        file << "Ball;300;40;SPORTS_SHOP;10\n";
        file << "Juice;90;60;DRINKS;15\n";
        file << "Pants;700;15;CLOTH;20\n";
        file << "Table;2500;5;FURNITURE;35\n";
        file << "Mug;150;100;KITCHENWARE;5\n";
        file << "Sneakers;1200;20;SPORTS_SHOP;30\n";

        file.close();
        cout << "Test file created: " << filename << endl;
    }
    else {
        cerr << "Error creating test file!" << endl;
    }
}

// менюшка
void printMenu() {
    cout << "\n=== SEARCH MENU ===" << endl;
    cout << "1. Search by exact name" << endl;
    cout << "2. Items with price greater than" << endl;
    cout << "3. Items with price less than" << endl;
    cout << "4. Show all items" << endl;
    cout << "0. Exit" << endl;
    cout << "Select action: ";
}

// вывод всех товаров
void printAllItems(const storage* arr, int size) {
    if (size == 0) {
        cout << "Database is empty!" << endl;
        return;
    }

    cout << "\n=== ALL ITEMS IN DATABASE ===" << endl;
    cout << "Total: " << size << " item(s)" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        arr[i].print();
        cout << "   Section: " << sectionToString(arr[i].section_name) << endl;
    }
}

// вывод результатов поиска
void printSearchResults(const storage* arr, const vector<int>& indices, const string& searchType) {
    if (indices.empty()) {
        cout << "\nNo results found for query: '" << searchType << "'" << endl;
        return;
    }

    cout << "\n=== Search Results: " << searchType << " ===" << endl;
    cout << "Found: " << indices.size() << " item(s)" << endl;
    cout << "----------------------------------------" << endl;

    for (int idx : indices) {
        cout << idx + 1 << ". ";
        arr[idx].print();
        cout << "   Section: " << sectionToString(arr[idx].section_name) << endl;
    }
    cout << "========================================" << endl;
}

int main() {
    int arrSize = 0;
    string file = "test.txt";

    createTestFile(file);

    storage* storageArray = fillArrayFromFile(file, arrSize);

    if (!storageArray || arrSize == 0) {
        cerr << "Failed to load data from file!" << endl;
        return 1;
    }

    cout << "Successfully loaded " << arrSize << " items from file." << endl;

    int choice;
    bool running = true;

    while (running) {
        printMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string searchName;
            cout << "Enter exact item name: ";
            getline(cin, searchName);

            vector<int> results = findByName(storageArray, arrSize, searchName);
            printSearchResults(storageArray, results, "Name: " + searchName);
            break;
        }

        case 2: {
            int price;
            cout << "Enter minimum price: ";
            cin >> price;

            vector<int> results = findByPriceGreater(storageArray, arrSize, price);
            printSearchResults(storageArray, results, "Price > " + to_string(price));
            break;
        }

        case 3: {
            int price;
            cout << "Enter maximum price: ";
            cin >> price;

            vector<int> results = findByPriceLess(storageArray, arrSize, price);
            printSearchResults(storageArray, results, "Price < " + to_string(price));
            break;
        }

        case 4: {
            printAllItems(storageArray, arrSize);
            break;
        }

        case 0: {
            running = false;
            cout << "Exiting program..." << endl;
            break;
        }

        default: {
            cout << "Invalid choice! Try again." << endl;
            break;
        }
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }

    delete[] storageArray;
    return 0;
}