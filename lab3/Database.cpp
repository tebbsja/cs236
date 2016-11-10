//
//  Database.cpp
//  lab2
//
//  Created by Austin Tebbs on 3/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Database.h"
#include <iostream>
#include <sstream>
#include <fstream>

Database::Database(DatalogProgram dp)
{
    this->dp = dp;
    schemes = dp.getSchemes();
    queries = dp.getQueries();
    facts = dp.getFacts();
    rules = dp.getRules();
}

vector<Predicate> Database::getSchemes()
{
    return schemes;
}
vector<Predicate> Database::getFacts()
{
    return facts;
}
vector<Predicate> Database::getQueries()
{
    return queries;
}
vector<Rule> Database::getRules()
{
    return rules;
}
void Database::createRelations()
{
    Relation temp;
    
    for (int i=0; i < schemes.size(); i++)
    {
        temp.setName(schemes[i].name);
        addRelationScheme(temp, i);
        relations.insert(pair<string, Relation>(temp.getName(),temp));
        temp.clear();
    }
    parseFacts();
}
void Database::parseFacts()
{
    for (int i=0; i < facts.size(); i++)
    {
        addTuples(i);
    }
}
void Database::addTuples(int i)
{
    Tuple t;
    
    for (int j=0; j < facts[i].parameters.size(); j++)
    {
        t.push_back(facts[i].parameters[j].value);
    }
    
    relations[facts[i].name].tuples.insert(t);
}

void Database::addRelationScheme(Relation& r, int i)
{
    for (int j=0; j < schemes[i].parameters.size(); j++)
    {
        r.addSchemeAttribute(schemes[i].parameters[j].name);
    }
}
void Database::printVariables(map<string, int> mapVar)
{
    typedef map<string, int>::iterator it;

    for (it iterator = mapVar.begin(); iterator != mapVar.end(); iterator++)
    {
        cout << iterator->first << " ";
    }
}
vector<string> Database::findVarValue(int i, int pos)
{
    vector<string> value;
    string constant = "";
    string param = "";
    
    for (int j=0; j < queries[i].parameters.size(); j++)
    {
        
        if (queries[i].parameters[j].name == "")
        {
            param = queries[i].parameters[j].value;
        }
        else
        {
            param = queries[i].parameters[j].name;
        }
        if (queries[i].parameters[j].isConstant(param))
        {
            constant = param;
        }
    }

    Relation temp;
    temp = getRelation(queries[i].name);
    value = temp.matchTuple(constant, pos);

    return value;
}
void Database::evalQueries()
{
    output += "Query Evaluation\n\n";
    
    Relation temp;
    map<string, int> variables;
    map<string, vector<string>> variable_values;
    
    for (int i=0; i < queries.size(); i++)
    {
            temp = getRelation(queries[i].name);
            
            
            for (int j=0; j < queries[i].parameters.size();j++)
            {
                string param = "";
                param = queries[i].parameters[j].getParam();
                
                if (queries[i].parameters[j].isConstant(param))
                {
                    temp = temp.select(j, param);
                }
                else // variables
                {
                    
                    if (queries[i].hasConstant())
                    {
                        variable_values.insert(pair<string,vector<string>>(param, findVarValue(i, j)));
                    }
                    if (variable_values.count(param) > 0)
                    {
                        
                        if (variable_values[param].size() == 1)
                        {
                            temp = temp.select(j,variable_values[param][0]);
                        }
                        else
                        {
                            temp = temp.select(j,variable_values[param]);
                        }

                    }
                    else if (variables.count(param) > 0)
                    {
                        temp = temp.select(j, variables[param]);
                    }
                    variables.insert(pair<string, int>(param, j));
                    
                }
            }
        
        printEvaluation(i, temp);
        
    }
    
}

void Database::printEvaluation(int i, Relation temp)
{
    stringstream ss;
    
    ss << queries[i].toString() << "? ";
    if (temp.tuples.size() > 0)
    {
        ss << "Yes(" << temp.tuples.size() << ")" << endl;
        temp.setName("select");
        ss << temp.toString();
        temp = dbPrjct(temp, i);
        temp.setName("project");
        ss << temp.toString();
        temp = dbRname(temp, i);
        temp.setName("rename");
        ss << temp.toString() << endl;
    }
    else
    {
        ss << "No\n\n";
    }
    
    output += ss.str();
}

void Database::print()
{
    typedef map<string, Relation>::iterator it;
    output += "Scheme Evaluation\n\n";
    output += "Fact Evaluation\n\n";
    for (it iterator = relations.begin(); iterator != relations.end(); iterator++)
    {
        output += iterator->second.toString();// + endl;
        output += "\n";
    }
    
    evalQueries();
    
}

Relation Database::getRelation(string rel_name)
{
    Relation temp;
    
    typedef map<string, Relation>::iterator it;
    
    for (it iterator = relations.begin(); iterator != relations.end(); iterator++)
    {
        if (iterator->first == rel_name)
        {
            temp = iterator->second;
        }
       
    }
    
    return temp;
}

Relation Database::dbPrjct(Relation r, int i)
{
    Relation temp;
    vector<int> pos_list;
    vector<string> variables;
    bool constant;
    string param = "";
    
    for (int j=0; j < queries[i].parameters.size();j++)
    {
        bool duplicate = false;
        
        if (queries[i].parameters[j].name == "")
        {
            param = queries[i].parameters[j].value;
        }
        else
        {
            param = queries[i].parameters[j].name;
        }
        constant = queries[i].parameters[j].isConstant(param);
        
        for (int k=0; k < variables.size(); k++)
        {
            if(variables[k] == param)
            {
                duplicate = true;
            }
        }
        
        if (!constant && !duplicate)
        {
            pos_list.push_back(j);
            variables.push_back(param);
        }
    }
    
    temp = r.project(pos_list);
    

    
    return temp;
}

bool Database::allVariables(int i)
{
    bool bothVariables = true;
    for (int j=0; j < queries[i].parameters.size(); j++)
    {
        string param = "";
        if (queries[i].parameters[j].name == "")
        {
            param  = queries[i].parameters[j].value;
        }
        else
        {
            param = queries[i].parameters[j].name;
        }
        
        if(queries[i].parameters[j].isConstant(param))
        {
            bothVariables = false;
        }
           
    }
    
    return bothVariables;
}
int Database::variablePos(vector<string> vars, string param)
{
    int index = 0;
    for (int i=0; i < vars.size(); i++)
    {
        if (vars[i] == param)
        {
            index = i;
        }
    }
    
    return index;
}

Relation Database::dbRname(Relation r, int i)
{
    Relation temp;
    vector<string> variables;
    bool constant;
    string param = "";
    
    for (int j=0; j < queries[i].parameters.size();j++)
    {
        bool duplicate = false;
        
        if (queries[i].parameters[j].name == "")
        {
            param = queries[i].parameters[j].value;
        }
        else
        {
            param = queries[i].parameters[j].name;
        }
        constant = queries[i].parameters[j].isConstant(param);
        
        for (int k=0; k < variables.size(); k++)
        {
            if(variables[k] == param)
            {
                duplicate = true;
            }
        }
        
        if (!constant && !duplicate)
        {
            variables.push_back(param);
        }
    }
    
    temp = r.rename(variables);
    

    return temp;
}
void Database::printVariables()
{
    cout << "Variables: ";
    for (int i=0; i < paramVariables.size();i++)
    {
        cout << paramVariables[i] << " ";
    }
    cout << endl;
}
void Database::print(char *file_name)
{
    ofstream out;
    out.open(file_name);
    out << output;
    out.close();
}
