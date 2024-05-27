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
   //testAll();
   //cout << "Done." << endl;
   //return 0;

  Inventory inventory;
  CustomerManager customerManager;
  inventory.loadMovies("data4movies.txt");
  inventory.display();
  customerManager.loadCustomers("data4customers.txt");
  CommandProcessor commandProcessor(inventory, customerManager);
  commandProcessor.processCommands("data4commands.txt");
  //assert(inventory.findMovie('C', "8 1942 Ingrid Bergman") != nullptr);
/*
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

  //create inventory object
  Inventory inventory1;

  //load movies from file
  inventory1.loadMovies("data4movies.txt");

  //display inventory to visually check the loaded data
  cout << "Displaying inventory loaded from file: " << endl;
  inventory1.display();

  //add movies directly
  Comedy* newComedy = new Comedy(8, "Mel Brooks", "Spaceballs", 1987);
  Drama* newDrama = new Drama(6, "Martin Scorses", "Goodfellas", 1990);
  Classic* newClassic = new Classic(4, "John Ford", "The Searchers", "John Wayne", 5, 1956);

  inventory1.addMovie(newComedy);
  inventory1.addMovie(newDrama);
  inventory1.addMovie(newClassic);

  //display inventory to visually check the loaded data
  cout << "Displaying inventory after adding movies directly: " << endl;
  inventory1.display();

  //find movies tests
  Movie* foundComedy = inventory1.findMovie('F', "Spaceballs 1987");
  Movie* foundDrama = inventory1.findMovie('D', "Martin Scorses Goodfellas");
  Movie* foundClassic = inventory1.findMovie('C', "5 1956 John Wayne");

  //assert that movies were found correctly
  assert(foundComedy != nullptr);
  assert(foundDrama != nullptr);
  assert(foundClassic != nullptr);

  //check attributes of found movies
  assert(foundComedy->getTitle() == "Spaceballs");
  assert(static_cast<Comedy*>(foundComedy)->getYear() == 1987);
  assert(foundDrama->getTitle() == "Goodfellas");
  assert(static_cast<Drama*>(foundDrama)->getDirector() == "Martin Scorses");
  assert(foundClassic->getTitle() == "The Searchers");
  assert(static_cast<Classic*>(foundClassic)->getMajorActor() == "John Wayne");
  assert(static_cast<Classic*>(foundClassic)->getMonth() == 5);
  assert(static_cast<Classic*>(foundClassic)->getYear() == 1956);

  //test invalid movie types
  Movie* invalidMovie = inventory1.findMovie('X', "Some Invalid Movie");
  assert(invalidMovie == nullptr);

  //test invalid movie search
  Movie* notFoundMovie = inventory1.findMovie('F', "Non Existent Movie 2024");
  assert(notFoundMovie == nullptr);
  
  cout << "All inventory tests have passed!" << endl;

  //COMMAND PROCESSOR TESTS
  //creating sample file for customers
  ofstream testCustomersFile("test_customers.txt");
  testCustomersFile << "1234 Doe John\n";
  testCustomersFile << "5678 Smith Jane\n";
  testCustomersFile.close();

  //creating sample file for commands
  ofstream testCommandsFile("test_commands.txt");
  //display inventory
  testCommandsFile << "I\n";
  //1234 borrows comedy movie
  testCommandsFile << "B 1234 D F The Grand Budapest Hotel, 2014\n";
  //1234 returns comedy movie
  testCommandsFile << "R 1234 D F The Grand Budapest Hotel, 2014\n";
  //display history for customer 1234
  testCommandsFile << "H 1234\n";
  //5678 borrows a drama movie
  testCommandsFile << "B 5678 D D Frank Darabont, The Shawshank Redemption\n";
  //5678 returns dramam movie
  testCommandsFile << "R 5678 D D Frank Darabont, The Shawshank Redemption\n";
  //display history for 5678
  testCommandsFile << "H 5678\n";
  testCommandsFile.close();
 
  //create a customer manager object and load customers
  CustomerManager testCustomerManager;
  testCustomerManager.loadCustomers("test_customers.txt");

  //create a command processor object and process commands
  CommandProcessor testCommandProcessor(inventory, testCustomerManager);
  testCommandProcessor.processCommands("test_commands.txt");

  //assertions for verifying successful command processing
  Customer* testCustomer1 = testCustomerManager.findCustomer(1234);
  Customer* testCustomer2 = testCustomerManager.findCustomer(5678);

  assert(testCustomer1 != nullptr);
  assert(testCustomer2 != nullptr);

  //testCustomer1 and testCustomer2 history should have 2 entries each
  cout << "History for customer 1234 should have 2 entries:" << endl;
  testCustomer1->displayHistory();
  cout << "History for customer 5678 should have 2 entries:" << endl;
  testCustomer2->displayHistory();

  //display inventory to check final state
  inventory.display();

  cout << "All CommandProcessor tests have passed." << endl;



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
*/
  return 0;
}


