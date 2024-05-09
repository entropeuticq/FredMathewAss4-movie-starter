#ifndef INVENTORY_H
#define INVENTORY_H

#include "Movie.h"
#include <vector>
#include <map>
#include <string>


class Inventory {
public:
    //adds a movie to inventory
    void addMovie(Movie* movie);

    //finds a movie in inventory by type and attributes
    Movie* findMovie(char type, const string& firstAttribute, const string& secondAttribute);

    //display movies in inventory
    void display() const;

private:
    vector<Movie*> comedies;
    vector<Movie*> dramas;
    vector<Movie*> classics;

    //sort comedies by title and then year
    void sortComedies();

    //sorts dramas by director and then title
    void sortDramas();

    //sorts classics by release date and then major actor
    void sortClassics();
};

#endif