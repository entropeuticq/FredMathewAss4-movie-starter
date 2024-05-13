#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>

using namespace std;

class Movie {
public:
    //constructor, initializes move attributes common to all types
    Movie(char type, int stock, const string& director, const string& title) : type(type), stock(stock), director(director), title(title) {}

    //virtual desctructor for proper cleanup for derived movie based classes
    virtual ~Movie();

    //virutal function to display movie details, derived classes will implement this
    virtual void display() const = 0;
    
    //returns type of movie
    char getType() const;

    //returns number of movies in stock
    int getStock() const;

    //returned movies will increment stock
    void increaseStock(int count);

    //borrowed movies will decrement stock
    bool decreaseStock();

    //returns director of movie
    string getDirector() const;

    //returns title of movie 
    string getTitle() const;

    //derived classes will implement each comparison logic
    virtual bool operator==(const Movie& other) const = 0;
    virtual bool operator<(const Movie& other) const = 0;

protected:
    //movie type, F D or C
    char type;
    //number of movies available
    int stock;
    //directors name
    string director;
    //movie title
    string title;

};

class Comedy : public Movie {
public:
    //constructor, initializes with comedy-specific details
    Comedy(int stock, const string& director, const string& title, int year) : Movie('F', stock, director, title), year(year) {}
    
    //displays comedy details
    void display() const override;
    //comparison for sorting comedies by title, then year
    bool operator==(const Movie& other) const override;
    bool operator<(const Movie& other) const override;

private:
    //year of release
    int year;
};

class Drama : public Movie {
public:
    //constructor, initializes with drama-specific details
    Drama(int stock, const string& director, const string& title, int year) : Movie('D', stock, director, title), year(year) {}

    //displays drama details
    void display() const override;

    //comparisons for sorting dramas by director then title
    bool operator==(const Movie& other) const override;
    bool operator<(const Movie& other) const override;

private:
    //year of release
    int year;

};

class Classic : public Movie {
public:
    //constructor, initializes with classic specifc details
    Classic(int stock, const string& director, const string& title, const string& majorActor, int month, int year) : Movie('C', stock, director, title), majorActor(majorActor), month(month), year(year) {}

    //disaplys classic movie details
    void display() const override;

    //comparisons for sorting classics by release date and then major actor
    bool operator==(const Movie& other) const override;
    bool operator<(const Movie& other) const override;

private:
    //major actors name
    string majorActor;
    //monthg of release
    int month;
    //year of release
    int year;

};
#endif

