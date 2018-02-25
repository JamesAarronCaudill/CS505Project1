#include <iostream>
#include <string>
#include <vector>
#include "Entry.h"

using namespace std;

int main() {
    string cmd; //holds user's command
    string grantor; //user who is doing the inserting/deleting
    string user; //user of interest; placeholder
    vector<Entry> forbidden; //table of forbidden users
    vector<Entry> authorized; //table of authorized users

    cout << "Welcome! Commands understood are: \n <grantor_name> INSERT <user> INTO <table> \n<grantor_name> REMOVE <user> FROM <table> (Will only succeed for security officers)"
            << "\nType EXIT to leave.\nPlease enter your first command.\n";
//TODO: handle setting permissions
    //TODO: use maps and keys to point to each Entry object in the vector

    //while user doesn't want to quit, take input and process the command
    do
    {
        cin >> cmd;
        grantor = cmd; //store grantor info for checking permissions etc.
        cout << grantor << ": grantor"<< endl;
        cin.ignore(256, ' ');
        cin >> cmd; //now process what this user wants to do
        cout << "Now have: " << cmd << endl;
        //respond to command
        //check necessary tables & react to any conflicts
        if(cmd.compare("INSERT") == 0)
        {
            cout << "Inserting..." << endl;
            cin.clear();
            cin >> cmd; //get user
            user = cmd; //store user for entry into table
            cout << cmd << ": user" << endl; //test
            cin >> cmd; //into--ignore
            cin >> cmd; //get table name
            cout << cmd << ": table" << endl;
            if(cmd.compare("FORBIDDEN")) //
            {
                //add this user to FORBIDDEN table
                //make sure grantor has security officer status first
                forbidden.push_back(Entry(user, 0)); //no one in forbidden will be a security officer
                //set map and keys to point to this user when looking for their name
            }
            else if(cmd.compare("AUTHORIZED"))
            {
                //TODO: should user be a security officer? add extra case to handle
                //make sure user isn't in forbidden table; if so, print a message; fails
                authorized.push_back(Entry(user, 1));
            }

        }
        else if(cmd.compare("REMOVE") == 0)
        {
            cout << "Removing..." << endl;
            cin.clear();
            cin >> cmd; //get user
            user = cmd; //store user for entry into table
            cout << cmd << ": user" << endl; //test
            cin >> cmd; //into--ignore
            cin >> cmd; //get table name
            cout << cmd << ": table" << endl;
            if(cmd.compare("FORBIDDEN")) //
            {
                //make sure grantor has SO status
                //search for user in forbidden vector
                //if found, remove user
            }
            else if(cmd.compare("AUTHORIZED"))
            {
                //make sure grantor has SO status?
                //search for user in authorized vector
                //if found, remove user
            }
        }

    }while(cmd.compare("EXIT") != 0);

    return 0;
}