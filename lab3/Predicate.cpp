//
//  Predicate.cpp
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Predicate.h"
#include <sstream>
#include <iostream>

Predicate::Predicate(string id)
{
    name = id;
}

void Predicate::push_back(Parameter param)
{
    parameters.push_back(param);
}

string Predicate::toString()
{
    stringstream ss;
    ss << name << "(";
    for (unsigned int i =0; i < parameters.size();i++)
    {
        if (parameters[i].name != "")
        {
            ss << parameters[i].name;
        }
        else
        {
            ss << parameters[i].value;
        }
        if (i < parameters.size() -1)
        {
            ss << ",";
        }
    }
    
    ss << ")";
    
    return ss.str();
}

