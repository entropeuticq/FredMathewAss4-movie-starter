#include "CustomHashMap.h"

using namespace std;

//Reserves 11 buckets as an initial vector size
CustomHashMap::CustomHashMap() {
    map.resize(11);
    size = 11;
}

int CustomHashMap::getSize() {
    return size;
}
//adds a customer to the hash map by generating the hashing the ID and choosing a bucket accordingly
bool CustomHashMap::add(Customer* cust) {
    int index = hash(cust->getID()); //the hash index

    //This for loop checks if the ID is already in the map, if so, it returns false
    for(const auto& customer: map[index]) {

        if(customer->getID() == cust->getID()) {
            return false;
        }

    }
    //add customer to the map
    map[index].push_back(cust);
    //increase total number of customers by 1
    load++;
    //rehash if the load is greater than the size
    if(load > size) {
        rehash();
    }

    return true;
}

int CustomHashMap::hash(int custID) const{
    return custID % size;
}

Customer* CustomHashMap::retrieve(int custID) const{
    int bucket = hash(custID);
    for(const auto& customer : map[bucket]) {
        if(customer->getID() == custID)
            return customer;
    }
    return nullptr;
}

void CustomHashMap::display() const{
    for(int i = 0; i < size; i++) {

        for(const auto& customer : map[i]) {
            cout << "ID: " << customer->getID() << " Name: " << customer->getFullName() << endl;
        }
        
    }

}

//Increases the size of the hash map by 10
void CustomHashMap::rehash() {
    int index; //used within inner for loop to hold customer hashes
    size = size + 10; //the size of the new map

    //creates a new map with the new size
    vector<list<Customer*>> newMap;
    newMap.resize(size);

    //iterates through the current map and adds all the customers to the new map
    for(int i = 0; i < map.size(); i++) {

        for(const auto& customer : map[i]) {
            index = hash(customer->getID());
            newMap[index].push_back(customer);
        }

    }

    //replaces the old map with the new map
    map = newMap;
}

CustomHashMap::~CustomHashMap() {
    for(int i = 0; i < map.size(); i++) {

        for(const auto& customer : map[i]) {
            delete customer;
        }

    }
}