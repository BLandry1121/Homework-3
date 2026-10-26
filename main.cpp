
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "address.h"
#include "credit_card.h"
#include "person.h"
#include "product.h"
#include "store.h"
#include "transaction.h"

using namespace std;

int main() {

    Store store1;

    Person customers[100];
    product products[100];

    int customer_count = 0;
    int product_count = 0;

    // Import customer information
    ifstream people_file("people.txt");

    if (!people_file) {
        cout << "Error opening people.txt" << endl;
        return 1;
    }

    int total_people;
    people_file >> total_people;
    people_file.ignore();

    for (int i = 0; i < total_people && i < 100; i++) {
        string name, phone;
        address addr;

        getline(people_file, name);
        getline(people_file, phone);
        getline(people_file, addr.address_line1);
        getline(people_file, addr.address_line2);
        getline(people_file, addr.city);
        getline(people_file, addr.state);
        getline(people_file, addr.zip);

        credit_card card = {};

        customers[customer_count] =
            Person(name, phone, addr, card);

        customer_count++;
    }

    people_file.close();

    // Import credit card information
    ifstream card_file("credit_card.txt");

    if (!card_file) {
        cout << "Error opening credit_card.txt" << endl;
        return 1;
    }

    int total_cards;
    card_file >> total_cards;
    card_file.ignore();

    for (int i = 0; i < total_cards; i++) {
        string customer_name;
        credit_card card;

        getline(card_file, customer_name);

        card_file >> card.cc_number;
        card_file >> card.limit;
        card_file >> card.current_balance;
        card_file.ignore();

        for (int j = 0; j < customer_count; j++) {
            if (customers[j].name() == customer_name) {
                customers[j].person_credit_card(card);
                break;
            }
        }
    }

    card_file.close();

    // Import product information
    ifstream product_file("products.txt");

    if (!product_file) {
        cout << "Error opening products.txt" << endl;
        return 1;
    }

    int total_products;
    product_file >> total_products;
    product_file.ignore();

    for (int i = 0; i < total_products && i < 100; i++) {
        product item;

        getline(product_file, item.name);
        getline(product_file, item.description);

        product_file >> item.price;
        product_file.ignore();

        products[product_count] = item;
        product_count++;
    }

    product_file.close();

    // Add customers and products to store
    for (int i = 0; i < customer_count; i++) {
        store1.add_customer(customers[i]);
    }

    for (int i = 0; i < product_count; i++) {
        store1.add_product(products[i]);
    }

    // Print initial store information
    cout << "Store info: " << endl << endl;
    cout << store1.store_info() << endl << endl;

    // Generate random transactions
    srand(time(0));

    int number_of_transactions = rand() % 89 + 11;

    for (int i = 0; i < number_of_transactions; i++) {

        int random_customer = rand() % customer_count;
        int random_product = rand() % product_count;
        int quantity = rand() % 10 + 1;

        Person customer = store1.get_customer(random_customer);
        product item = store1.get_product(random_product);

        bool success = store1.make_purchase(
            customer, item, quantity
        );

        if (success) {
            cout << "Successful transaction!" << endl;
            cout << "Transaction Details:" << endl;

            transaction current = store1.get_transaction(
                store1.num_transactions() - 1
            );

            cout << current.transaction_info() << endl;
        }
        else {
            cout << "Unsuccessful transaction!" << endl;
            cout << "Transaction Details:" << endl;
            cout << "Person:" << endl;
            cout << customer.person_info();
            cout << "Product:" << endl;
            cout << item.product_info();
            cout << "Purchase Quantity: "
                 << quantity << endl << endl;
        }
    }

    // Print updated customer information
    cout << "Updated Customer Information:" << endl;
    cout << store1.customer_info() << endl;

    // Print final store information
    cout << "Store info: " << endl << endl;
    cout << store1.store_info() << endl << endl;

    return 0;
}
