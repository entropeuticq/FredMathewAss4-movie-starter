/**
 * Driver for starting movie store tests
 */
#include "Inventory.h"
// #include "CustomerManager.h"
// #include "CommandProcessor.h"
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

  //TEST INVENTORY.CPP

  string filename = "data4movies.txt";
  ifstream infile(filename);
  if (!infile.is_open()) {
    cerr << "Error: could not open file " << filename << endl;
    return 1;
  }

  cout << "File " << filename << " opened successfully." << endl;

  //create inventory object
  Inventory inventory;

  //load movies from file
  inventory.loadMovies("data4movies.txt");

  //display inventory to visually check the loaded data
  cout << "Displaying inventory loaded from file: " << endl;
  inventory.display();

  //add movies directly
  Comedy* newComedy = new Comedy(8, "Mel Brooks", "Spaceballs", 1987);
  Drama* newDrama = new Drama(6, "Martin Scorses", "Goodfellas", 1990);
  Classic* newClassic = new Classic(4, "John Ford", "The Searchers", "John Wayne", 5, 1956);

  inventory.addMovie(newComedy);
  inventory.addMovie(newDrama);
  inventory.addMovie(newClassic);

  //display inventory to visually check the loaded data
  cout << "Displaying inventory after adding movies directly: " << endl;
  inventory.display();

  //find movies tests
  Movie* foundComedy = inventory.findMovie('F', "Spaceballs 1987");
  Movie* foundDrama = inventory.findMovie('D', "Martin Scorses Goodfellas");
  Movie* foundClassic = inventory.findMovie('C', "5 1956 John Wayne");

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
  Movie* invalidMovie = inventory.findMovie('X', "Some Invalid Movie");
  assert(invalidMovie == nullptr);

  //test invalid movie search
  Movie* notFoundMovie = inventory.findMovie('F', "Non Existent Movie 2024");
  assert(notFoundMovie == nullptr);

  cout << "All inventory tests have passed!" << endl;

  return 0;
}


