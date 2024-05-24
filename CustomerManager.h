

#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include "Customer.h"
#include "CustomHashMap.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class CustomerManager {
public:
    //loads customers from given file
    void loadCustomers(const string& filename);

    //lookup customers using unique ID
    Customer* findCustomer(int customerID) const;

    //show customers in the system
    void displayCustomers() const;

private:
    //maps for quick searches using customer ID
    CustomHashMap customerMap;

    //add new customer to the system
    void addCustomer(int customerID, const string& firstName, const string& lastName);

};
#endif

