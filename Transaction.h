#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

//forward declaration, debugging file linkage
class Customer;
class Movie;

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
    //based on whether it is a borrow or a return
    virtual bool execute() = 0;

    //displays transaction details, implemented separately by derived classes
    //based on whether it is a borrow or return
    virtual void display() const = 0;

protected:
    //transaction type, B for borrow, R for return
    char type;
    //transaction description
    string description;
};

class Borrow : public Transaction {
public:
    //constructor, initializes attributes based on borrowed movie and borrower
    Borrow(Customer* customer, Movie* movie);

    //execute borrow transaction
    bool execute() override;

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
    Return(Customer* customer, Movie* movie);

    //executes the return transaction
    bool execute() override;

    //display return details
    void display() const override;

private:
    //customer returning movie
    Customer* customer;

    //movie being returned
    Movie* movie;

};

#endif

