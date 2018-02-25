#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Supporting functions:
void parseInput(string str, vector<string>& vec);
void performAction(vector<string> input);
int login(string user);
void logout();
int grant(string user, bool grant, string table);
int createUser(string name, bool isSecOff);
int searchVectorForUser(string key, vector<string> vec);
int searchVectorForUserAndTable(string name, string table, vector<string> names, vector<string> tables);
bool checkSecurityOfficer(string name);

//TODO: implement security officer capabilities?

string loggedUser; //user we are logged in as
vector<string> allUsers; //keep track of all users - no duplicates
vector<bool> isSecurityOfficer; //keep track of the users who are security officers; corresponds with allUsers

/* To produce the forbidden table we use the following vectors: */
vector<string> forbiddenUsers;
vector<string> forbiddenTables; //corresponds with forbiddenUsers
/* Produces <user, table> */

/* To produce the assigned table we use the following vectors: */
vector<string> assignedUsers;
vector<string> assignedTables; //corresponds with assignedUsers
vector<bool> hasGrantAccess; //corresponds with assigned vectors
vector<string> granter; //keeps track of the user who granted the user in question access
/* Produces <user, table, hasGrant, granter> */


int main() {
    string cmd;
    vector<string> userInput;

    cout << "Welcome! Commands understood are: \n LOGIN \n LOGOUT \n GRANT \n CREATEUSER"
            << "\nType EXIT to leave.\nPlease enter your first command.\n";
    //TODO: add a CREATETABLE option? (user becomes owner & can grant access)

    //while user doesn't want to quit, take input and process the command
    do
    {
        cout << "Enter another command: " << endl;
        getline(cin, cmd); //get the line of input to parse
        parseInput(cmd, userInput);
        performAction(userInput); //
    }while(cmd != "EXIT");

    return 0;
}



/***********************
 * Supporting functions:
 ************************/

/*
 * Split the string we have on spaces;
 * Get the key words and put them into the vector;
 * */
void parseInput(const string str, vector<string>& vec)
{
    string buf;
    stringstream ss(str);
    vec.clear(); //clear out the vector
    while(ss >> buf)
    {
        vec.push_back(buf);
    }
}


/*
 * In scope:
 * Login
 * Log out
 * Grant (check logged user for granting ability for table)
 * Create user
 * Depends on what the parser gets
 * */
void performAction(vector<string> input) {
    //for now: assume input will be 1 string
    if (input[0] == "LOGIN") {
        string user;
        cout << "Enter username: ";
        cin >> user;
        cout << endl;
        //get username from the user
        login(user);
    }
    else if (input[0] == "LOGOUT") {
        logout();
    }
    else if (input[0] == "GRANT")
    {
        string user;
        string table;
        string tmp; //hold y/n until it's converted to bool
        bool grnt;
        cout << "Enter user to grant access: ";
        cin >> user;
        cout << "Enter table name: ";
        cin >> table;
        cout << "With grant access? (y/n) ";
        cin >> tmp;
        if(tmp == "y")
        {
            grnt = true;
        }
        else grnt = false;
        grant(user, grnt, table);
    }
    else if(input[0] == "CREATEUSER")
    {
        string name;
        string tmp;
        bool SO; //security officer
        cout << "Enter the user's name: ";
        cin >> name;
        cout << "Is this user a security officer? (y/n) ";
        cin >> tmp;
        if(tmp == "y"){
            SO = true;
        }
        else SO = false;
        createUser(name, SO);
    }
    cin.ignore(256, '\n'); //since we are mixing cin and getline, we need to throw out the \n that remains
}

/*
 * Log in as a user found in the table.
 * If user can't be found in the table, return an error.
 * */
int login(const string user)
{
    int loc = searchVectorForUser(user, allUsers);
    if(loc == -1) //if user isn't found, return an error
    {
        cout << "Login failed. User could not be found." << endl;
        return -1;
    }
    else
    {
        loggedUser = allUsers[loc]; //update logged in user name
        cout << "Success -- user " << user << " logged in." << endl;
    }
    return 0; //success
}

/*
 * Log out of current user.
 * Just set to empty string.
 * */
void logout()
{
    loggedUser = "";
    cout << "User has been logged out." << endl;
}


/*
 * Grant a user access to a table
 * May or may not have granting abilities
 * */
int grant(string user, bool grant, string table)
{
    //check if current user has granting ability
    int loc = searchVectorForUserAndTable(loggedUser, table, assignedUsers, assignedTables);
    if(loc == -1 || !hasGrantAccess[loc]){
        //error -- user is not able to grant for this table
        cout << "User " << loggedUser << " cannot grant access to table " << table << endl;
        return -1;
    }

    //check if grantee is in the forbidden list for this table
    loc = searchVectorForUserAndTable(user, table, forbiddenUsers, forbiddenTables);
    if(loc != -1) //if we find the user in the forbidden list, we can't grant access
    {
        cout << "User " << user << " was found in the forbidden list." << endl;
        return -1;
    }

    //if we make it this far, the user is able to be added to the assigned list; add them
    assignedUsers.push_back(user);
    assignedTables.push_back(table);
    hasGrantAccess.push_back(grant);
    granter.push_back(loggedUser);

    return 0; //success
}


/*
 * Create a new user
 * May or may not be a security officer
 * Returns false if a user with this name already exists
 * */
int createUser(string name, bool isSecOff)
{
    //search vector
    if(!allUsers.empty() && searchVectorForUser(name, allUsers) != -1) //if the user name exists already, we can't create the user
    {
        return -1;
    }
    //if we make it through the search, the user doesn't exist--add them
    allUsers.push_back(name);
    isSecurityOfficer.push_back(isSecOff);
    return 0; //success
}

//search a vector for a key; return the location or -1 if not found
int searchVectorForUser(string key, vector<string> vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(key == vec[i])
        {
            return i;
        }
    }
    return -1;
}

int searchVectorForUserAndTable(string name, string table, vector<string> names, vector<string> tables)
{
    for(int i = 0; i < names.size(); i++)
    {
        if(name == names[i] && table == tables[i])
        {
            return i;
        }
    }
    return -1;
}

bool checkSecurityOfficer(string name)
{
    int loc = searchVectorForUser(name, allUsers);
    return isSecurityOfficer[loc];
}