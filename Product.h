#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <ctime>

class Product {
public:
    std::string name;
    std::string manufacturer;
    double price;
    std::string category;
    std::tm arrivalDate;
    std::tm expiryDate;
    std::string OEM;
    std::string comment;

    Product(const std::string &name, const std::string &manufacturer, double price, const std::string &category, const std::tm &arrivalDate, const std::tm &expiryDate, const std::string &OEM, const std::string &comment);
    Product() = default;

    std::string toString() const;
    static Product fromString(const std::string &data);
};

#endif 
