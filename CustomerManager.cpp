#include "CustomerManager.h"

using namespace std;


void CustomerManager::loadCustomers(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Couldn't open " << filename << endl;
        return;
    }

    string currentLine;
    while (getline(infile, currentLine)) {
        if (!currentLine.empty()) {
            stringstream lineStream(currentLine);
            int ID;
            string lastName, firstName;
            lineStream >> ID >> lastName >> firstName;
            addCustomer(ID, firstName, lastName);
            cout << "Loaded customer: ID=" << ID << ", LastName=" << lastName << ", FirstName=" << firstName << endl;
        }
    }
}

Customer* CustomerManager::findCustomer(int custID) const{
    Customer* customer = customerMap.retrieve(custID);
    cout << "Find customer with ID: " << custID << (customer ? " - Found" : " - Not Found") << endl;
    return customer;
}

void CustomerManager::displayCustomers() const{
    customerMap.display();
}


void CustomerManager::addCustomer(int ID, const string &firstName, const string &lastName) {
    //create a new customer
    Customer* x = new Customer(ID, firstName, lastName);
    //add it to the customer hash map
    customerMap.add(x);
    cout << "Added customer: ID=" << ID << ", LastName=" << lastName << ", FirstName=" << firstName << endl;
}
