//
//  Rule.h
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Rule_h
#define Rule_h
#include "Predicate.h"
#include <vector>

#include <stdio.h>

class Rule
{
private:
    Predicate name;
    vector<Predicate> addtlPreds;
    
    
public:
    Rule(){}
    Rule(Predicate str);
    void insertPreds(vector<Predicate> add);
    string toString();
    vector<Predicate> getPredicates();
    Predicate getName(){ return name;}
    
    
};

#endif /* Rule_h */
