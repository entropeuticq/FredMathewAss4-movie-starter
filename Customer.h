#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Transaction.h"
#include <string>
#include <vector>


using namespace std;

class Customer {
public:
    //constructor, initializing customer details
    Customer(int id, const string& firstName, const string& lastName) : id(id), firstName(firstName), lastName(lastName) {}

    ~Customer();

    //add a new transaction to vector that stores them for customer history, const pointer for access-only 
    void addTransaction(const Transaction* transaction);

    //displays customers transaction history
    void displayHistory() const;

    //returns customers unique ID
    int getID() const;

    //returns customers name
    string getFullName() const;

private:
    //unique customer ID and name
    int id;
    string firstName;
    string lastName;

    //vector for storing transactions into customer history, const pointer for accessing transaction object
    vector<const Transaction*> transactions;


};
#endif

