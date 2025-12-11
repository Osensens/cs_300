//How to complie: g++ final_2.cpp -std=c++11 -o final_2
// how to run: ./final_2


#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

// struct product

struct Product {
    std::string name;
    int quantity;
    double price;
};

// Helper: print products
void printProducts(const std::vector<Product>& products, const std::string& title) {
    std::cout << "--- " << title << " ---\n";
    for (const auto& p : products) {
        std::cout << p.name
                  << " (qty=" << p.quantity
                  << ", price=" << p.price << ")\n";
    }
    std::cout << std::endl;
}

// ========================= 1. Initialization =========================

void initializeInventory(std::vector<Product>& products,
                         std::unordered_map<std::string, int>& nameToIndex) 
{
    products.clear();
    nameToIndex.clear();

    products.push_back({"Milk", 5, 2.99});
    products.push_back({"Bread", 12, 1.49});
    products.push_back({"Eggs", 30, 3.50});
    products.push_back({"Apples", 8, 0.99});
    products.push_back({"Chicken", 3, 7.99});

    for (int i = 0; i < products.size(); ++i) {
        nameToIndex[products[i].name] = i;
    }
}

// ========================= 2. Fast item lookup =========================

Product* findProduct(const std::string& name,
                     std::vector<Product>& products,
                     std::unordered_map<std::string, int>& nameToIndex)
{
    auto it = nameToIndex.find(name);
    if (it == nameToIndex.end()) return nullptr;
    return &products[it->second];
}

// ========================= 3. Low-stock products =========================

std::vector<Product> filter_lower(const std::vector<Product>& products, int threshold) {
    std::vector<Product> result;

    for (const auto& p : products) {
        if (p.quantity < threshold) {
            result.push_back(p);
        }
    }

    return result;
}

// ========================= 4. Sort =========================

void sortAndRefresh(std::vector<Product>& products,
                    std::unordered_map<std::string, int>& nameToIndex)
{
    // Sort by quantity ascending
    std::sort(products.begin(), products.end(),
              [](const Product& a, const Product& b) {
                  return a.quantity < b.quantity;
              });

    // update nameToIndex accordingly
    nameToIndex.clear();
    for (int i = 0; i < products.size(); ++i) {
        nameToIndex[products[i].name] = i;
    }
}

// ========================= 5. Increase stock =========================

void restockProducts(const std::vector<Product>& lowStock,
                     int amount,
                     std::vector<Product>& products,
                     std::unordered_map<std::string, int>& nameToIndex)
{
    for (const auto& item : lowStock) {
        auto it = nameToIndex.find(item.name);
        if (it != nameToIndex.end()) {
            products[it->second].quantity += amount;
        }
    }
}

int main() {
    std::vector<Product> products;
    std::unordered_map<std::string, int> nameToIndex;

    // 1. Initialization
    initializeInventory(products, nameToIndex);
    printProducts(products, "Initial inventory");

    // Show the name-to-index map
    std::cout << "--- Name to Index Map ---\n";
    for (const auto& pair : nameToIndex) {
        std::cout << pair.first << " -> " << pair.second << "\n";
    }
    std::cout << std::endl;

    // 2. Fast item lookup demo
    std::cout << "--- Fast item lookup demo ---\n";
    const std::string lookupName1 = "Milk";
    const std::string lookupName2 = "Unknown";

    if (Product* p = findProduct(lookupName1, products, nameToIndex)) {
        std::cout << "Found " << lookupName1
                  << ": qty=" << p->quantity
                  << ", price=" << p->price << "\n";
    } else {
        std::cout << lookupName1 << " not found.\n";
    }

    if (Product* p = findProduct(lookupName2, products, nameToIndex)) {
        std::cout << "Found " << lookupName2
                  << ": qty=" << p->quantity
                  << ", price=" << p->price << "\n";
    } else {
        std::cout << lookupName2 << " not found.\n";
    }
    std::cout << std::endl;

    // 3. Low-stock products (threshold = 10)
    auto lowStock = filter_lower(products, 10);
    printProducts(lowStock, "Low-stock products (quantity < 10)");

    // 4. Sort by quantity (ascending)
    sortAndRefresh(products, nameToIndex);
    printProducts(products, "Inventory sorted by quantity (ascending)");

    // 5. Increase stock for low-stock products (e.g., +20 each)
    restockProducts(lowStock, 20, products, nameToIndex);
    printProducts(products, "Inventory after restocking");

    return 0;
}