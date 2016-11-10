//
//  Predicate.h
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Predicate_h
#define Predicate_h

#include "Parameter.h"
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class Predicate
{
public:
    string name;
    vector<Parameter> parameters;
    Predicate(){}
    Predicate(string id);
    void push_back(Parameter param);
    string toString();
};

#endif /* Predicate_h */
