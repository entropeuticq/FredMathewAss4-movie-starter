#include "CustomerManager.h"

using namespace std;

void CustomerManager::loadCustomers(const string &filename)
{
    string currentLine;
    string IDs;
    int ID;
    string firstName;
    string lastName;

    ifstream thisFile(filename);

    if (!thisFile.is_open())
    {
        cerr << "Couldn't open " << filename << endl;
        return;
    }

    // Read the first line separately
    getline(thisFile, currentLine);
    stringstream lineStream(currentLine); // Create a stringstream for parsing

    // Parse the first line to get data
    // Need this here because the loop was not reading first line because of the getline break condition
    lineStream >> IDs >> lastName >> firstName;
    //ensures id is an integer
    try
    {
        ID = stoi(IDs);
        addCustomer(ID, firstName, lastName);
    }
    catch (const invalid_argument &)
    {
        cout << "Error: Invalid Customer ID" << endl;
        // prevents invalid customer ID
    }

    // Now iterate through the rest of the file
    while (getline(thisFile, currentLine))
    {
        lineStream.clear();          // Clear any flags from previous parsing
        lineStream.str(currentLine); // Set the stringstream to the new line
        lineStream >> IDs >> lastName >> firstName;
        try
        {
            ID = stoi(IDs);
            addCustomer(ID, firstName, lastName);
        }
        catch (const invalid_argument &)
        {
            cout << "Error: Invalid Customer ID" << endl;
            // prevents invalid customer ID
        }
    }

    thisFile.close();
}

Customer *CustomerManager::findCustomer(int custID) const
{
    return customerMap.retrieve(custID);
}

void CustomerManager::displayCustomers() const
{
    customerMap.display();
}

void CustomerManager::addCustomer(int ID, const string &firstName, const string &lastName)
{
    // create a new customer
    Customer *x = new Customer(ID, firstName, lastName);
    // add it to the customer hash map
    customerMap.add(x);
}
