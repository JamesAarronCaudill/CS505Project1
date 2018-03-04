#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

using namespace std;

// Supporting functions:
void parseInput(string str, vector<string>& vec);
void performAction(vector<string> input);
int login(string user);
void logout();
int grant(string user, bool grant, string table);
int createUser(string name, bool isSecOff);
int createTable(string table);
/* SO Options */
int printFTable();
int forbidUser(string user, string table);
int printSOLogs();
/* SO Options end */
int searchVectorForKey(string key, vector<string> vec);
int searchVectorForUserAndTable(string name, string table, vector<string> names, vector<string> tables);
bool checkSecurityOfficer(string name);

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
vector< pair<string,string> > SOLogs;
/* Produces <user, table, hasGrant, granter> */

/*
 Main driver function for the program.
 Prompt the user and take in their input to pass to parsing;
 Then perform the action the user requested.
 */
int main() {
    string cmd;
    vector<string> userInput;

    cout << "Welcome! Commands understood are: \n LOGIN \n LOGOUT \n GRANT \n CREATEUSER \n CREATETABlE \n SOOPTIONS"
            << "\nType EXIT to leave.\n";

    //While user doesn't want to quit, take input and process the command
    do
    {
        cout << "\nCommands: \n";
        cout << "\n  1) LOGIN \n  2) LOGOUT \n  3) GRANT \n  4) CREATEUSER \n  5) CREATETABLE \n  6) SOOPTIONS \n  7) EXIT \n";
        cout << "Enter another command: " << endl;
        getline(cin, cmd); //get the line of input to parse

        //Makes sure that if the user presses enter no seg fault will occur.
        if(cmd != "")
        {
          parseInput(cmd, userInput);
          performAction(userInput);
        }
    }while(true);

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
 * Correctly handle user commands.
 * In scope:
 * Login
 * Log out
 * Grant (check logged user for granting ability for table)
 * Create user
 * Create table
 * Security officer options (if user is a SO)
 * Depends on what the parser obtains
 * */
void performAction(vector<string> input) {
    //for now: assume input will be 1 string
    if (input[0] == "LOGIN" || input[0] == "1") {
        string user;
        cout << "Enter username: ";
        cin >> user;
        cout << endl;
        //get username from the user
        login(user);
    }
    else if (input[0] == "LOGOUT" || input[0] == "2") {
        logout();
    }
    else if (input[0] == "GRANT" || input[0] == "3")
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
    else if(input[0] == "CREATEUSER" || input[0] == "4")
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
    else if(input[0] == "CREATETABLE" || input[0] == "5")
    {
        string table;
        cout << "Enter the table's name: ";
        cin >> table;

        createTable(table);
    }
    else if(input[0] == "SOOPTIONS" || input[0] == "6")
    {
      if(checkSecurityOfficer(loggedUser))
      {
        cout << "\n Security Officer Options:\n";
        cout << "\n  8) FORBIDDENTABLE \n";
        cout << "  9) FORBIDUSER\n";
        cout << " 10) SOLOGS\n";
        cout << "\n Please type enter a command: ";
        string cmd;
        vector<string> userInput;
        getline(cin, cmd); //get the line of input to parse
        parseInput(cmd, userInput);
        performAction(userInput);
      }
      if(!checkSecurityOfficer(loggedUser))
      {
        cout << "\nYou are not a Security Officer" << endl;
      }
      if(loggedUser == "")
      {
        cout << "\nYou must login, or create a User to access Security Officer Options" << endl;
      }
    }
    else if(input[0] == "7" || input[0] == "EXIT")
    {
      exit(0);
    }
    else if((input[0] == "FORBIDDENTABLE" || input[0] == "8") && checkSecurityOfficer(loggedUser))
    {
      printFTable();
    }
    else if((input[0] == "FORBIDUSER" || input[0] == "9") && checkSecurityOfficer(loggedUser))
    {
      string user;
      string table;

      cout << "\n Please enter the Users Name: ";
      cin >> user;
      cout << "\n Please enter the table to forbid the user from: ";
      cin >> table;
      forbidUser(user, table);
    }
    else if((input[0] == "SOLOGS" || input[0] == "10") && checkSecurityOfficer(loggedUser))
    {

      printSOLogs();
    }
    cin.ignore(256, '\n'); //since we are mixing cin and getline, we need to throw out the \n that remains
}

/*
 * Log in as a user (must be found in the table.)
 * If user can't be found in the table, return an error.
 * */
int login(const string user)
{
    int loc = searchVectorForKey(user, allUsers);
    if(loc == -1) //if user isn't found, return an error
    {
        cout << "Login failed. User could not be found." << endl;
        return -1;
    }
    else
    {
        loggedUser = allUsers[loc]; //update logged in user name
        cout << "Success -- user " << user << " logged in." << endl;
        return 0;
    }
    return 0; //success
}

/*
 * Log out of current user.
 * Just set loggedUser to an empty string.
 * */
void logout()
{
    loggedUser = "";
    cout << "User has been logged out." << endl;
}


/*
 * Grant a user access to a table
 * Check for granter's granting abilities & respond accordingly
 * Also check that the grantee is not in the forbidden table for this table.
 * */
int grant(string user, bool grant, string table)
{
    //check if current user has granting ability
    int loc = searchVectorForUserAndTable(loggedUser, table, assignedUsers, assignedTables);
    int logSize = SOLogs.size();
    if(loc == -1 || !hasGrantAccess[loc] || loggedUser == ""){
        //error -- user is not able to grant for this table
        cout << "User " << loggedUser << " cannot grant access to table " << table << endl;
        SOLogs.push_back(make_pair(loggedUser, ("User " + loggedUser + " attempted to add " + user + " to grant access to " + table + " without the permision." )));
        return 0;
    }

    //check if grantee is in the forbidden list for this table
    loc = searchVectorForUserAndTable(user, table, forbiddenUsers, forbiddenTables);
    if(loc != -1) //if we find the user in the forbidden list, we can't grant access
    {
        cout << "User " << user << " was found in the forbidden list." << endl;
        if(checkSecurityOfficer(loggedUser))
        {
          cout << "Did you want to remove user from the forbidden table, and add them to the assigned table." << endl;
          cout << "1) YES\n";
          cout << "2) NO\n";

          string input;
          cin >> input;

          if(input == "1" || input == "YES")
          {

            forbiddenUsers.erase(forbiddenUsers.begin() - loc);
            forbiddenTables.erase(forbiddenTables.begin() - loc);
            assignedUsers.push_back(user);
            assignedTables.push_back(table);


            return 0;
          }
          if(input == "2" || input == "NO")
          {
            return 0;
          }
        }
        return -1;
    }

    loc = searchVectorForKey(user, allUsers);
    if(loc == -1) //if user isn't found, return an error
    {
        cout << "Failed. User: " << user << " could not be found." << endl;
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
 * Create a table as long as the table does not already exist
 * automatically gives creating user grant access
 */
int createTable(string table)
{
    //Check if the table exists
    int loc = searchVectorForKey(table, assignedTables);

    //check if grantee is in the forbidden list for this table
    int loc2 = searchVectorForUserAndTable(loggedUser, table, forbiddenUsers, forbiddenTables);

    if(loc == -1 && loc2 == -1 && loggedUser != ""){
      assignedUsers.push_back(loggedUser);
      assignedTables.push_back(table);
      hasGrantAccess.push_back(1);
      granter.push_back(loggedUser);
      return 0;
    }

    if(loc != -1) //if we find the table exists
    {
        cout << "The table " << table << " already exists." << endl;
        return -1;
    }
    if(loc2 != -1) //if we find the user in the forbidden list, we can't grant access
    {
        cout << "User " << loggedUser << " was found in the forbidden list." << endl;
        return -1;
    }
    if(loggedUser == "")
    {
      cout << "\nYou must log in to create a table" << endl;
    }

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
    if(!allUsers.empty() && searchVectorForKey(name, allUsers) != -1) //if the user name exists already, we can't create the user
    {
        return -1;
    }
    //if we make it through the search, the user doesn't exist--add them
    allUsers.push_back(name);
    isSecurityOfficer.push_back(isSecOff);
    return 0; //success
}

//search a vector for a key; return the location or -1 if not found
int searchVectorForKey(string key, vector<string> vec)
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

/*
 This searches to see if a user has an associated table pairing
 Searches for <name, table> pair
*/
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

/*
This prints the forbidden table, very similar to searchVectorForUserAndTable but this doesnt return users and tables, only prints.
*/
int printFTable()
{
  cout << "\nFORBIDDEN TABLE:\n";
  for(int i = 0; i < forbiddenUsers.size(); i++)
  {
    cout << "USER: " << forbiddenUsers[i] << " TABLE: " << forbiddenTables[i] << endl;
  }
  if(forbiddenUsers.size() == 0)
  {
    cout << "\nTable is empty.";
    return 0;
  }
  return 0;
}


/*
This is the function that add's users to the forbidden table
*/
int forbidUser(string user, string table)
{
  int sizeU = forbiddenUsers.size();
  int sizeT = forbiddenTables.size();
  int loc = searchVectorForUserAndTable(user, table, forbiddenUsers, forbiddenTables);
  int loc2 = searchVectorForUserAndTable(user, table, assignedUsers, assignedTables);
  int logSize = SOLogs.size();
  if(loc == -1)
  {
    if(loc2 == -1)
    {
      if(sizeU == sizeT)
      {
        forbiddenUsers.push_back(user);
        forbiddenTables.push_back(table);
        return 0;
      }
    }
    if(loc2 != -1)
    {
      cout << "\nThis user is on the assigned list for this table, would you like to remove them and add them to the forbidden list?\n";
      cout << "YES" << endl;
      cout << "NO" << endl;
      cout << "Please type your choice here: ";
      string cmd;
      cin >> cmd;
      //A case if the user enters yes
      if(cmd == "YES")
      {
        //This makes sure that the vector is not off sized. This should never fail.
        if(sizeU == sizeT)
        {
          forbiddenUsers.push_back(user);
          forbiddenTables.push_back(table);
          assignedUsers.erase(assignedUsers.begin() - loc2);
          assignedTables.erase(assignedTables.begin() - loc2);
          SOLogs.push_back(make_pair(loggedUser, ("The Security officer " + loggedUser + " added " + user + " to the forbidden table, when they were on the assigned table previously.")));
          return 0;
        }
      }
      //A case if the user enters no
      if(cmd == "NO")
      {
        return 0;
      }
      //A case is the user enters no or yes
      if(cmd != "NO" || cmd != "YES")
      {
        cout << "\nSorry that was not a choice.\n";
        return 0;
      }
      return 0;
    }
  }
  if(loc != -1)
  {
    cout << "\nThis user is already in the forbidden table for this table!\n";
    return 0;
  }
  return 0;
}

int printSOLogs()
{
  for(int i = 0; i < SOLogs.size(); i++)
  {
    cout << "      User: " << SOLogs[i].first << " Action: " << SOLogs[i].second << "\n" << endl;
  }
  if(SOLogs.size() == 0)
  {
    cout << "\n This table is empty \n";
  }
  return 0;
}


bool checkSecurityOfficer(string name)
{
  if(name != "")
  {
    int loc = searchVectorForKey(name, allUsers);
    return isSecurityOfficer[loc];
  }
  return false;
}
