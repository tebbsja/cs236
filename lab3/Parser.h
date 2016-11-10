//
//  Parser.h
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Parser_h
#define Parser_h
#include <vector>
#include <string>
#include "DatalogProgram.h"
#include "Token.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"

#include <stdio.h>

class Parser
{
private:
    vector<Token> tokens;
    vector<Predicate> predicates;
    vector<Rule> rules;
    vector<string> domain;
    
    Rule myRule;
    Predicate myPred;
    Parameter myParam;
    
    DatalogProgram dp;
    
    int index;
    Token curr_token;
    string error_str;
    
    
public:
    
    Parser(vector<Token> token_list);
    
    void checkSyntax(string to_check);
    void parse();
    void scheme();
    void predicate();
    void parameter();
    void parameterList();
    void schemeList();
    void factList();
    void ruleList();
    void query();
    void queryList();
    void predicateList();
    void rule();
    void fact();
    
    void print();
    void print(char* file_name);
    
};

#endif /* Parser_h */
