/*
 * Contains information about a user
 * */

//
// Created by Kristina Gessel on 2/24/18.
//

#ifndef PROJECT1_ENTRY_H
#define PROJECT1_ENTRY_H

using namespace std;
#include <string>

class Entry {
public:
    Entry(string nm, bool sec);
    string getName();
    bool isSecurityOfficer();

private:
    string name;
    bool SO; //is security officer or not

};


#endif //PROJECT1_ENTRY_H
