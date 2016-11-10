//
//  Tuple.h
//  lab2
//
//  Created by Austin Tebbs on 3/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Tuple_h
#define Tuple_h

#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

class Tuple : public vector<string>
{
public:
    void addTuple(string to_add);
    string getTupleAtIndex(int i);    
};

#endif /* Tuple_h */
