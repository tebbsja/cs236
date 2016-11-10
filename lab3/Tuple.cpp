//
//  Tuple.cpp
//  lab2
//
//  Created by Austin Tebbs on 3/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Tuple.h"

void Tuple::addTuple(string to_add)
{
    push_back(to_add);
}

string Tuple::getTupleAtIndex(int i)
{
    return at(i);
}