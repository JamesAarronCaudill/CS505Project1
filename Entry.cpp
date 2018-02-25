//
// Created by Kristina Gessel on 2/24/18.
//

#include "Entry.h"

Entry::Entry(string nm, bool sec)
{
    name = nm;
    SO = sec;
}

string Entry::getName()
{
    return name;
}

bool Entry::isSecurityOfficer()
{
    return SO;
}
