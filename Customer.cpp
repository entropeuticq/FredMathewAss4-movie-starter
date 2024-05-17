#include "Customer.h"
#include <iostream>
using namespace std;

//adds a transaction to customers history vector
void Customer::addTransaction(const Transaction* transaction) {
    transactions.push_back(transaction);
}

//displays customers transaction history
void Customer::displayHistory() const {
    cout << "Transaction History for " << getFullName() << ": " << endl;
    //iterating through customers history vector
    for (const auto& transaction : transactions) {
        transaction->display(); 
        cout << endl;
    }
}

//returns Customer ID number
int Customer::getID() const {
    return id;
}

//return customers full name
string Customer::getFullName() const {
    return lastName + ", " + firstName;
}

