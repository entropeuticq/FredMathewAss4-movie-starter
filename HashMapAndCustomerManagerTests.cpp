#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <CustomHashMap.h>
#include <CustomerManager.h>

using namespace std;

CustomHashMap cust;
CustomerManager mang;

void constructorTestHM() {
    assert(cust.getSize() == 11);
}

//Also serves as add customer test, as the loadCustomer method calls addCustomer
void loadCustomerTest() {
    mang.loadCustomers("FredMathewAss4-movie-starter/data4customers.txt");
    assert(mang.findCustomer(3333) != nullptr && mang.findCustomer(1111) != nullptr && mang.findCustomer(2000) != nullptr);
    Customer* x = mang.findCustomer(4444);
    assert(x->getFullName() == "Bullwinkle, Moose");
}

