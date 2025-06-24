#pragma once
#include "models.h"
#include <vector>
#include <string>

class Cart {
private:
    std::vector<Product> cart_products;

public:
    void load_cart(std::string filename);
    void save_cart(std::string filename);

    void add_product(std::string barcode, int quantity);
    void modify_product(std::string barcode, int new_quantity);
    void delete_product(std::string barcode);
    void view_cart();

    Order create_order(Date date, std::vector<Product> stock);
    std::vector<Product> get_products();
};
