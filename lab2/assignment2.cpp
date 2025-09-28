#include <iostream>
#include <string>

//  Custom strlen and strcpy 

size_t myStrlen(const char* s) {
    size_t length = 0;
    while (*s != '\0') {
        ++length;
        ++s;
    }
    return length;
}

void myStrcpy(char* dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0'; 
}

//  Count Character Occurrences

// std::string
int countChar(const std::string& s, char target) {
    int count = 0;
    for (char c : s) {
        if (c == target) ++count;
    }
    return count;
}

// C-style string
int countChar(const char* s, char target) {
    int count = 0;
    while (*s != '\0') {
        if (*s == target) ++count;
        ++s;
    }
    return count;
}

//  Array Statistics 

int findMax(const int arr[], int size) {
    int maxVal = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

double computeAverage(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) sum += arr[i];
    return static_cast<double>(sum) / size;
}

void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; ++i) {
        std::swap(arr[i], arr[size - 1 - i]);
    }
}

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

//  Simple Address Book 

struct Contact {
    std::string name;
    std::string phone;
    int age;
};

void addContact(Contact contacts[], int &count) {
    if (count >= 10) {
        std::cout << "Address book full!\n";
        return;
    }
    std::cout << "Enter name: ";
    std::cin >> contacts[count].name;
    std::cout << "Enter phone: ";
    std::cin >> contacts[count].phone;
    std::cout << "Enter age: ";
    std::cin >> contacts[count].age;
    ++count;
    std::cout << "Contact added.\n";
}

void deleteContact(Contact contacts[], int &count, const std::string& name) {
    for (int i = 0; i < count; ++i) {
        if (contacts[i].name == name) {
            for (int j = i; j < count - 1; ++j) {
                contacts[j] = contacts[j + 1];
            }
            --count;
            std::cout << "Contact deleted.\n";
            return;
        }
    }
    std::cout << "Contact not found.\n";
}

void listContacts(const Contact contacts[], int count) {
    if (count == 0) {
        std::cout << "No contacts.\n";
        return;
    }
    for (int i = 0; i < count; ++i) {
        std::cout << i + 1 << ". "
                  << contacts[i].name << " | "
                  << contacts[i].phone << " | "
                  << contacts[i].age << "\n";
    }
}

void searchByName(const Contact contacts[], int count, const std::string& name) {
    for (int i = 0; i < count; ++i) {
        if (contacts[i].name == name) {
            std::cout << "Found: "
                      << contacts[i].name << " | "
                      << contacts[i].phone << " | "
                      << contacts[i].age << "\n";
            return;
        }
    }
    std::cout << "Contact not found.\n";
}

//   test Program 

int main() {
    // test 1
    std::cout << "=== Part 1: Custom strlen & strcpy ===\n";
    const char* inputStr = "UAB-CS";
    std::cout << "Input string: " << inputStr << "\n";
    std::cout << "myStrlen: " << myStrlen(inputStr) << "\n";
    char dest[50];
    myStrcpy(dest, inputStr);
    std::cout << "After myStrcpy, destination: " << dest << "\n\n";

    // test 2
    std::cout << "=== Part 2: Count Character Occurrences ===\n";
    std::string s = "UAB-CS-UAB";
    char target = 'A';
    std::cout << "String: " << s << "\nTarget char: " << target << "\n";
    std::cout << "std::string version: " << countChar(s, target) << "\n";
    std::cout << "C-string version: " << countChar(s.c_str(), target) << "\n\n";

    // test 3
    std::cout << "=== Part 3: Array Statistics ===\n";
    int numbers[10];
    std::cout << "Enter 10 integers: ";
    for (int i = 0; i < 10; ++i) std::cin >> numbers[i];

    std::cout << "Max: " << findMax(numbers, 10) << "\n";
    std::cout << "Average: " << computeAverage(numbers, 10) << "\n";
    reverseArray(numbers, 10);
    std::cout << "Reversed array: ";
    printArray(numbers, 10);
    std::cout << "\n";

    // test 4
    std::cout << "=== Part 4: Simple Address Book ===\n";
    Contact contacts[10];
    int count = 0, choice;

    do {
        std::cout << "\nMenu:\n"
                  << "1. Add contact\n"
                  << "2. Delete contact\n"
                  << "3. List contacts\n"
                  << "4. Search by name\n"
                  << "0. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) addContact(contacts, count);
        else if (choice == 2) {
            std::string name;
            std::cout << "Enter name to delete: ";
            std::cin >> name;
            deleteContact(contacts, count, name);
        }
        else if (choice == 3) listContacts(contacts, count);
        else if (choice == 4) {
            std::string name;
            std::cout << "Enter name to search: ";
            std::cin >> name;
            searchByName(contacts, count, name);
        }
    } while (choice != 0);

    return 0;
}
