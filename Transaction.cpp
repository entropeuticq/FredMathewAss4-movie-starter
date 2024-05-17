#include "Transaction.h"
#include "Customer.h"
#include "Movie.h"

//virtual destructor ensuring that borrow and return destructors
//are called when deleting objects through base class pointer
Transaction::~Transaction() {

}

//returns type of transaction, useful for type dependant logic
char Transaction::getType() const {
    return type;
}

//returns string for displaying transaction details
string Transaction::getDescription() const {
    return description;
}

//BORROW
//constructor
 Borrow::Borrow(Customer* customer, Movie* movie) : Transaction('B', ""), customer(customer), movie(movie) {
    if (customer && movie) {
        description = "Borrowed " + movie->getTitle() + " by " + customer->getFullName();
    }
 } 

//execute borrow transaction
void Borrow::execute() {
    if(movie->decreaseStock()) {
        //adds transaction to customer history of stock decrease successful
        customer->addTransaction(this);
    } else {
        //alerts if borrow not executed successfully
        cout << "Borrow denied, none in stock." << endl;
    }
}

//display borrow transaction details, customer name and movie title
void Borrow::display() const {
    cout << "Borrowed: " << movie->getTitle() << " by " << customer->getFullName();
}

//RETURN
//constructor
 Return::Return(Customer* customer, Movie* movie) : Transaction('R', ""), customer(customer), movie(movie) {
    if (customer && movie) {
        description = "Returned " + movie->getTitle() + " by " + customer->getFullName();
    }
 } 

//execute return transaction
void Return::execute() {
    movie->increaseStock(1);
    //adds transaction to customers history
    customer->addTransaction(this);
}

//display return transaction details, customer name and movie title
void Return::display() const {
    cout << "Returned: " << movie->getTitle() << " by " << customer->getFullName();
}

