/**
 * Driver for starting movie store tests
 */
// #include "Inventory.h"
// #include "CustomerManager.h"
// #include "CommandProcessor.h"
#include "Movie.h"
#include "Customer.h"
#include "Transaction.h"
#include <iostream>
#include <cassert>

using namespace std;

// forward declaration, implementation in store_test.cpp
// void testAll();

int main() {
  // testAll();
  // cout << "Done." << endl;
  // return 0;

  // Inventory inventory;
  // CustomerManager customerManager;
  // inventory.loadMovies("data4movies.txt");
  // customerManager.loadCustomers("data4customers.txt");
  // CommandProcessor commandProcessor(inventory, customerManager);
  // commandProcessor.processCommands("data4commands.txt");

  //TEST MOVIE.CPP
  //instances of each movie type
  Comedy comedyMovie(10, "Wes Anderson", "The Grand Budapest Hotel", 2014);
  Drama dramaMovie(5, "Frank Darabont", "The Shawshank Redemption", 1994);
  Classic classicMovie(3, "Victor Fleming", "Gone with the Wind", "Clark Gable", 1, 1939);
  Customer customer(1234, "John", "Doe");

  //display tests
  cout << "Testing display functionality:\n";
  comedyMovie.display();
  dramaMovie.display();
  classicMovie.display();

  //stock display/increase/decrease tests
  assert(comedyMovie.getStock() == 10);
  comedyMovie.decreaseStock();
  assert(comedyMovie.getStock() ==9);
  comedyMovie.increaseStock(1);
  assert(comedyMovie.getStock() == 10);

  assert(dramaMovie.getStock() == 5);
  dramaMovie.decreaseStock();
  assert(dramaMovie.getStock() == 4);
  dramaMovie.increaseStock(1);
  assert(dramaMovie.getStock() == 5);

  assert(classicMovie.getStock() == 3);
  classicMovie.decreaseStock();
  assert(classicMovie.getStock() == 2);
  classicMovie.increaseStock(1);
  assert(classicMovie.getStock() == 3);

  //equality tests
  Drama dramaMovie2(5, "Frank Darabont", "The Shawshank Redemption", 1994);
  assert(dramaMovie == dramaMovie2);
  Drama dramaMovie3(5, "Christohper Nolan", "Inception", 2010);
  assert(!(dramaMovie == dramaMovie3));

  cout << "All Movie tests passed!" << endl;

  //TEST TRANSACTION.CPP and CUSTOMER.CPP
  //borrows and returns
  Borrow borrow1(&customer, &comedyMovie);
  borrow1.execute();
  Return return1(&customer, &comedyMovie);
  return1.execute();
  Borrow borrow2(&customer, &dramaMovie);
  borrow2.execute();

  //check history to see if borrows and returns are reflected in history
  customer.displayHistory();

  //make sure borrows and returns altered stock
  cout << "Movies in stock after customers transactions:" << endl;
  cout << " " << comedyMovie.getTitle() << " - Stock: " << comedyMovie.getStock() << endl;
  cout << " " << dramaMovie.getTitle() << " - Stock: " << dramaMovie.getStock() << endl;
  assert(comedyMovie.getStock() == 10);
  assert(dramaMovie.getStock() == 4);

  cout << "All Transaction and Customer tests passed!" << endl;

  return 0;
}
