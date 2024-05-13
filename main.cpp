/**
 * Driver for starting movie store tests
 */
#include "Inventory.h"
#include "CustomerManager.h"
#include "CommandProcessor.h"
#include <iostream>

#include <iostream>

using namespace std;

// forward declaration, implementation in store_test.cpp
void testAll();

int main() {
  // testAll();
  // cout << "Done." << endl;
  // return 0;

  Inventory inventory;
  CustomerManager customerManager;

  inventory.loadMovies("data4movies.txt");
  customerManager.loadCustomers("data4customers.txt");

  CommandProcessor commandProcessor(inventory, customerManager);

  commandProcessor.processCommands("data4commands.txt");

  return 0;
}
