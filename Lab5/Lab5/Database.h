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
#include "Graph.h"
#include <sstream>

class Database
{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    map<string, Relation> relations;
    
    Graph graph;

    
public:
    void build_graphs();
    //Database(){}
    Database(DatalogProgram dp);
    ~Database(){}
    
    stringstream output;
    
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
    void evalRules();
    void evalGraph();
    void evalRulesLoop();
    
    Relation getRelation(string rel_name);
    
    Relation dbPrjct(Relation r, int i);
    Relation rulePrjct(Relation r, vector<Parameter> params);
    Relation dbRname(Relation r, int i);
    Relation ruleRname(Relation r, vector<Parameter> params);
    Relation ruleSelect(Relation r, vector<Parameter> params);
    
    Relation projectHead(Relation r, int i);
    
    bool allVariables(int i);
    bool sameName(Rule r);
    
    void printVariables();
    void printVariables(map<string, int> mapVar);
    void print(char* file_name);
    
    vector<string> findVarValue(int i, int pos);
    
    int variablePos(vector<string> vars, string param);
    
    int getCorrespondingQuery(string name);
    
    int getSize();
    
    Relation dbJoin(vector<Relation> relations, Relation temp);
    
};

#endif /* Database_h */
