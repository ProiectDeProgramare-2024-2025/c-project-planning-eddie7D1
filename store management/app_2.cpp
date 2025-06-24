
#include "cart.h"
#include "store.h"
#include <iostream>
#include <fstream>
#include <ctime>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

Date get_today() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
}

int main(int argc, char* argv[]) {
    Cart cart;
    cart.load_cart("Shopping_Cart.txt");

    if (argc < 2) {
        std::cout << RED << "Please provide a command.\n" << RESET;
        return 1;
    }

    std::string command = argv[1];

    if (command == "view_cart") {
        if (argc != 2) {
            std::cout << YELLOW << "Usage: view_cart\n" << RESET;
            return 1;
        }
        cart.view_cart();
    }

    else if (command == "add_product") {
        if (argc != 4) {
            std::cout << YELLOW << "Usage: add_product <barcode> <quantity>\n" << RESET;
            return 1;
        }
        std::string barcode = argv[2];
        int quantity = std::stoi(argv[3]);

        cart.add_product(barcode, quantity);
        cart.save_cart("Shopping_Cart.txt");
        std::cout << GREEN << "Product added to cart.\n" << RESET;
    }

    else if (command == "modify_product") {
        if (argc != 4) {
            std::cout << YELLOW << "Usage: modify_product <barcode> <new_quantity>\n" << RESET;
            return 1;
        }
        std::string barcode = argv[2];
        int quantity = std::stoi(argv[3]);

        cart.modify_product(barcode, quantity);
        cart.save_cart("Shopping_Cart.txt");
        std::cout << GREEN << "Cart updated.\n" << RESET;
    }

    else if (command == "delete_product") {
        if (argc != 3) {
            std::cout << YELLOW << "Usage: delete_product <barcode>\n" << RESET;
            return 1;
        }
        std::string barcode = argv[2];
        cart.delete_product(barcode);
        cart.save_cart("Shopping_Cart.txt");
        std::cout << GREEN << "Product removed from cart.\n" << RESET;
    }

    else if (command == "purchase") {
        if (argc != 2) {
            std::cout << YELLOW << "Usage: purchase\n" << RESET;
            return 1;
        }

        Store store;
        store.load_stock("stock.txt");

        Date today = get_today();
        Order order = cart.create_order(today, store.get_stock());

        if (order.products.size() == 0) {
            std::cout << RED << "Order failed due to stock issues.\n" << RESET;
            return 1;
        }

        std::vector<Product> cart_items = cart.get_products();
        std::vector<Product>& stock = store.get_stock_ref();

        for (int i = 0; i < cart_items.size(); i++) {
            for (int j = 0; j < stock.size(); j++) {
                if (cart_items[i].barcode == stock[j].barcode) {
                    stock[j].quantity -= cart_items[i].quantity;
                    break;
                }
            }
        }

        store.save_stock("stock.txt");

        std::ofstream fout("Orders.txt", std::ios::app);
        fout << order.to_string() << "\n";
        fout.close();

        cart = Cart();
        cart.save_cart("Shopping_Cart.txt");

        std::cout << GREEN << "Order placed successfully.\n" << RESET;
    }

    else {
        std::cout << RED << "Unknown command.\n" << RESET;
        std::cout << CYAN << "Available commands:\n"
                  << "  view_cart\n"
                  << "  add_product <barcode> <quantity>\n"
                  << "  modify_product <barcode> <new_quantity>\n"
                  << "  delete_product <barcode>\n"
                  << "  purchase\n" << RESET;
    }

    return 0;
}