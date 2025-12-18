#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;


struct rabbit {
    int height;
    int weight;
    string coat_color;
    bool disease;
    
    void print() const {
        cout << "Height: " << height << " cm | Weight: " << weight
            << " kg | Color: " << setw(10) << left << coat_color
            << " | Disease: " << (disease ? "Yes" : "No") << endl;
    }
};

rabbit* getRabbitArray(int size);
void deleteRabbitArray(rabbit* rabbits);
void printRabbitList(const rabbit* rabbits, int size);
rabbit* addRabbit(rabbit* rabbits, int& size, const rabbit& newRabbit);
rabbit* removeRabbit(rabbit* rabbits, int& size, int index);
void clearList(rabbit*& rabbits, int& size);
bool saveToFile(const rabbit* rabbits, int size, const string& filename);
rabbit* loadFromFile(const string& filename, int& size);
rabbit inputRabbitData();
void printMenu(int size);

int main()
{
    rabbit* rabbits = nullptr;
    int size = 0;
    int choice;
    bool running = true;

    while (running) {
        printMenu(size);
        cin >> choice;

        switch (choice) {
        case 1: {
            printRabbitList(rabbits, size);
            break;
        }

        case 2: {
            rabbit newRabbit = inputRabbitData();
            rabbits = addRabbit(rabbits, size, newRabbit);
            cout << "Rabbit added successfully!\n";
            break;
        }
        
        case 3: {
            if (size == 0) {
                cout << "List is empty!\n";
                break;
            }

            printRabbitList(rabbits, size);
            int index;
            cout << "Enter rabbit number to remove (1-" << size << "): ";
            cin >> index;

            if (index < 1 || index > size) {
                cout << "Invalid number!\n";
            }
            else {
                rabbits = removeRabbit(rabbits, size, index - 1);
                cout << "Rabbit removed successfully!\n";
            }
            break;
        }

        case 4: {
            clearList(rabbits, size);
            cout << "List cleared!\n";
            break;
        }

        case 5: { 
            if (size == 0) {
                cout << "List is empty! Nothing to save.\n";
                break;
            }

            string filename;
            cout << "Enter filename to save (e.g., rabbits.txt): ";
            cin >> filename;

            if (saveToFile(rabbits, size, filename)) {
                cout << "List saved to " << filename << " successfully!\n";
            }
            else {
                cout << "Error saving to file!\n";
            }
            break;
        }

        case 6: { 
            string filename;
            cout << "Enter filename to load (e.g., rabbits.txt): ";
            cin >> filename;

            int newSize;
            rabbit* loadedRabbits = loadFromFile(filename, newSize);

            if (loadedRabbits) {

                delete[] rabbits;

                rabbits = loadedRabbits;
                size = newSize;
                cout << "List loaded from " << filename << " successfully! "
                    << size << " rabbits loaded.\n";
            }
            else {
                cout << "Error loading from file or file is empty!\n";
            }
            break;
        }

        case 7: {
            running = false;
            cout << "Exiting program...\n";
            break;
        }

        default:
            cout << "Invalid choice! Please select 1-7.\n";
            break;
        }

        if (choice != 7) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}

rabbit* getRabbitArray(int size) {
    if (size <= 0) return nullptr;
    return new rabbit[size];
}

void deleteRabbitArray(rabbit* arr) {
    delete[] arr;
}

void printRabbitList(const rabbit* rabbits, int size) {
    if (size == 0) {
        cout << "List is empty\n";
        return;
    }

    cout << "\n=== RABBIT LIST (" << size << " rabbits) ===\n";
    cout << "==============================================\n";
    for (int i = 0; i <= size; i++) {
        cout << i + 1 << ": ";
        rabbits[i].print();
    }
    cout << "==============================================\n";
}



rabbit* addRabbit(rabbit* rabbits, int& size, const rabbit& newRabbit) {
    rabbit* newArray = new rabbit[size + 1];

    for (int i = 0; i < size; i++) {
        newArray[i] = rabbits[i];
    }

    newArray[size] = newRabbit;

    size++;

    delete[] rabbits;

    return newArray;
}

rabbit* removeRabbit(rabbit* rabbits, int& size, int index) {
    if (size <= 0 || index < 0 || index >= size) {
        return rabbits;
    }

    if (size == 1) {
        delete[] rabbits;
        size = 0;
        return nullptr;
    }

    rabbit* newArray = new rabbit[size - 1];

    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) {
            newArray[j++] = rabbits[i];
        }
    }

    size--;

    delete[] rabbits;

    return newArray;
}

void clearList(rabbit*& rabbits, int& size) {
    delete[] rabbits;
    rabbits = nullptr;
    size = 0;
}

bool saveToFile(const rabbit* rabbits, int size, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << size << "\n";

    for (int i = 0; i < size; i++) {
        file << rabbits[i].height << " "
            << rabbits[i].weight << " "
            << rabbits[i].coat_color << " "
            << rabbits[i].disease << "\n";
    }

    file.close();
    return true;
}

rabbit* loadFromFile(const string& filename, int& size) {
    ifstream file(filename);
    if (!file.is_open()) {
        return nullptr;
    }

    file >> size;
    if (size <= 0) {
        file.close();
        return nullptr;
    }

    rabbit* rabbits = new rabbit[size];

    for (int i = 0; i < size; i++) {
        file >> rabbits[i].height
            >> rabbits[i].weight
            >> rabbits[i].coat_color
            >> rabbits[i].disease;

        if (file.fail()) {
            delete[] rabbits;
            file.close();
            return nullptr;
        }
    }

    file.close();
    return rabbits;
}

rabbit inputRabbitData() {
    rabbit rabbit;

    cout << "\n=== ENTER RABBIT DATA ===\n";
    cout << "Height (cm): ";
    cin >> rabbit.height;

    cout << "Weight (kg): ";
    cin >> rabbit.weight;

    cout << "Color: ";
    cin.ignore();
    getline(cin, rabbit.coat_color);

    cout << "Has disease? (1 for Yes, 0 for No): ";
    cin >> rabbit.disease;

    return rabbit;
}

void printMenu(int size) {
    cout << "\n=== RABBIT LIST MANAGER ===\n";
    cout << "Current list size: " << size << " rabbits\n";
    cout << "1. Show current list\n";
    cout << "2. Add new rabbit\n";
    cout << "3. Remove rabbit\n";
    cout << "4. Clear list\n";
    cout << "5. Save list to file\n";
    cout << "6. Load list from file\n";
    cout << "7. Exit program\n";
    cout << "============================\n";
    cout << "Select option (1-7): ";
}
