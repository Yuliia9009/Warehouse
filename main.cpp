#include "Warehouse.h"
#include "Product.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <set>

void printMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Добавить товар\n";
    std::cout << "2. Удалить товар\n";
    std::cout << "3. Заменить товар\n";
    std::cout << "4. Найти товар\n";
    std::cout << "5. Сортировать товары\n";
    std::cout << "6. Показать инвентарь\n";
    std::cout << "0. Выход\n";
}

void printCategoryMenu() {
    std::cout << "Выберите категорию:\n";
    std::cout << "1. Автозапчасти\n";
    std::cout << "2. Расходные материалы\n";
    std::cout << "3. Автокосметика\n";
    std::cout << "4. Жидкости\n";
}

std::string getCategory(int categoryChoice) {
    switch (categoryChoice) {
        case 1: return "автозапчасти";
        case 2: return "расходные материалы";
        case 3: return "автокосметика";
        case 4: return "жидкости";
        default: return "неизвестно";
    }
}

std::tm parseDate(const std::string &dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return tm;
}

std::tm getExpiryDate(const std::string &dateStr) {
    if (dateStr == "none") {
        std::tm expiryDate = {};
        expiryDate.tm_year = 2999 - 1900;
        expiryDate.tm_mon = 11;
        expiryDate.tm_mday = 31;
        return expiryDate;
    } else {
        return parseDate(dateStr);
    }
}

int main() {
    Warehouse warehouse;
    int choice;

    do {
        printMenu();
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистить буфер ввода

        if (choice == 1) {
            std::string name, manufacturer, arrivalDateStr, expiryDateStr, OEM, comment;
            double price;
            int categoryChoice;
            std::cout << "Введите название товара: ";
            std::getline(std::cin, name);
            std::cout << "Введите производителя: ";
            std::getline(std::cin, manufacturer);
            std::cout << "Введите цену: ";
            std::cin >> price;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printCategoryMenu();
            std::cout << "Введите номер категории: ";
            std::cin >> categoryChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите дату поступления (гггг-мм-дд): ";
            std::getline(std::cin, arrivalDateStr);
            std::cout << "Введите срок годности (гггг-мм-дд) или 'none': ";
            std::getline(std::cin, expiryDateStr);
            std::cout << "Введите OEM: ";
            std::getline(std::cin, OEM);
            std::cout << "Введите комментарий: ";
            std::getline(std::cin, comment);

            std::tm arrivalDate = parseDate(arrivalDateStr);
            std::tm expiryDate = getExpiryDate(expiryDateStr);

            Product product(name, manufacturer, price, getCategory(categoryChoice), arrivalDate, expiryDate, OEM, comment);
            warehouse.addProduct(product);
        } else if (choice == 2) {
            std::string name;
            std::cout << "Введите название товара для удаления: ";
            std::getline(std::cin, name);
            if (warehouse.removeProduct(name)) {
                std::cout << "Товар успешно удален.\n";
            } else {
                std::cout << "Товар не найден.\n";
            }
        } else if (choice == 3) {
            std::string name, newName, newManufacturer, newArrivalDateStr, newExpiryDateStr, newOEM, newComment;
            double newPrice;
            int newCategoryChoice;
            std::cout << "Введите название товара для замены: ";
            std::getline(std::cin, name);
            std::cout << "Введите новое название товара: ";
            std::getline(std::cin, newName);
            std::cout << "Введите нового производителя: ";
            std::getline(std::cin, newManufacturer);
            std::cout << "Введите новую цену: ";
            std::cin >> newPrice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printCategoryMenu();
            std::cout << "Введите новый номер категории: ";
            std::cin >> newCategoryChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите новую дату поступления (гггг-мм-дд): ";
            std::getline(std::cin, newArrivalDateStr);
            std::cout << "Введите новый срок годности (гггг-мм-дд) или 'none': ";
            std::getline(std::cin, newExpiryDateStr);
            std::cout << "Введите новый OEM: ";
            std::getline(std::cin, newOEM);
            std::cout << "Введите новый комментарий: ";
            std::getline(std::cin, newComment);

            std::tm newArrivalDate = parseDate(newArrivalDateStr);
            std::tm newExpiryDate = getExpiryDate(newExpiryDateStr);

            Product newProduct(newName, newManufacturer, newPrice, getCategory(newCategoryChoice), newArrivalDate, newExpiryDate, newOEM, newComment);
            if (warehouse.replaceProduct(name, newProduct)) {
                std::cout << "Товар успешно заменен.\n";
            } else {
                std::cout << "Товар не найден.\n";
            }
        } else if (choice == 4) {
            int searchChoice;
            std::cout << "1. Поиск по названию\n";
            std::cout << "2. Поиск по производителю\n";
            std::cout << "3. Поиск по цене\n";
            std::cout << "4. Поиск по категории\n";
            std::cout << "Введите ваш выбор: ";
            std::cin >> searchChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (searchChoice == 1) {
                std::string name;
                std::cout << "Введите название товара: ";
                std::getline(std::cin, name);
                std::vector<Product> results = warehouse.searchByName(name);
                for (const auto &product : results) {
                    std::cout << product.toString() << std::endl;
                }
            } else if (searchChoice == 2) {
                std::string manufacturer;
                std::cout << "Введите производителя: ";
                std::getline(std::cin, manufacturer);
                std::vector<Product> results = warehouse.searchByManufacturer(manufacturer);
                for (const auto &product : results) {
                    std::cout << product.toString() << std::endl;
                }
            } else if (searchChoice == 3) {
                double price;
                std::cout << "Введите цену: ";
                std::cin >> price;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::vector<Product> results = warehouse.searchByPrice(price);
                for (const auto &product : results) {
                    std::cout << product.toString() << std::endl;
                }
            } else if (searchChoice == 4) {
                std::set<std::string> uniqueCategories = warehouse.getUniqueCategories();
                std::cout << "Доступные категории:\n";
                int categoryIndex = 1;
                for (const auto &category : uniqueCategories) {
                    std::cout << categoryIndex << ". " << category << std::endl;
                    categoryIndex++;
                }
                std::cout << "Введите номер категории: ";
                int categoryChoice;
                std::cin >> categoryChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string chosenCategory;
                categoryIndex = 1;
                for (const auto &category : uniqueCategories) {
                    if (categoryIndex == categoryChoice) {
                        chosenCategory = category;
                        break;
                    }
                    categoryIndex++;
                }
                std::vector<Product> results = warehouse.searchByCategory(chosenCategory);
                for (const auto &product : results) {
                    std::cout << product.toString() << std::endl;
                }
            }
        } else if (choice == 5) {
            int sortChoice;
            std::cout << "1. Сортировать по цене\n";
            std::cout << "2. Сортировать по категории\n";
            std::cout << "Введите ваш выбор: ";
            std::cin >> sortChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (sortChoice == 1) {
                warehouse.sortByPrice();
                std::cout << "Товары отсортированы по цене.\n";
            } else if (sortChoice == 2) {
                warehouse.sortByCategory();
                std::cout << "Товары отсортированы по категории.\n";
            }
        } else if (choice == 6) {
            warehouse.printInventory();
        }
    } while (choice != 0);

    return 0;
}
