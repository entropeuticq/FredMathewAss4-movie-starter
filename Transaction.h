#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Movie.h"

using namespace std;

class Transaction {
public:
    Transaction(char type, const string& description) : type(type), description(description) {}

    //virtual because of presence of derived classes
    virtual ~Transaction();

    char getType() const;
    string getDescription() const;

    //virtual because derived classes will implement executing a transaction
    virtual void execute();

    virtual void disaply() const;

protected:
    char type;
    string description;
};

class Borrow : public Transaction {
public:
    
}