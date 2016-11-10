//
//  Parser.cpp
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//
#include <iostream>
#include "Parser.h"
#include <fstream>

using namespace std;

Parser::Parser(vector<Token> token_list)
{
    tokens = token_list;
    index = 0;
    curr_token = tokens[0];
    error_str = "";
}

void Parser::checkSyntax(string to_check)
{
    
    if (curr_token.token_type == to_check)
    {
        index++;
        curr_token = tokens[index];
        
    }
    else {
        throw curr_token;
    }
}
void Parser::parameter()
{
    if (curr_token.token_type == "STRING")
    {
        domain.push_back(curr_token.token_value);
        myParam = Parameter("", curr_token.token_value);
        checkSyntax("STRING");
    }
    else
    {
        
        myParam = Parameter(curr_token.token_value, "");
        checkSyntax("ID");
    }
    
    myPred.push_back(myParam);
}
void Parser::parameterList()
{
    
    if (curr_token.token_type == "COMMA")
    {
        checkSyntax("COMMA");
        parameter();
        parameterList();
    }
}
void Parser::predicate()
{
    myPred = Predicate(curr_token.token_value);
    checkSyntax("ID");
    checkSyntax("LEFT_PAREN");
    parameter();
    parameterList();
    checkSyntax("RIGHT_PAREN");
    predicates.push_back(myPred);
}
void Parser::predicateList(){
    
    if (curr_token.token_type == "COMMA")
    {
        checkSyntax("COMMA");
        predicate();
        predicateList();
    }
}
void Parser::scheme(){
    predicate();
}
void Parser::schemeList(){
    
    if (curr_token.token_type == "ID"){
        scheme();
        schemeList();
    }
}
void Parser::fact(){
    
    predicate();
    checkSyntax("PERIOD");
}
void Parser::factList(){
    
    if (curr_token.token_type == "ID"){
        fact();
        factList();
    }
}
void Parser::rule(){
    
    predicate();
    myRule = Rule(predicates[0]);
    predicates.clear();
    checkSyntax("COLON_DASH");
    predicate();
    predicateList();
    myRule.insertPreds(predicates);
    checkSyntax("PERIOD");
    rules.push_back(myRule);
    predicates.clear();
}
void Parser::ruleList(){
    
    if (curr_token.token_type == "ID"){
        rule();
        ruleList();
    }
}
void Parser::query(){
    
    predicate();
    checkSyntax("Q_MARK");
}
void Parser::queryList(){
    
    if (curr_token.token_type == "ID"){
        query();
        queryList();
    }
}
void Parser::parse()
{
    try
    {
        checkSyntax("SCHEMES");
        checkSyntax("COLON");
        scheme();
        schemeList();
        dp.insertScheme(predicates);
        predicates.clear();
        
        checkSyntax("FACTS");
        checkSyntax("COLON");
        factList();
        dp.insertFact(predicates);
        predicates.clear();
        
        checkSyntax("RULES");
        checkSyntax("COLON");
        ruleList();
        dp.insertRules(rules);
        predicates.clear();
        
        checkSyntax("QUERIES");
        checkSyntax("COLON");
        query();
        queryList();
        dp.insertQueries(predicates);
        predicates.clear();
        checkSyntax("EoF");
    }
    catch (Token bad_token)
    {
        error_str = "Failure!\n  " + bad_token.toString();
    }
}
void Parser::print()
{
    if (error_str == "")
    {
        vector<string> temp;
        cout << "Success!\n";
        cout << dp.toString();
        sort(domain.begin(), domain.end() );
        domain.erase(unique(domain.begin(), domain.end()), domain.end());
        cout << endl << "Domain(" << domain.size() << "):";
        for (int i=0; i < domain.size(); i++)
        {
            cout << endl << "  " << domain[i];
        }
    }
    else
    {
        cout << error_str;
    }
}
void Parser::print(char* file_name)
{
    ofstream output;
    output.open(file_name);
    
    if (error_str == "")
    {
        vector<string> temp;
        output << "Success!\n";
        output << dp.toString();
        sort(domain.begin(), domain.end() );
        domain.erase(unique(domain.begin(), domain.end()), domain.end());
        output << endl << "Domain(" << domain.size() << "):";
        for (int i=0; i < domain.size(); i++)
        {
            output << endl << "  " << domain[i];
        }
    }
    else
    {
        output << error_str;
    }
    output.close();
}
DatalogProgram Parser::getDP()
{
    return dp;
}
