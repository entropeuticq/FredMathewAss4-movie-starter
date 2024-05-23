#ifndef INVENTORY_H
#define INVENTORY_H

#include "Movie.h"
#include <vector>
#include <map>
#include <string>

class Inventory {
public:
    //constructor
    Inventory() = default;

    //destructor
    ~Inventory();
    
    //loads movies from given file
    void loadMovies(const string& filename);

    //adds a movie to inventory based on its type
    void addMovie(Movie* movie);

    //finds a movie in inventory by type and attributes
    //firstAttribute is primary sorting attribute
    //secondAttribute is secondary sorting attribute
    Movie* findMovie(char type, const string& attributes) const;

    //display movies in inventory catagorized by movie type
    //each catagory will be sorted based on required sorting attributes
    void display() const;

private:
    //maps for storing movies based on type and sorting criteria
    map<string, Movie*> comedyMap;
    map<string, Movie*> dramaMap;
    map<string, Movie*> classicMap;
    
    string parseAttributes(char type, const string& attributes) const;

    void addMovieToMap(Movie* movie, map<string, Movie*>& moviemap, const string& key);
};

#endif
