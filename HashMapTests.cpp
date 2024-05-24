#include "Customer.h"
#include "CustomHashMap.h"
#include "CustomerManager.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

CustomerManager mang;
CustomHashMap map;

class HashMapTests
{
public:
    void constructorTest()
    {
        assert(map.getSize() == 11);
    }

    // also tests retrieve, and by extension hash, within CustomHashMap
    // also triggers rehash
    // a very multi purposse test lol
    void loadCustomersAndFindCustomerTest()
    {
        mang.loadCustomers("/home/NETID/mdavid3/FredMathewAss4-movie-starter/data4customers.txt");
        assert(mang.findCustomer(1111) != nullptr && mang.findCustomer(3333) != nullptr && mang.findCustomer(2000) != nullptr);
    }

    void displayTest()
    {
        mang.displayCustomers();
    }
};
int main()
{
    HashMapTests x;
    x.constructorTest();
    x.loadCustomersAndFindCustomerTest();
    x.displayTest();
    return 0;
}
