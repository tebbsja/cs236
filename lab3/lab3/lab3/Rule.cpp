//
//  Rule.cpp
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Rule.h"
#include <sstream>

Rule::Rule(Predicate str)
{
    name = str;
}

void Rule::insertPreds(vector<Predicate> add)
{
    addtlPreds = add;
}

string Rule::toString()
{
    stringstream ss;
    
    ss << name.toString() << " :- ";
    for (unsigned int i=0; i < addtlPreds.size(); i++)
    {
        ss << addtlPreds[i].toString();
        if (i < addtlPreds.size() - 1)
        {
            ss << ",";
        }
    }
    return ss.str();
}
