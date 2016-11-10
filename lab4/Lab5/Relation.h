//
//  Relation.h
//  lab2
//
//  Created by Austin Tebbs on 3/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Relation_h
#define Relation_h
#include "Scheme.h"
#include "Tuple.h"
#include <set>
#include <vector>
#include <string>

using namespace std;

#include <stdio.h>

class Relation
{
private:
    string name;
    
    
public:
    Relation(){}
    ~Relation(){}
    
    Scheme s;
    
    set<Tuple> tuples;
    void setName(string name);
    void setScheme(Scheme scheme);
    void addSchemeAttribute(string attrib);
    void addTuple(Tuple);
    Tuple atIndex(int i);
    void clear();
    string getName(){return name;}
    
    string toString();
    string tupleString();
    
    vector<string> matchTuple(string value, int pos);
    
    Relation select(int pos, string value);
    Relation select(int pos1, int pos2);
    Relation project(vector<int> pos);
    Relation rename(vector<string> names);
    Relation select(int pos, vector<string> values);
    Relation join(Relation r);
    
    Scheme makeScheme(Relation r);
    
    bool unique(string attribute);
    bool joinable(Scheme s1, Scheme s2, Tuple t1, Tuple t2);
    
    Tuple joinTuples(Scheme s1, Scheme s2, Tuple t1, Tuple t2);
    
    string performUnion(Relation& r);

    
    
};

#endif /* Relation_h */
