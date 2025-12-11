//how to complie: g++ final_1.cpp -std=c++11 -o final_1
//how to run ./final_1


#include <iostream>
#include <string>
#include <unordered_map>

// =======================================================
// Item (Base Class)
// =======================================================
class Item {
    // TODO
protected:
    std::string title;
    bool borrowed;
    int dueDays;

public:
    Item(const std::string& t) : title(t), borrowed(false), dueDays(0) {}
    virtual ~Item() = default;

    std::string getTitle() const { return title; }
    bool available() const { return !borrowed; }

    void borrowItem(int days) {
        borrowed = true;
        dueDays = days;
    }

    void giveBack() {
        borrowed = false;
        dueDays = 0;
    }

    virtual std::string info() const = 0;
    int getDueDays() const { return dueDays; }
};

// =======================================================
// Book
// =======================================================
class Book : public Item {
    // TODO
private:
    std::string author;
    int year;

public:
    Book(const std::string& t, const std::string& a, int y)
        : Item(t), author(a), year(y) {}

    std::string info() const override {
        return "Book: " + title + " by " + author + " (" + std::to_string(year) + ")";
    }
};

// =======================================================
// Magazine
// =======================================================
class Magazine : public Item {
    // TODO
private:
    int issue;

public:
    Magazine(const std::string& t, int i)
        : Item(t), issue(i) {}

    std::string info() const override {
        return "Magazine: " + title + ", Issue " + std::to_string(issue);
    }
};

// =======================================================
// Library
// =======================================================
class Library {
    // TODO
private:
    std::unordered_map<std::string, Item*> items;

public:
    ~Library() {
        for (auto& p : items)
            delete p.second;
    }

    void addItem(Item* item) {
        items[item->getTitle()] = item;
    }

    bool checkAvailability(const std::string& title) const {
        auto it = items.find(title);
        if (it == items.end()) return false;
        return it->second->available();
    }

    bool borrowItem(const std::string& title, int days) {
        auto it = items.find(title);
        if (it == items.end()) return false;
        if (!it->second->available()) return false;
        it->second->borrowItem(days);
        return true;
    }

    bool returnItem(const std::string& title) {
        auto it = items.find(title);
        if (it == items.end()) return false;
        if (it->second->available()) return false;
        it->second->giveBack();
        return true;
    }

    void listItems() const {
        for (const auto& p : items) {
            const Item* item = p.second;
            if (item->available())
                std::cout << item->info() << " — Available\n";
            else
                std::cout << item->info() << " — Borrowed for "
                          << item->getDueDays() << " days\n";
        }
    }
};

// =======================================================
// main(): test
// =======================================================
int main() {
    Library lib;

    // ----- Add Items -----
    lib.addItem(new Book("The Hobbit", "Tolkien", 1937));
    lib.addItem(new Book("Clean Code", "Martin", 2008));
    lib.addItem(new Magazine("Science Weekly", 42));

    std::cout << "--- Initial Items ---\n";
    lib.listItems();

    // ----- Check Availability -----
    std::cout << "\nChecking availability of 'Clean Code': ";
    std::cout << (lib.checkAvailability("Clean Code") ? "Available\n" : "Not available\n");

    // ----- Borrow Success -----
    std::cout << "\nBorrowing 'Clean Code' for 5 days...\n";
    bool ok = lib.borrowItem("Clean Code", 5);
    std::cout << (ok ? "Borrow successful.\n" : "Borrow failed.\n");
    lib.listItems();

    // ----- Borrow Fail (already borrowed) -----
    std::cout << "\nTrying to borrow 'Clean Code' again...\n";
    ok = lib.borrowItem("Clean Code", 3);
    std::cout << (ok ? "Borrow successful.\n" : "Borrow failed.\n");

    // ----- Return Success -----
    std::cout << "\nReturning 'Clean Code'...\n";
    ok = lib.returnItem("Clean Code");
    std::cout << (ok ? "Return successful.\n" : "Return failed.\n");
    lib.listItems();

    // ----- Return Fail (not borrowed) -----
    std::cout << "\nTrying to return 'Clean Code' again...\n";
    ok = lib.returnItem("Clean Code");
    std::cout << (ok ? "Return successful.\n" : "Return failed.\n");

    // ----- Check availability again -----
    std::cout << "\nChecking availability of 'Clean Code' again: ";
    std::cout << (lib.checkAvailability("Clean Code") ? "Available\n" : "Not available\n");

    return 0;
}
