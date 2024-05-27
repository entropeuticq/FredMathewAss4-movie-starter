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
//Checks if the customer has an active borrow of a movie
bool Customer::hasActiveBorrow(Movie* movie) {
    int borrows = 0;
    int returns = 0;
    for (const auto& transaction : transactions) {
        if(transaction->getMovie() == movie && transaction->getType() == 'B') {
            ++borrows;
        } else if (transaction->getMovie() == movie && transaction->getType() == 'R') {
            ++returns;
        }
    }
    if(borrows > returns)
        return true;
    else   
        return false;
}
//returns Customer ID number
int Customer::getID() const {
    return id;
}

//return customers full name
string Customer::getFullName() const {
    return lastName + ", " + firstName;
}

Customer::~Customer() {
    for (const auto& transaction : transactions) {
        delete transaction;
    }
}
