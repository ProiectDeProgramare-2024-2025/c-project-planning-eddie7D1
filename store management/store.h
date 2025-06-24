#pragma once
#include "models.h"
#include <vector>
#include <string>

class Store {
private:
    std::vector<Product> stock;
    std::vector<Order> orders;

public:
    void load_stock(std::string filename);
    void save_stock(std::string filename);

    void add_product(Product p);
    void delete_product(std::string barcode);
    void modify_product(std::string barcode, std::string field, double value);
    void view_stock();

    void load_orders(std::string filename);
    void view_orders();

    std::vector<Product> get_stock();      
    std::vector<Product>& get_stock_ref(); 
};
