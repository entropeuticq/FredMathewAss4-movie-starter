#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Transaction.h"
#include <string>
#include <vector>


using namespace std;

class Customer {
public:
    Customer(int id, const string& firstName, const string& lastName) : id(id), firstName(firstName), lastName(lastName) {}

    //add a new transaction to vector that stores them, const pointer for access-only 
    void addTransaction(const Transaction* transaction);
    void displayHistory() const;
    int getID() const;
    string getFullName() const;

private:
    int id;
    string firstName;
    string lastName;
    //vector for storing transactions, const pointer for accessing transaction object
    vector<const Transaction*> transactions;


};
#endif