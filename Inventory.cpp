
#include "Inventory.h"
#include "Movie.h"
#include <algorithm>        //for sorting
#include <sstream>          //string stream
#include <iostream>         
#include <fstream>          //file stream
#include <cctype>           //character handling

using namespace std;

//Destructor for cleaning up dynamically allocated movie objects
Inventory::~Inventory() {
    //loops through all entries in the movie type map deleting them
    for (auto& pair : comedyMap) {
        delete pair.second;
    }
    for (auto& pair : dramaMap) {
        delete pair.second;
    }
    for (auto& pair : classicMap) {
        delete pair.second;
    }
}

//load movies from a file
void Inventory::loadMovies(const string& filename) {
    //opens the file to prepare for reading
    ifstream infile(filename);

    //check to make sure file was opened successfully
    if(!infile) {
        cerr << "Error: could not open file " << filename << endl;
        return;
    }

    //holds each line from the file
    string line;
    //reads the file line by line
    while (getline(infile, line)) {
        //skips empty lines
        if (line.empty()) {
            continue;
        }
        //debug statement
        cout << "Reading line: " << line << endl;

        //for parsing the line
        istringstream iss(line);
        //holds type of movie F, D or C
        char type;
        //holds stock quantity
        int stock;
        //holds directors name and movie title and major actor
        string director, title, firstName, lastName, majorActor;
        //holds month and year of release date
        int month, year = 0;

        //reads type from our string stream with error when not found
        if (!(iss >> type)) {
            cerr << "Invalid format: missing type in line: " << line << endl;
            continue;
        }

        //ignore the comma after type
        iss.ignore(1, ',');

        //reads stock from our string stream with error when not found
        if(!(iss >> stock)) {
            cerr << "Invalid format: missing stock in line: " << line << endl;
            continue;
        }

        //ignore the comma after the stock
        iss.ignore(1, ',');

        //reads director from our string stream with error when not found
        //stops reading at ','
        if (!getline(iss, director, ',')) {
            cerr << "Invalid format: missing director in line: " << line << endl;
            continue;
        }

        //reads title from our string stream with error when not found
        //stops reading at ','
        if(!getline(iss, title, ',')) {
            cerr << "Invalid format: missing title in line: " << line << endl;
            continue;
        }
        
        //remove leading and trailing spaces from director and title
        director.erase(0, director.find_first_not_of(" \t"));
        director.erase(director.find_last_not_of(" \t") + 1);

        title.erase(0, title.find_first_not_of(" \t"));
        title.erase(title.find_last_not_of(" \t") + 1);

        //debug statement
        cout << "Parsed type: " << type << ", stock: " << stock << ", director: " << director << ", title: " << title << endl;

        //checks if the movie is a Comedy or Drama
        if (type == 'F' || type == 'D') {
            //reads the year from our string stream, with error when not found
            if (!(iss >> year)) {
                cerr << "Invalid format: missing year in line: " << line << endl;
                continue;
            }

            //debug statement
            cout << "Parsed year: " << year << endl;

            //creates a new comedy or or drama object
            //cast to Movie type, store in movie pointer, achieves late binding
            //allowing the full utilization of virtual overidden functions in derived classes
            Movie* movie = (type == 'F') ? static_cast<Movie*>(new Comedy(stock, director, title, year))
                                         : static_cast<Movie*>(new Drama(stock, director, title, year));
            
            addMovie(movie);

        //checks if movie is a Classic    
        } else if (type == 'C') {
            //skips leading white spaces
            iss >> ws;
            //reads major actors first and last name, as well as month and year of release, from string stream
            //prints error if attributes are missing and skips to next movie
            if (!(getline(iss, firstName, ' ') && iss >> lastName >> month >> year)) {
                cerr << "Invalid format: missing major actor, month or year in line: " << line << endl;
                continue;
            }
            
            majorActor = firstName + " " + lastName;
            //remove leading and trailing spaces from majorActor
            majorActor.erase(0, majorActor.find_first_not_of(" \t"));
            majorActor.erase(majorActor.find_last_not_of(" \t") + 1);
            
            //debug statement
            cout << "Parsed majorActor: " << majorActor << ", month: " << month << ", year: " << year << endl;

            //create classic, cast to movie, store in movie pointer, achieves late binding
            Movie* movie = static_cast<Movie*>(new Classic(stock, director, title, majorActor, month, year));
            addMovie(movie);
        } else {
            //invalid movie type
            cerr << "Invalid movie type in file: " << type << endl;
        }
    }

    //debug statement
    cout << "Inventory after loading movies:" << endl;
    display();
}

//add movie to inventory
void Inventory::addMovie(Movie* movie) {
    char type = movie->getType();
    //for sorting key
    string key;

    //generates sorting key based on type
    if (type == 'F') {
        //title and year for comedies
        //cast to derived type for use of derived class methods required for generating sorting key
        //also ensures compile time type checking
        Comedy* comedyMovie = static_cast<Comedy*>(movie);
        key = comedyMovie->getTitle() + " " + to_string(comedyMovie->getYear());
    } else if (type == 'D') {
        //director and title for dramas
        Drama* dramaMovie = static_cast<Drama*>(movie);
        key = dramaMovie->getDirector() + " " + dramaMovie->getTitle();
    } else if (type == 'C') {
        //release date and major actor for classics
        Classic* classicMovie = static_cast<Classic*>(movie);
        key = to_string(classicMovie->getYear()) + " " + to_string(classicMovie->getMonth()) + " " + classicMovie->getMajorActor();
    } else {
        //invalid movie type
        cerr << "Invalid movie type" << type << endl;
        delete movie;
        return;
    }

    //debug statement
    cout << "Generated key: " << key << " for type: " << type << endl;
    
    //add movie to appropriate map
    if (type == 'F') {
        addMovieToMap(movie, comedyMap, key);
    } else if (type == 'D') {
        addMovieToMap(movie, dramaMap, key);
    } else if (type == 'C') {
        addMovieToMap(movie, classicMap, key);
    } else {
        cerr << "Invalid Movie Type: " << type << endl;
        delete movie;
    }
}
//finds a movie in the inventory
Movie* Inventory::findMovie(char type, const string& attributes) const {
    //determines correct map to search based on movie type
    const map<string, Movie*>* movieMap;
    if (type == 'F') {
        movieMap = &comedyMap;
    } else if (type == 'D') {
        movieMap = &dramaMap;
    } else if (type == 'C') {
        movieMap = &classicMap;
    } else {
        //invalid movie type
        cerr << "Invalid movie type: " << type << endl;
        return nullptr;
    }

    //generates key for movie searches
    string key = parseAttributes(type, attributes);

    //debug statement
    cout << "Parsed attributes into key: " << key << endl;
    cout << "Searching for key: " << key << " in map of type: " << type << endl;

    //finds the movie in the map
    auto it = movieMap->find(key);

    //returns found movie or nullptr if not found
    if (it != movieMap->end()) {
        cout << "Found movie with key: " << key << endl;
        return it->second;
    } else {
        cout << "Movie with key: " << key << " not found." << endl;
        return nullptr;
    }
}

//displays inventory
void Inventory::display() const {
    cout << "Inventory:\n";
    cout << "Comedies:\n";

    //iterates over the appropriate vector and displays each movie
    for (const auto& pair : comedyMap) {
        pair.second->display();
        cout << endl;
    }
    cout << "Dramas:\n";
    for (const auto& pair : dramaMap) {
        pair.second->display();
        cout << endl;
    }
    cout << "Classics:\n";
    for (const auto& pair : classicMap) {
        pair.second->display();
        cout << endl;
    }
}

//helper function for parsing movie attributes for finding and sorting
string Inventory::parseAttributes(char type, const string& attributes) const {
    //for comedies and dramas we'll use title and year/director and title as the key
    if (type == 'F' || type == 'D') {
        return attributes;
    } else if (type == 'C') {
        istringstream iss(attributes);
        string majorActor;
        int month, year;

        //parses month and year
        iss >> month >> year;
        //parses major actor
        getline(iss, majorActor);

        //remove leading and trailing spaces from major actor
        majorActor.erase(0, majorActor.find_first_not_of(" \t"));
        majorActor.erase(majorActor.find_last_not_of(" \t") + 1);
        
        //creates the key and returns it or empty string if invalid or missing type
        return to_string(year) + " " + to_string(month) + " " + majorActor;
    } else {
        return "";
    }
}

//helper function to add movie to the appropriate map
void Inventory::addMovieToMap(Movie* movie, map<string, Movie*>& moviemap, const string& key) {
    //adds movie to map with its new key
    moviemap[key] = movie;
}
