#include <iostream>
#include <string>
#include <vector>

using namespace std;

void parseInput(string str, vector<string>& vec);
void performAction();
int login(string user);
void logout();
int grant(string user, bool grant, string table);
int createUser(string name);

string loggedUser; //user we are logged in as
vector<string> allUsers; //keep track of all users - no duplicates

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

    //while user doesn't want to quit, take input and process the command
    do
    {
        getline(cin, cmd); //get the line of input to parse
        parseInput(cmd, userInput);
        performAction(); //
    }while(cmd != "EXIT");

    return 0;
}

/*
 * Split the string we have on spaces;
 * Get the key words and put them into the vector;
 * */
void parseInput(const string str, vector<string>& vec)
{
    vec.clear(); //clear out the vector
    //TODO: parse the input

}


/*
 * In scope:
 * Login
 * Log out
 * Grant (check logged user for granting ability for table)
 * Create user
 * */
void performAction()
{

}

/*
 * Log in as a user found in the table.
 * If user can't be found in the table, return an error.
 * */
int login(const string user)
{

    return 0; //success
}

/*
 * Log out of current user.
 * Just set to NULL.
 * */
void logout()
{
    loggedUser = NULL;
}


/*
 * Grant a user access to a table
 * May or may not have granting abilities
 * */
int grant(string user, bool grant, string table)
{

    return 0; //success
}


/*
 * Create a new user
 * Returns false if a user with this name already exists
 * */
int createUser(string name)
{
    bool exists = false;
    //search vector
    for(int i = 0; i < allUsers.size(); i++)
    {
        if(name.compare(allUsers[i]) == 0) // if we find a match, this user already exists and we can't create them
        {
            exists = true;
            return -1;
        }
    }

    if(!exists)
    {
        allUsers.push_back(name);
    }
    return 0;
}
