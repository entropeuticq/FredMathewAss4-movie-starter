#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "Inventory.h"
#include "CustomerManager.h"
#include "Transaction.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

//class for handling reading and processing commands from a file
//uses Inventory and CustomerManager classes for this purpose
class CommandProcessor {
public:
    //constructor, initialize with refrecnes to inventory and customer manager
    CommandProcessor(Inventory& inventory, CustomerManager& customerManager);

    //function to process commands from given files
    void processCommands(const string& filename);

    //process command strings
    void processCommandString(const string& command);


private:
    Inventory& inventory;
    CustomerManager& customerManager;

    //execute borrow command
    void processBorrowCommand(int customerID, char mediaType, char movieType, const string& attributes);
    
    //execute return command
    void processReturnCommand(int customerID, char mediaType, char movieType, const string& attributes);

    //execute inventory display command
    void processInventoryCommand();

    //execute transaction history command
    void processHistoryCommand(int customerID);


};
#endif

