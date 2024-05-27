# Self-Evaluation

## Name(s): 

Out of 25 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes/No
Yes
- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: 0

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: Full
History: Full
Borrow: Full
Return: Full


Q: -1 for each compilation warning, min -3: 0

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: ENTER_NUMBER

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: ENTER_NUMBER

- Check under *4. clang-format does not find any formatting issues*


Q: -2 for any detected memory leak: 0

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: 0

to my knowledge every function/large code block is called during testing, super hard to ensure this though so I could be wrong
- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): 0

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: file : CommandProcessor.cpp
function: void CommandProcessor::processCommandString (const string& command)
location : default case in switch statements

invalid movie type: file : Inventory.cpp
functions : void Inventory::addMovie(Movie* movie) {

Movie* Inventory::findMovie(char type, const string& attributes) const {

void Inventory::loadMovies(const string& filename) {



invalid customer ID: file : CustomHashMap.cpp
functions : CustomHashMap::retrieve
file : CommandProcessor.cpp
functions : CommandProcessor::processBorrowCommand, CommandProcessor::processReturnCommand, 
CommandProcessor::processHistoryCommand
 
invalid movie: file : CommandProcessor.cpp
functions : CommandProcessor::processBorrowCommand, 
CommandProcessor::processReturnCommand

factory classes: CustomerManager, Inventory

hashtable: Hashtable is used to store and manage the customer objects. 

container used for comedy movies: map<string, Movie*> comedyMap //Within inventory.h

function for sorting comedy movies: file : Movie.h
function :     bool operator==(const Movie& other) const override;
    bool operator<(const Movie& other) const override;

function where comedy movies are sorted: file : Inventory.cpp
function : void Inventory::addMovieToMap(Movie* movie, map<string, Movie*>& moviemap, const string& key) {
(When a comedy movie is added to the comedyMap, it is inserted in a sorted manner according to the key generated from its title and year.)

functions called when retrieving a comedy movie based on title and year: file : Inventory.cpp
functions : Movie* Inventory::findMovie(char type, const string& attributes) const {

string Inventory::parseAttributes(char type, const string& attributes) const {

find(key);
getline(iss, majorActor);
majorActor.erase(0, majorActor.find_first_not_of(" \t"));
majorActor.erase(majorActor.find_last_not_of(" \t") + 1);
return to_string(year) + " " + to_string(month) + " " + majorActor;




functions called for retrieving and printing customer history: file : Customer.cpp
functions : void Customer::displayHistory() const {

string Customer::getFullName() const {

void Borrow::display() const {

void Return::display() const {


container used for customer history: file : Customer.h
vector<const Transaction*> transactions

functions called when borrowing a movie: 
Main call stack:
CommandProcessssor::processCommands-->CommandProcessssor::processCommandString-->CommandProcessssor::processBorrowCommand-->Borrow constructor
->Borrow::execute-->Movie::decreaseStock()-->Customer::addTransaction
Auxilary functions:
CommandProcessor::removeCommasAndLeadingSpace CustomerManager::findCustomer CustomHashMap::retrieve CustomHashMap::Hash
Inventory::findMovie Inventory::parseAttributes

explain borrowing a movie that does not exist: in Inventory.cpp 
Movie* Inventory::findMovie(char type, const string& attributes) const {

    //returns found movie or nullptr if not found
    if (it != movieMap->end()) {
        cout << "Found movie with key: " << key << endl;
        return it->second;
    } else {
        cout << "Movie with key: " << key << " not found." << endl;
        return nullptr;
    }

in CommandProcessor.cpp - void CommandProcessor::processBorrowCommand(int customerID, char mediaType, char movieType, const string& attributes) {
    //finds movie by type and attributes
    Movie* movie = inventory.findMovie(movieType, attributes);

        if (!movie) {
        //error if movie not found
        cerr << "Error: Movie not found for borrow command with attributes: " << attributes << endl;
        return;
    }
(uses call to findMovie in inventory.cpp, If the movie is not found (if (!movie)), an error message is printed, and the command is not processed further.)



explain borrowing a movie that has 0 stock: in Transaction.cpp - bool Borrow::execute() {
     } else {
        //alerts if borrow not executed successfully
        cout << "Borrow denied, none in stock." << endl;
        return false;
(if none in stock, error message is is printed, and execute aborts)

explain returning a movie that customer has not checked out: 
->  CommandProcessor reads the return from the file
->  a transaction is created with the correct movie and customer
->  transaction::execute() is called
->  execute() calls Customer::hasActiveBorrow()
->  since there is no active borrow, this returns false
->  execute() then determines the transaction is faulty and also returns false
->  CommandProcessor deletes the transaction object due to the false return

any static_cast or dynamic_cast used: Yes


Q: Total points: ADD_ALL_POINTS (max 25)