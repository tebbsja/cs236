//
//  Tuple.cpp
//  lab2
//
//  Created by Austin Tebbs on 3/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Tuple.h"
#include <sstream>

void Tuple::addTuple(string to_add)
{
    push_back(to_add);
}

string Tuple::getTupleAtIndex(int i)
{
    return at(i);
}

string Tuple::toString()
{
    stringstream ss;
    for (unsigned int i=0; i < this->size(); i++)
    {
        ss << at(i);
    }
    
    return ss.str();
}