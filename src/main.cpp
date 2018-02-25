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
int searchVectorForUser(string key, vector<string> vec);
int searchVectorForUserAndTable(string name, string table, vector<string> names, vector<string> tables)

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
    int loc = searchVectorForUser(user, allUsers);
    if(loc == -1) //if user isn't found, return an error
    {
        return -1;
    }
    else
    {
        loggedUser = allUsers[loc]; //update logged in user name
    }
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
 * Returns false if a user with this name already exists
 * */
int createUser(string name)
{
    //search vector
    if(searchVectorForUser(name, allUsers) != -1) //if the user name exists already, we can't create the user
    {
        return -1;
    }
    //if we make it through the search, the user doesn't exist--add them
    allUsers.push_back(name);
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