//
//  DatalogProgram.hpp
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef DatalogProgram_h
#define DatalogProgram_h

#include <vector>
#include "Predicate.h"
#include "Rule.h"
#include <stdio.h>

class DatalogProgram
{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
public:
    DatalogProgram(){}
    
    void insertFact(vector<Predicate> add);
    void insertScheme(vector<Predicate> add);
    void insertQueries(vector<Predicate> add);
    void insertRules(vector<Rule> add);
    
    string toString();
    
};
#endif /* DatalogProgram_h */
