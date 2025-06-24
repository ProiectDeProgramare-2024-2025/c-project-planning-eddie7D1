#pragma once
#include <string>
#include <vector>

class Date {
public:
    int day;
    int month;
    int year;

    Date();
    Date(int d, int m, int y);
    std::string to_string();
};

class Product {
public:
    std::string barcode;
    std::string name;
    int quantity;
    double price;

    Product(std::string bc, std::string n, int q, double p);
    std::string to_string();
};

class Order {
public:
    std::vector<Product> products;
    Date order_date;

    Order();                                
    Order(std::vector<Product> p, Date d);  
    std::string to_string();
};
