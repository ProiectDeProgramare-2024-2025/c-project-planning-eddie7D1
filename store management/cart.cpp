#include "cart.h"
#include <fstream>
#include <iostream>
#include <sstream>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"

void Cart::load_cart(std::string filename) {
    cart_products.clear();
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    std::string barcode;
    int quantity;

    while (fin >> barcode >> quantity) {
        Product p(barcode, "", quantity, 0);
        cart_products.push_back(p);
    }

    fin.close();
}

void Cart::save_cart(std::string filename) {
    std::ofstream fout(filename);
    for (int i = 0; i < cart_products.size(); i++) {
        fout << cart_products[i].barcode << " " << cart_products[i].quantity << "\n";
    }
    fout.close();
}

void Cart::add_product(std::string barcode, int quantity) {
    for (int i = 0; i < cart_products.size(); i++) {
        if (cart_products[i].barcode == barcode) {
            cart_products[i].quantity += quantity;
            return;
        }
    }
    Product p(barcode, "", quantity, 0);
    cart_products.push_back(p);
}

void Cart::modify_product(std::string barcode, int new_quantity) {
    for (int i = 0; i < cart_products.size(); i++) {
        if (cart_products[i].barcode == barcode) {
            cart_products[i].quantity = new_quantity;
            return;
        }
    }
}

void Cart::delete_product(std::string barcode) {
    for (int i = 0; i < cart_products.size(); i++) {
        if (cart_products[i].barcode == barcode) {
            cart_products.erase(cart_products.begin() + i);
            return;
        }
    }
}

void Cart::view_cart() {
    std::cout << GREEN << "Shopping Cart:\n" << RESET;
    for (int i = 0; i < cart_products.size(); i++) {
        std::cout << GREEN
                  << cart_products[i].barcode << " "
                  << cart_products[i].quantity
                  << RESET << "\n";
    }
}

Order Cart::create_order(Date date, std::vector<Product> stock) {
    std::vector<Product> final_products;

    for (int i = 0; i < cart_products.size(); i++) {
        std::string cart_barcode = cart_products[i].barcode;
        int cart_quantity = cart_products[i].quantity;

        bool found = false;

        for (int j = 0; j < stock.size(); j++) {
            if (stock[j].barcode == cart_barcode) {
                found = true;

                if (cart_quantity > stock[j].quantity) {
                    std::cout << "Insufficient stock for: " << cart_barcode << "\n";
                    return Order();
                }

                Product ordered = stock[j];
                ordered.quantity = cart_quantity;
                final_products.push_back(ordered);
                break;
            }
        }

        if (!found) {
            std::cout << "Product not found in stock: " << cart_barcode << "\n";
            return Order();  
        }
    }

    return Order(final_products, date);
}



std::vector<Product> Cart::get_products() {
    return cart_products;
}
