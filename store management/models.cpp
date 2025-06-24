#include "models.h"
#include <string>
#include <iomanip> // precision for price output 4.50000 -> 4.50

Date::Date() {
    day = 1;
    month = 1;
    year = 2000;
}

Date::Date(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

std::string Date::to_string() {
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}

Product::Product(std::string bc, std::string n, int q, double p) {
    barcode = bc;
    name = n;
    quantity = q;
    price = p;
}

std::string Product::to_string() {
    std::ostringstream oss;
    oss << barcode << " " << name << " " << quantity << " "
        << std::fixed << std::setprecision(2) << price;
    return oss.str();
}

Order::Order() {
    order_date = Date();
}

Order::Order(std::vector<Product> p_list, Date d) {
    products = p_list;
    order_date = d;
}

std::string Order::to_string() {
    std::string result = order_date.to_string() + "\n";
    for (int i = 0; i < products.size(); i++) {
        result += products[i].to_string() + "\n";
    }
    result += "\n";
    return result;
}

