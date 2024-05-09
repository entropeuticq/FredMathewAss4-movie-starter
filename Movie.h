#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>

using namespace std;

class Movie {
public:
    Movie(char type, int stock, const string& director, const string& title) : type(type), stock(stock), director(director), title(title) {}

    virtual ~Movie();

    //virutal function to display movie details, derived classes will implement this
    virtual void display() const;

    char getType() const;
    int getStock() const;
    void increaseStock(int count);
    bool decreaseStock();

    string getDirector() const; 
    string getTitle() const;

    //derived classes will implement each comparison logic
    virtual bool operator==(const Movie& other) const;
    virtual bool operator<(const Movie& other) const;

protected:
    char type;
    int stock;
    string director;
    string title;

};

class Comedy : public Movie {
public:
    Comedy(int stock, const string& director, const string& title, int year) : Movie('F', stock, director, title), year(year) {}
    void display() const override;
    bool operator==(const Movie& other) const override;
    bool operator<(const Movie& other) const override;

private:
    int year;
};

class Drama : public Movie {
public:
    Drama(int stock, const string& director, const string& title, int year) : Movie('D', stock, director, title), year(year) {}
    void display() const override;
    bool operator==(const Movie& other) const override;
    bool operator<(const Movie& other) const override;

private:
    int year;

};

class Classic : public Movie {
public:
    Classic(int stock, const string& director, const string& title, const string& majorActor, int month, int year) : Movie('C', stock, director, title), majorActor(majorActor), month(month), year(year) {}

    void display() const override;
    bool operator==(const Movie& other) const override;
    bool operator<(const Movie& other) const override;

private:
    string majorActor;
    int month;
    int year;

};
#endif