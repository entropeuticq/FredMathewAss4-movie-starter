#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Movie.h"
#include "Customer.h"
#include <string>

using namespace std;

class Transaction {
public:
    Transaction(char type, const string& description) : type(type), description(description) {}

    //virtual because of presence of derived classes
    virtual ~Transaction();

    //gets type of transaction, borrow or return
    char getType() const;

    //description of transaction
    string getDescription() const;

    //virtual because derived classes will implement executing a transaction
    virtual void execute();

    //displays transaction details
    virtual void display() const;

protected:
    //transaction type, B for borrow, R for return
    char type;
    //transaction description
    string description;
};

class Borrow : public Transaction {
public:
    //constructor, initializes attributes based on borrowed movie and borrower
    Borrow(Customer* customer, Movie* movie) : Transaction('B', "Borrowed " + movie->getTitle() + " by " + customer->getFullName()), customer(customer), movie(movie) {}

    //execute borrow transaction
    void execute() override;

    //display aspects of the borrow transaction
    void display() const override;

private:
    //borrowing customer
    Customer* customer;

    //movie being borrowed
    Movie* movie;

};

class Return : public Transaction {
public:
    //constructor, initializes return with return attributes
    Return(Customer* customer, Movie* movie) : Transaction('R', "Returned " + movie->getTitle() + " by " + customer->getFullName()), customer(customer), movie(movie) {}

    //executes the return transaction
    void execute() override;

    //display return details
    void display() const override;

private:
    //customer returning movie
    Customer* customer;

    //movie being returned
    Movie* movie;

};

#endif

