#include "Warehouse.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <set>

Warehouse::Warehouse() {
    loadFromFile();
}

void Warehouse::loadFromFile() {
    std::ifstream file(inventoryFile);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла для чтения: " << inventoryFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            products.push_back(Product::fromString(line));
        }
    }
    file.close();
}

void Warehouse::saveToFile() {
    std::ofstream file(inventoryFile);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла для записи: " << inventoryFile << std::endl;
        return;
    }

    for (const auto &product : products) {
        file << product.toString() << std::endl;
    }
    file.close();
}

void Warehouse::addProduct(const Product &product) {
    products.push_back(product);
    saveToFile();
}

bool Warehouse::removeProduct(const std::string &name) {
    auto it = std::remove_if(products.begin(), products.end(), [&name](const Product &product) {
        return product.name == name;
    });

    if (it != products.end()) {
        products.erase(it, products.end());
        saveToFile();
        return true;
    }
    return false;
}

bool Warehouse::replaceProduct(const std::string &name, const Product &newProduct) {
    for (auto &product : products) {
        if (product.name == name) {
            product = newProduct;
            saveToFile();
            return true;
        }
    }
    return false;
}

std::vector<Product> Warehouse::searchByName(const std::string &name) const {
    std::vector<Product> results;
    for (const auto &product : products) {
        if (product.name.find(name) != std::string::npos) {
            results.push_back(product);
        }
    }
    return results;
}

std::vector<Product> Warehouse::searchByManufacturer(const std::string &manufacturer) const {
    std::vector<Product> results;
    for (const auto &product : products) {
        if (product.manufacturer.find(manufacturer) != std::string::npos) {
            results.push_back(product);
        }
    }
    return results;
}

std::vector<Product> Warehouse::searchByPrice(double price) const {
    std::vector<Product> results;
    for (const auto &product : products) {
        if (product.price == price) {
            results.push_back(product);
        }
    }
    return results;
}

std::vector<Product> Warehouse::searchByCategory(const std::string &category) const {
    std::vector<Product> results;
    for (const auto &product : products) {
        if (product.category.find(category) != std::string::npos) {
            results.push_back(product);
        }
    }
    return results;
}

std::vector<Product> Warehouse::searchByArrivalDate(const std::tm &date) const {
    std::vector<Product> results;
    for (const auto &product : products) {
        if (std::difftime(mktime(const_cast<std::tm*>(&product.arrivalDate)), mktime(const_cast<std::tm*>(&date))) == 0) {
            results.push_back(product);
        }
    }
    return results;
}

std::vector<Product> Warehouse::searchByExpiryDate(const std::tm &date) const {
    std::vector<Product> results;
    for (const auto &product : products) {
        if (std::difftime(mktime(const_cast<std::tm*>(&product.expiryDate)), mktime(const_cast<std::tm*>(&date))) == 0) {
            results.push_back(product);
        }
    }
    return results;
}

void Warehouse::sortByPrice() {
    std::sort(products.begin(), products.end(), [](const Product &a, const Product &b) {
        return a.price < b.price;
    });
    saveToFile();
}

void Warehouse::sortByCategory() {
    std::sort(products.begin(), products.end(), [](const Product &a, const Product &b) {
        return a.category < b.category;
    });
    saveToFile();
}

void Warehouse::printInventory() const {
    for (const auto &product : products) {
        std::cout << product.toString() << std::endl;
    }
}

std::set<std::string> Warehouse::getUniqueCategories() const {
    std::set<std::string> uniqueCategories;
    for (const auto &product : products) {
        uniqueCategories.insert(product.category);
    }
    return uniqueCategories;
}
