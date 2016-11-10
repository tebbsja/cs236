//
//  DatalogProgram.cpp
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "DatalogProgram.h"
#include <sstream>
#include <iostream>

void DatalogProgram::insertFact(vector<Predicate> add)
{
    facts = add;

}

void DatalogProgram::insertScheme(vector<Predicate> add)
{
    schemes = add;

}

void DatalogProgram::insertQueries(vector<Predicate> add)
{
    queries = add;

}
void DatalogProgram::insertRules(vector<Rule> add)
{
    rules = add;
    
}
string DatalogProgram::toString()
{
    stringstream ss;
    
    ss << "Schemes(" << schemes.size() << "):";
    for (int i=0; i < schemes.size(); i++)
    {
        ss << endl << "  " << schemes[i].toString();
    }
    ss << "\nFacts(" << facts.size() << "):";
    for (int i=0; i < facts.size(); i++)
    {
        ss << endl << "  " << facts[i].toString();
    }
    ss << "\nRules(" << rules.size() << "):";
    for (int i=0; i < rules.size(); i++)
    {
        ss << endl << "  " << rules[i].toString();
    }
    ss << "\nQueries(" << queries.size() << "):";
    for (int i=0; i < queries.size(); i++)
    {
        ss << endl << "  " << queries[i].toString();
    }
    
    return ss.str();
}