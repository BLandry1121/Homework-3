
#include "store.h"
#include <sstream>
#include <string>

using namespace std;

Store::Store() {
    num_customers_ = 0;
    num_products_ = 0;
    num_transactions_ = 0;
}

void Store::num_customers(int customer_count) {
    num_customers_ = customer_count;
}

int Store::num_customers() {
    return num_customers_;
}

void Store::num_products(int product_count) {
    num_products_ = product_count;
}

int Store::num_products() {
    return num_products_;
}

void Store::num_transactions(int transaction_count) {
    num_transactions_ = transaction_count;
}

int Store::num_transactions() {
    return num_transactions_;
}

bool Store::add_customer(Person customer) {
    if (num_customers_ >= 100) {
        return false;
    }

    customers_[num_customers_] = customer;
    num_customers_++;
    return true;
}

bool Store::update_customer(int index, Person customer) {
    if (index < 0 || index >= num_customers_) {
        return false;
    }

    if (customers_[index].name() != customer.name()) {
        return false;
    }

    customers_[index] = customer;
    return true;
}

Person Store::get_customer(int index) {
    if (index >= 0 && index < num_customers_) {
        return customers_[index];
    }
    return Person();
}

bool Store::add_product(product item) {
    if (num_products_ >= 100) {
        return false;
    }

    products_[num_products_] = item;
    num_products_++;
    return true;
}

product Store::get_product(int index) {
    if (index >= 0 && index < num_products_) {
        return products_[index];
    }
    return product();
}

bool Store::add_transaction(transaction ntransaction) {
    if (num_transactions_ >= 100) {
        return false;
    }

    transactions_[num_transactions_] = ntransaction;
    num_transactions_++;
    return true;
}

transaction Store::get_transaction(int index) {
    if (index >= 0 && index < num_transactions_) {
        return transactions_[index];
    }
    return transaction();
}

int Store::find_customer(Person cust) {
    for (int i = 0; i < num_customers_; i++) {
        if (customers_[i].name() == cust.name()) {
            return i;
        }
    }
    return -1;
}

bool Store::make_purchase(Person customer, product item, int amount) {
    int index = find_customer(customer);

    if (index == -1 || amount <= 0 ||
        num_transactions_ >= 100) {
        return false;
    }

    credit_card card = customers_[index].person_credit_card();

    double total = item.price * amount;

    if (!card.make_purchase(total)) {
        return false;
    }

    Person updated_customer = customers_[index];
    updated_customer.person_credit_card(card);
    customers_[index] = updated_customer;

    transaction new_transaction;
    new_transaction.transaction_number = num_transactions_ + 1;
    new_transaction.customer = updated_customer;
    new_transaction.purchased_item = item;
    new_transaction.quantity = amount;

    return add_transaction(new_transaction);
}

string Store::customer_info() {
    stringstream ss;
    ss << "Customers:\n";

    for (int i = 0; i < num_customers_; i++) {
        ss << customers_[i].person_info() << "\n";
    }

    return ss.str();
}

string Store::product_info() {
    stringstream ss;
    ss << "Products:\n";

    for (int i = 0; i < num_products_; i++) {
        ss << products_[i].product_info() << "\n";
    }

    return ss.str();
}

string Store::transaction_info() {
    stringstream ss;
    ss << "All Transactions:\n";

    for (int i = 0; i < num_transactions_; i++) {
        ss << transactions_[i].transaction_info() << "\n";
    }

    return ss.str();
}

string Store::store_info() {
    stringstream ss;

    ss << customer_info() << "\n";
    ss << product_info() << "\n";
    ss << transaction_info();

    return ss.str();
}

string Store::purchase_history(Person customer) {
    stringstream ss;

    for (int i = 0; i < num_transactions_; i++) {
        if (transactions_[i].customer.name() == customer.name()) {
            ss << transactions_[i].transaction_info() << "\n";
        }
    }

    return ss.str();
}
//code for store class here
