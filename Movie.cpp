#include "Movie.h"

//virtual desctructor for proper cleanup 
//for deleting derived class objects
Movie::~Movie() {

}

//display function is pure virtual
//implementation provided in dervied classes

//returns type of movie, F, D or C
char Movie::getType() const {
    return type;
}

//returns number of copies in stock
int Movie::getStock() const {
    return stock;
}

//increase stock count, occurs when movie is returned
void Movie::increaseStock(int count) {
    stock += count;
}

//decrease stock count, occurs when a movie is borrowed
bool Movie::decreaseStock() {
    //only decrease if there was a copy available to borrow
    if (stock > 0) {
        stock--;
        return true;
    }
    //no stock to decrease
    return false;
}

//returns name of director
string Movie::getDirector() const {
    return director;
}

//returns title of movie
string Movie::getTitle() const {
    return title;
}

//COMEDY

void Comedy::display() const {
    cout << "Type: Comedy\n"
    << "Title: " << title << "\n"
    << "Director: " << director << "\n"
    << "Year: " << year << "\n"
    << "Stock: " << stock << endl;
}

//to ensure being able to compare generic 'Movie' types possibly
//we need to use Movie& as object type here then static cast to 'Comedy'
//also allowing us to store all movies in single container and perform
//generic operations on them in the future
//these operators also need to access fields specific to derived classes
//based on title and year
bool Comedy::operator==(const Movie& other) const {
    const Comedy& otherComedy = static_cast<const Comedy&>(other);
    return title == otherComedy.title && year == otherComedy.year;
}

//based on title and THEN year
bool Comedy::operator<(const Movie& other) const {
    const Comedy& otherComedy = static_cast<const Comedy&>(other);
    return title < otherComedy.title || (title == otherComedy.title && year < otherComedy.year);
}

//DRAMA

void Drama::display() const {
    cout << "Type: Drama\n"
    << "Director: " << director << "\n"
    << "Title: " << title << "\n"
    << "Year: " << year << "\n"
    << "Stock: " << stock << "\n" << endl;
}

//based on director and title
bool Drama::operator==(const Movie& other) const {
    const Drama& otherDrama = static_cast<const Drama&>(other);
    return director == otherDrama.director && title == otherDrama.title;
}

//based on director THEN title
bool Drama::operator<(const Movie& other) const {
    const Drama& otherDrama = static_cast<const Drama&>(other);
    return director < otherDrama.director || (director == otherDrama.director && title < otherDrama.title);
}

//CLASSIC

void Classic::display() const {
    cout << "Type: Classic\n"
    << "Director: " << director << "\n"
    << "Title: " << title << "\n"
    << "Major Actor: " << majorActor << "\n"
    << "Date: " << month << " " << year << "\n"
    << "Stock: " << stock << endl;
}

//based on release date and major actor
bool Classic::operator==(const Movie& other) const {
    const Classic& otherClassic = static_cast<const Classic&>(other);
    return year == otherClassic.year && month == otherClassic.month && majorActor == otherClassic.majorActor;
}

//based on release date THEN major actor
bool Classic::operator<(const Movie& other) const {
    const Classic& otherClassic = static_cast<const Classic&>(other);
    return year < otherClassic.year || (year == otherClassic.year && (month < otherClassic.month || (month == otherClassic.month && majorActor < otherClassic.majorActor)));
}

