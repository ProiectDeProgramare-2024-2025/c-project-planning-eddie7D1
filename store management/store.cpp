#include "store.h"
#include <fstream>
#include <iostream>
#include <sstream>

#define RESET   "\033[0m"
#define CYAN    "\033[36m"

void Store::load_stock(std::string filename) {
    stock.clear();
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    int count;
    fin >> count;

    for (int i = 0; i < count; i++) {
        std::string barcode, name;
        int quantity;
        double price;
        fin >> barcode >> name >> quantity >> price;
        Product p(barcode, name, quantity, price);
        stock.push_back(p);
    }

    fin.close();
}

void Store::save_stock(std::string filename) {
    std::ofstream fout(filename);
    fout << stock.size() << "\n";
    for (int i = 0; i < stock.size(); i++) {
        fout << stock[i].to_string() << "\n";
    }
    fout.close();
}

void Store::add_product(Product p) {
    stock.push_back(p);
}

void Store::delete_product(std::string barcode) {
    for (int i = 0; i < stock.size(); i++) {
        if (stock[i].barcode == barcode) {
            stock.erase(stock.begin() + i);
            break;
        }
    }
}

void Store::modify_product(std::string barcode, std::string field, double value) {
    for (int i = 0; i < stock.size(); i++) {
        if (stock[i].barcode == barcode) {
            if (field == "price") {
                stock[i].price = value;
            } else if (field == "quantity") {
                stock[i].quantity = (int)value;
            }
            break;
        }
    }
}

void Store::view_stock() {
    std::cout << CYAN << "Available Products in Stock:\n" << RESET;
    for (int i = 0; i < stock.size(); i++) {
        std::cout << stock[i].to_string() << "\n";
    }
}

void Store::load_orders(std::string filename) {
    orders.clear();

    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        int d, m, y;
        char slash1, slash2;
        std::istringstream date_stream(line);
        if (!(date_stream >> d >> slash1 >> m >> slash2 >> y)) {
            continue; // skip invalid lines
        }

        Date date(d, m, y);
        std::vector<Product> order_products;

        while (std::getline(fin, line)) {
            if (line.empty()) break;

            std::istringstream prod_stream(line);
            std::string barcode, name;
            int quantity;
            double price;

            if (prod_stream >> barcode >> name >> quantity >> price) {
                Product p(barcode, name, quantity, price);
                order_products.push_back(p);
            } else {
                std::cout << "Skipping invalid product line: " << line << "\n";
            }
        }

        orders.push_back(Order(order_products, date));
    }

    fin.close();
}



void Store::view_orders() {
    std::cout << CYAN << "Previous Orders:\n" << RESET;
    for (int i = 0; i < orders.size(); i++) {
        std::cout << orders[i].to_string() << "\n";
    }
}

std::vector<Product> Store::get_stock() {
    return stock;
}

std::vector<Product>& Store::get_stock_ref() {
    return stock;
}
