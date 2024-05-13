#ifndef INVENTORY_H
#define INVENTORY_H

#include "Movie.h"
#include <vector>
#include <unordered_map>
#include <string>


class Inventory {
public:
    //loads movies from given file
    void loadMovies(const string& filename);


    //adds a movie to inventory based on its type
    void addMovie(Movie* movie);

    //finds a movie in inventory by type and attributes
    //firstAttribute is primary sorting attribute
    //secondAttribute is secondary sorting attribute
    Movie* findMovie(char type, const string& firstAttribute, const string& secondAttribute);

    //display movies in inventory catagorized by movie type
    //each catagory will be sorted based on required sorting attributes
    void display() const;

private:
    //maps for quick searches using unique keys
    unordered_map<string, Movie*> comedyMap;
    unordered_map<string, Movie*> dramaMap;
    unordered_map<string, Movie*> classicMap;

    //vectors that will keep sorted collections
    vector<Movie*> comedies;
    vector<Movie*> dramas;
    vector<Movie*> classics;

    //sort comedies by title and then year
    void sortComedies();

    //sorts dramas by director and then title
    void sortDramas();

    //sorts classics by release date and then major actor
    void sortClassics();

    //for making unique keys for comdies based on title and year
    string buildComedyKey(const string& title, int year);

    //for making unique keys for dramas based on director and title
    string buildDramaKey(const string& director, const string& title);

    //for making unique keys for classic movies bsed on release date and major actor
    string buildClassicKey(int month, int year, const string& majorActor);

    
};

#endif

