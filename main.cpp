/**
 * Driver for starting movie store tests
 */
#include "Inventory.h"
#include "CustomerManager.h" 
#include "CommandProcessor.h"
#include "CustomHashMap.h"
#include "Movie.h"
#include "Customer.h"
#include "Transaction.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

using namespace std;

// forward declaration, implementation in store_test.cpp
// void testAll();

int main() {
  // // testAll();
  // // cout << "Done." << endl;
  // // return 0;

  Inventory inventory;
  CustomerManager customerManager;
  inventory.loadMovies("data4movies.txt");
  inventory.display();
  customerManager.loadCustomers("data4customers.txt");
  CommandProcessor commandProcessor(inventory, customerManager);
  commandProcessor.processCommands("data4commands.txt");

// Check that all movies were loaded
  assert(inventory.findMovie('F', "Sleepless in Seattle 1993") != nullptr);
  assert(inventory.findMovie('F', "Annie Hall 1977") != nullptr);
  assert(inventory.findMovie('F', "When Harry Met Sally 1989") != nullptr);
  assert(inventory.findMovie('F', "Pirates of the Caribbean 2003") != nullptr);
  assert(inventory.findMovie('F', "Fargo 1996") != nullptr);
  assert(inventory.findMovie('F', "You've Got Mail 1998") != nullptr);
  assert(inventory.findMovie('F', "National Lampoon's Animal House 1978") != nullptr);

  assert(inventory.findMovie('D', "Barry Levinson Good Morning Vietnam") != nullptr);
  assert(inventory.findMovie('D', "Gus Van Sant Good Will Hunting") != nullptr);
  assert(inventory.findMovie('D', "Phillippe De Broca King of Hearts") != nullptr);
  assert(inventory.findMovie('D', "Steven Spielberg Schindler's List") != nullptr);
  assert(inventory.findMovie('D', "Jonathan Demme Silence of the Lambs") != nullptr);
  assert(inventory.findMovie('D', "Clint Eastwood Unforgiven") != nullptr);
  assert(inventory.findMovie('D', "Nancy Savoca Dogfight") != nullptr);

  assert(inventory.findMovie('C', "8 1942 Ingrid Bergman") != nullptr);
  assert(inventory.findMovie('C', "8 1942 Humphrey Bogart") != nullptr);
  assert(inventory.findMovie('C', "7 1939 Judy Garland") != nullptr);
  assert(inventory.findMovie('C', "3 1971 Ruth Gordon") != nullptr);
  assert(inventory.findMovie('C', "9 1938 Katherine Hepburn") != nullptr);
  assert(inventory.findMovie('C', "9 1938 Cary Grant") != nullptr);
  assert(inventory.findMovie('C', "2 1939 Vivien Leigh") != nullptr);
  assert(inventory.findMovie('C', "2 1939 Clark Gable") != nullptr);
  assert(inventory.findMovie('C', "5 1940 Katherine Hepburn") != nullptr);
  assert(inventory.findMovie('C', "5 1940 Cary Grant") != nullptr);
  assert(inventory.findMovie('C', "10 1941 Humphrey Bogart") != nullptr);
  assert(inventory.findMovie('C', "11 1946 Donna Reed") != nullptr);
  assert(inventory.findMovie('C', "2 1971 Malcolm McDowell") != nullptr);

  // Check that all customers were loaded correctly
  assert(customerManager.findCustomer(3333) != nullptr);
  assert(customerManager.findCustomer(8888) != nullptr);
  assert(customerManager.findCustomer(4444) != nullptr);
  assert(customerManager.findCustomer(9999) != nullptr);
  assert(customerManager.findCustomer(6666) != nullptr);
  assert(customerManager.findCustomer(7777) != nullptr);
  assert(customerManager.findCustomer(1111) != nullptr);
  assert(customerManager.findCustomer(1000) != nullptr);
  assert(customerManager.findCustomer(9000) != nullptr);
  assert(customerManager.findCustomer(8000) != nullptr);
  assert(customerManager.findCustomer(5000) != nullptr);
  assert(customerManager.findCustomer(2000) != nullptr);

  Movie* youveGotMail = inventory.findMovie('F', "You've Got Mail 1998");
  assert(youveGotMail != nullptr);
  assert(youveGotMail->getStock() == 9); // After several borrow and return transactions

  cout << "All command processor tests passed!" << endl;

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

  //TEST INVENTORY.CPP

  string filename = "data4movies.txt";
  ifstream infile(filename);
  if (!infile.is_open()) {
    cerr << "Error: could not open file " << filename << endl;
    return 1;
  }

  cout << "File " << filename << " opened successfully." << endl;

// Create inventory object
Inventory inventory1;

// Load movies from file
inventory1.loadMovies("data4movies.txt");

// Display inventory to visually check the loaded data
cout << "Displaying inventory loaded from file: " << endl;
inventory1.display();

// Add movies directly
Comedy* newComedy = new Comedy(8, "Mel Brooks", "Spaceballs", 1987);
Drama* newDrama = new Drama(6, "Martin Scorsese", "Goodfellas", 1990);
Classic* newClassic = new Classic(4, "John Ford", "The Searchers", "John Wayne", 5, 1956);

inventory1.addMovie(newComedy);
inventory1.addMovie(newDrama);
inventory1.addMovie(newClassic);

// Display inventory to visually check the loaded data
cout << "Displaying inventory after adding movies directly: " << endl;
inventory1.display();

// Find movies tests
Movie* foundComedy = inventory1.findMovie('F', "Spaceballs 1987");
Movie* foundDrama = inventory1.findMovie('D', "Martin Scorsese Goodfellas");
Movie* foundClassic = inventory1.findMovie('C', "5 1956 John Wayne");

// Assert that movies were found correctly
assert(foundComedy != nullptr);
assert(foundDrama != nullptr);
assert(foundClassic != nullptr);

// Check attributes of found movies
assert(foundComedy->getTitle() == "Spaceballs");
assert(static_cast<Comedy*>(foundComedy)->getYear() == 1987);
assert(foundDrama->getTitle() == "Goodfellas");
assert(static_cast<Drama*>(foundDrama)->getDirector() == "Martin Scorsese");
assert(foundClassic->getTitle() == "The Searchers");
assert(static_cast<Classic*>(foundClassic)->getMajorActor() == "John Wayne");
assert(static_cast<Classic*>(foundClassic)->getMonth() == 5);
assert(static_cast<Classic*>(foundClassic)->getYear() == 1956);

// Test invalid movie types
Movie* invalidMovie = inventory1.findMovie('X', "Some Invalid Movie");
assert(invalidMovie == nullptr);

// Test invalid movie search
Movie* notFoundMovie = inventory1.findMovie('F', "Non Existent Movie 2024");
assert(notFoundMovie == nullptr);

cout << "All inventory tests have passed!" << endl;

  CustomerManager mang;
  CustomHashMap map;
  //constructor/map initialization test
  assert(map.getSize() == 11);
  //Test for:
  //CustomerManager: loadCustomers, findCustomers, addCustomer
  //CustomerHashMap: add, retrieve, rehash, hash
  mang.loadCustomers("data4customers.txt");
  assert(mang.findCustomer(1111) != nullptr && mang.findCustomer(3333) != nullptr && mang.findCustomer(2000) != nullptr); 
  //bad file test
  mang.loadCustomers("dfsdf");
  //Find nonexistant customer test
  assert(mang.findCustomer(9352) == nullptr);
  //Display test, check visually
  mang.displayCustomers();
  cout << "All CustomHashTable and CustomerManager tests have passed!" << endl;

  return 0;
}


