#include "CommandProcessor.h"

//constructor
CommandProcessor::CommandProcessor(Inventory& inventory, CustomerManager& customerManager)
    : inventory(inventory), customerManager(customerManager) {}

//process commands read from file
void CommandProcessor::processCommands(const string& filename) {
    //opening file
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: could not open file " << filename << endl;
        return;
    }

    string line;
    //read file line by line
    while (getline(infile, line)) {
        //process lines when theyre not empty
        if (!line.empty()) {
            processCommandString(line);
        }
    }
}

//function for processing command strings
void CommandProcessor::processCommandString(const string& command) {
    //create a string stream using command string
    istringstream iss(command);

    //reading command types B, R, I, H
    char commandType;
    iss >> commandType;

    //switch based on different command types
    switch (commandType) {
        case 'B' : {
            //borrow command - read ID, media tpye and move type
            int customerID;
            char mediaType;
            char movieType;
            iss >> customerID >> mediaType >> movieType;
            //read the rest of the line as attributes
            string attributes;

            getline(iss, attributes);
            attributes = removeCommasAndLeadingSpace(attributes);
            //processing borrow command
            processBorrowCommand(customerID, mediaType, movieType, attributes);
            break;
        }
        case 'R' : {
            //return command - ID, mediat type and movie type
            int customerID;
            char mediaType;
            char movieType;
            iss >> customerID >> mediaType >> movieType;

            //reading rest of line as attributes
            string attributes;

            getline(iss, attributes);
            attributes = removeCommasAndLeadingSpace(attributes);
            
            //process return command
            processReturnCommand(customerID, mediaType, movieType, attributes);
            break;
        }
        case 'I' : {
            //inventory command - processes inventory display
            processInventoryCommand();
            break;
        }
        case 'H' : {
            //history command - reads customer ID
            int customerID;
            iss >> customerID;

            //process history command
            processHistoryCommand(customerID);
            break;
        }
        default:
            //prints error message for invalid command types
            cerr << "Error: Invalid command type " << commandType << " in command: " << command << endl;
            break;
    }
}

//processes borrow commands
void CommandProcessor::processBorrowCommand(int customerID, char mediaType, char movieType, const string& attributes) {
    //validates media type, only one type currently, D for DVD
    if (mediaType != 'D') {
        cerr << "Error: Invalid media type " << mediaType << " for borrow command." << endl;
        return;
    }

    //finds customer by ID
    Customer* customer = customerManager.findCustomer(customerID);
    if (!customer) {
        //error if customer not found
        cerr << "Error: customer ID " << customerID << " not found." << endl;
        return;
    }
    
    
    //finds movie by type and attributes
    string parsedAttributes = inventory.parseAttributes(movieType, attributes);

    //debug statement
    cout << "Borrow comman - parsed attributes: " << parsedAttributes << endl;

    Movie* movie = inventory.findMovie(movieType, parsedAttributes);
    if (!movie) {
        //error if movie not found
        cerr << "Error: Movie not found for borrow command with attributes: " << attributes << endl;
        return;
    }

    //creates a borrow transaction and executes it
    Borrow* borrowTransaction = new Borrow(customer, movie);
    bool isSuccessful = borrowTransaction->execute();
    if(!isSuccessful) {
        delete borrowTransaction;
    }

}

void CommandProcessor::processReturnCommand(int customerID, char mediaType, char movieType, const string& attributes) {
    //validates media type, only one type currently, D for DVD
    if (mediaType != 'D') {
        cerr << "Error: Invalid media type " << mediaType << " for borrow command." << endl;
        return;
    }

    //finds customer by ID
    Customer* customer = customerManager.findCustomer(customerID);
    if (!customer) {
        //error if customer not found
        cerr << "Error: customer ID " << customerID << " not found." << endl;
        return;
    }

    string parsedAttributes = inventory.parseAttributes(movieType, attributes);

    //debug statement
    cout << "Return command - parsed attributes: " << parsedAttributes << endl;

    //finds movie by type and attributes
    Movie* movie = inventory.findMovie(movieType, parsedAttributes);
    if (!movie) {
        //error if movie not found
        cerr << "Error: Movie not found for borrow command with attributes: " << attributes << endl;
        return;
    }

    //creates a borrow transaction and executes it
    Return* returnTransaction = new Return(customer, movie);
    returnTransaction->execute();
    customer->addTransaction(returnTransaction);
}


//processing inventory display commands
void CommandProcessor::processInventoryCommand() {
    inventory.display();
}

//processing history commands
void CommandProcessor::processHistoryCommand(int customerID) {
    Customer* customer = customerManager.findCustomer(customerID);
    if(!customer) {
        cerr << "Error: customer ID " << customerID << " not found." << endl;
        return;
    }

    customer->displayHistory();
}

string CommandProcessor::removeCommasAndLeadingSpace(string str) {
    string attributesNoCommas = "";
    string attributesNoCommasOrLeadingSpace = "";
    for(const auto &attribute: str) {
        if(attribute != ',') {
            attributesNoCommas += attribute;
        }
    }
    attributesNoCommasOrLeadingSpace = attributesNoCommas.substr(1, attributesNoCommas.size());
    return attributesNoCommasOrLeadingSpace;
}


