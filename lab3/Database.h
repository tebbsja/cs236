//
//  Database.h
//  lab2
//
//  Created by Austin Tebbs on 3/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Database_h
#define Database_h

#include <stdio.h>
#include "DatalogProgram.h"
#include "Relation.h"
#include <map>
#include "Tuple.h"

class Database
{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    map<string, Relation> relations;
    
public:
    Database(){}
    Database(DatalogProgram dp);
    ~Database(){}
    
    string output = "";
    
    vector<Predicate> getSchemes();
    vector<Predicate> getFacts();
    vector<Predicate> getQueries();
    vector<Rule> getRules();
    vector<string> paramVariables;
    
    DatalogProgram dp;
    
    void createRelations();
    void addRelationScheme(Relation& r, int i);
    void print();
    void addTuples(int i);
    void setTuples(Tuple& t, int i);
    void parseFacts();
    void evalQueries();
    void printEvaluation(int i, Relation temp);
    
    Relation getRelation(string rel_name);
    
    Relation dbPrjct(Relation r, int i);
    Relation dbRname(Relation r, int i);
    bool allVariables(int i);
    
    void printVariables();
    void printVariables(map<string, int> mapVar);
    void print(char* file_name);
    
    vector<string> findVarValue(int i, int pos);
    
    int variablePos(vector<string> vars, string param);
    
};

#endif /* Database_h */
