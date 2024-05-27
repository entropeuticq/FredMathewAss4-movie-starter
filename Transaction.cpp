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
bool Borrow::execute() {
    if(movie->decreaseStock()) {
        //adds transaction to customer history of stock decrease successful
        customer->addTransaction(this);
    } else {
        //alerts if borrow not executed successfully
        cout << "Borrow denied, none in stock." << endl;
        return false;
    }
    return true;
}

//display borrow transaction details, customer name and movie title
void Borrow::display() const {
    cout << "Borrowed: " << movie->getTitle() << " by " << customer->getFullName();
}
Movie* Borrow::getMovie() const {
    return movie;
}
//RETURN
//constructor
 Return::Return(Customer* customer, Movie* movie) : Transaction('R', ""), customer(customer), movie(movie) {
    if (customer && movie) {
        description = "Returned " + movie->getTitle() + " by " + customer->getFullName();
    }
 } 

//execute return transaction
bool Return::execute() {
    if(!(customer->hasActiveBorrow(movie))) {
        cout << "Error: Customer hasn't borrowed this movie" << endl;
        return false;
    }

    movie->increaseStock(1);
    //adds transaction to customers history
    customer->addTransaction(this);
    return true;
}

//display return transaction details, customer name and movie title
void Return::display() const {
    cout << "Returned: " << movie->getTitle() << " by " << customer->getFullName();
}
Movie* Return::getMovie() const {
    return movie;
}

