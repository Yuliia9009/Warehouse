#include "Product.h"
#include <sstream>
#include <iomanip>

Product::Product(const std::string &name, const std::string &manufacturer, double price, const std::string &category, const std::tm &arrivalDate, const std::tm &expiryDate, const std::string &OEM, const std::string &comment)
    : name(name), manufacturer(manufacturer), price(price), category(category), arrivalDate(arrivalDate), expiryDate(expiryDate), OEM(OEM), comment(comment) {}

std::string Product::toString() const {
    std::ostringstream oss;
    oss << name << ';' << manufacturer << ';' << price << ';' << category << ';'
        << std::put_time(&arrivalDate, "%Y-%m-%d") << ';' << std::put_time(&expiryDate, "%Y-%m-%d") << ';'
        << OEM << ';' << comment;
    return oss.str();
}

Product Product::fromString(const std::string &data) {
    std::istringstream iss(data);
    std::string name, manufacturer, priceStr, category, arrivalDateStr, expiryDateStr, OEM, comment;

    std::getline(iss, name, ';');
    std::getline(iss, manufacturer, ';');
    std::getline(iss, priceStr, ';');
    std::getline(iss, category, ';');
    std::getline(iss, arrivalDateStr, ';');
    std::getline(iss, expiryDateStr, ';');
    std::getline(iss, OEM, ';');
    std::getline(iss, comment, ';');

    double price = std::stod(priceStr);

    std::tm arrivalDate = {};
    std::tm expiryDate = {};

    std::istringstream arrivalDateStream(arrivalDateStr);
    std::istringstream expiryDateStream(expiryDateStr);

    arrivalDateStream >> std::get_time(&arrivalDate, "%Y-%m-%d");
    expiryDateStream >> std::get_time(&expiryDate, "%Y-%m-%d");

    return Product(name, manufacturer, price, category, arrivalDate, expiryDate, OEM, comment);
}
