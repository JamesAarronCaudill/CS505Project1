//
// Created by Kristina Gessel on 2/24/18.
//
/*
 *Table class - contains a CSV list of entries
 *Special case: forbidden table can only be accessed by security officer
 * */

#ifndef PROJECT1_TABLE_H
#define PROJECT1_TABLE_H

using namespace std;
#include <string>

class Table {

    public:
    string getName();

    private:
    string tableName;
    bool contains(string key); //search the table for a given key

};


#endif //PROJECT1_TABLE_H
