
#include "store.h"
#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

int main(int argc, char* argv[]) {
    Store store;
    store.load_stock("stock.txt");

    if (argc < 2) {
        std::cout << RED << "Please provide a command.\n" << RESET;
        return 1;
    }

    std::string command = argv[1];

    if (command == "view_stock_products") {
        if (argc != 2) {
            std::cout << YELLOW << "Usage: view_stock_products\n" << RESET;
            return 1;
        }
        store.view_stock();
    }

    else if (command == "add_product") {
        if (argc != 6) {
            std::cout << YELLOW << "Usage: add_product <barcode> <name> <quantity> <price>\n" << RESET;
            return 1;
        }
        std::string barcode = argv[2];
        std::string name = argv[3];
        int quantity = std::stoi(argv[4]);
        double price = std::stod(argv[5]);

        Product p(barcode, name, quantity, price);
        store.add_product(p);
        store.save_stock("stock.txt");
        std::cout << GREEN << "Product added successfully.\n" << RESET;
    }

    else if (command == "delete_product") {
        if (argc != 3) {
            std::cout << YELLOW << "Usage: delete_product <barcode>\n" << RESET;
            return 1;
        }
        std::string barcode = argv[2];
        store.delete_product(barcode);
        store.save_stock("stock.txt");
        std::cout << GREEN << "Product deleted successfully.\n" << RESET;
    }

    else if (command == "modify_product") {
        if (argc != 5) {
            std::cout << YELLOW << "Usage: modify_product <price | quantity> <barcode> <new_value>\n" << RESET;
            return 1;
        }
        std::string field = argv[2];
        std::string barcode = argv[3];
        double new_value = std::stod(argv[4]);

        store.modify_product(barcode, field, new_value);
        store.save_stock("stock.txt");
        std::cout << GREEN << "Product modified successfully.\n" << RESET;
    }

    else if (command == "view_orders") {
        if (argc != 2) {
            std::cout << YELLOW << "Usage: view_orders\n" << RESET;
            return 1;
        }
        store.load_orders("Orders.txt");
        store.view_orders();
    }

    else {
        std::cout << RED << "Unknown command.\n" << RESET;
        std::cout << CYAN << "Available commands:\n"
                  << "  view_stock_products\n"
                  << "  add_product <barcode> <name> <quantity> <price>\n"
                  << "  delete_product <barcode>\n"
                  << "  modify_product <price | quantity> <barcode> <new_value>\n"
                  << "  view_orders\n" << RESET;
    }

    return 0;
}