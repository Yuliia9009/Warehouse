#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Product.h"
#include <vector>
#include <string>
#include <set>

class Warehouse {
private:
    std::vector<Product> products;
    std::string inventoryFile = "inventory.txt";

    void loadFromFile();
    void saveToFile();

public:
    Warehouse();
    void addProduct(const Product &product);
    bool removeProduct(const std::string &name);
    bool replaceProduct(const std::string &name, const Product &newProduct);
    std::vector<Product> searchByName(const std::string &name) const;
    std::vector<Product> searchByManufacturer(const std::string &manufacturer) const;
    std::vector<Product> searchByPrice(double price) const;
    std::vector<Product> searchByCategory(const std::string &category) const;
    std::vector<Product> searchByArrivalDate(const std::tm &date) const;
    std::vector<Product> searchByExpiryDate(const std::tm &date) const;
    void sortByPrice();
    void sortByCategory();
    void printInventory() const;
    std::set<std::string> getUniqueCategories() const;  // New function
};

#endif
