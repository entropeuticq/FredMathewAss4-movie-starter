#ifndef CUSTOMHASHMAP_H
#define CUSTOMHASHMAP_H

#include <list>
#include <vector>
#include "Customer.h"
#include <string>
#include <queue>
#include <iostream>

using namespace std;

class CustomHashMap {

public:
CustomHashMap();

~ CustomHashMap();

int getSize();

void display() const;

bool add(Customer* cust);

int hash(int custID) const;

void rehash();

Customer* retrieve(int id) const;

private:
int load; //number of customers
int size; //size of map

vector<list<Customer*>> map;

};
#endif