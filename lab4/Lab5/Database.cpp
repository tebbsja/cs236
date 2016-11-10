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

    createRelations();
    output += "Scheme Evaluation\n\n";
    output += "Fact Evaluation\n\n";
    print();
    output += "Rule Evaluation\n\n";
    evalRules();
    print();
    evalQueries();
}
int Database::getSize()
{
    
    int tuple_count = 0;
    
    for (auto rel : relations)
    {
        tuple_count += rel.second.tuples.size();
    }
    return tuple_count;
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
    
    for (unsigned int i=0; i < schemes.size(); i++)
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
    for (unsigned int i=0; i < facts.size(); i++)
    {
        addTuples(i);
    }
}
void Database::addTuples(int i)
{
    Tuple t;
    
    for (unsigned int j=0; j < facts[i].parameters.size(); j++)
    {
        t.push_back(facts[i].parameters[j].value);
    }
    
    relations[facts[i].name].tuples.insert(t);
}

void Database::addRelationScheme(Relation& r, int i)
{
    for (unsigned int j=0; j < schemes[i].parameters.size(); j++)
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
    
    for (unsigned int j=0; j < queries[i].parameters.size(); j++)
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
    
    for (unsigned int i=0; i < queries.size(); i++)
    {
            temp = getRelation(queries[i].name);
            
            
            for (unsigned int j=0; j < queries[i].parameters.size();j++)
            {
                string param = "";
                param = queries[i].parameters[j].getParam();
                
                if (queries[i].parameters[j].isConstant(param))
                {
                    temp = temp.select(j, param);
                }
                else // variables
                {

                    if (variables.count(param) > 0)
                    {
                        temp = temp.select(j, variables[param]);
                    }
                    variables.insert(pair<string, int>(param, j));
                    
                }
            }
        
    printEvaluation(i, temp);
	variables.clear();
        
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


void Database::evalRules()
{
    bool change = true;
    stringstream ss;
    int start, total;
    total = 0;
    
    while(change)
    {
        change = false;
        total++;
        start = getSize();
        
        for (unsigned int i=0; i < rules.size(); i++)
        {
            vector<Relation> temp_relations;
            Relation r;
            
            for (unsigned int j=0; j < rules[i].getPredicates().size(); j++)
            {
              
                Relation temp = relations[rules[i].getPredicates()[j].name];
                
                temp = ruleSelect(temp, rules[i].getPredicates()[j].parameters);
                temp = rulePrjct(temp, rules[i].getPredicates()[j].parameters);
                temp = ruleRname(temp, rules[i].getPredicates()[j].parameters);
                
                
                temp_relations.push_back(temp);
                
                
            }
            
            r = temp_relations[0];
            if (temp_relations.size() > 1)
            {
                for (unsigned int k = 1; k < temp_relations.size(); k++)
                {
                    r = r.join(temp_relations[k]);
                }
            }
          

            r = projectHead(r, i);
            r = ruleRname(r, rules[i].getName().parameters);
            
            output += rules[i].toString();
            
            output += relations[rules[i].getName().name].performUnion(r);
        
           
        }
        if ((getSize() - start) > 0)
        {
            change = true;
        }

    }
    
    output += "\nConverged after ";
    ss << total;
    output += ss.str();
    output += " passes through the Rules.\n\n";
    

    
}

Relation Database::projectHead(Relation r, int i)
{
    vector<int> pos;
 
    for (unsigned int j=0; j < rules[i].getName().parameters.size(); j++)
    {
        for (unsigned int k=0; k < r.s.attributes.size(); k++)
        {
            if (rules[i].getName().parameters[j].getParam() == r.s.attributes[k])
            {
                pos.push_back(k);
            }
        }
    }
    r = r.project(pos);

    return r;
}

Relation Database::dbJoin(vector<Relation> relations, Relation temp)
{
    while (!relations.empty())
    {
        for (unsigned int i=1; i < relations.size(); i++)
        {
            temp = temp.join(relations[i]);
        }
    }
    
    return temp;
}

Relation Database::ruleRname(Relation r, vector<Parameter> params)
{
    Relation temp;
    vector<string> variables;
    
    for (unsigned int i=0; i < params.size();i++)
    {
        bool duplicate = false;
        bool constant = params[i].isConstant(params[i].getParam());
        
        for (unsigned int l=0; l < variables.size(); l++)
        {
            if(variables[l] == params[i].getParam())
            {
                duplicate = true;
            }
        }
        
        if (!constant && !duplicate)
        {
            variables.push_back(params[i].getParam());
        }
    }
    
    temp = r.rename(variables);
    
    
    return temp;
}

Relation Database::rulePrjct(Relation r, vector<Parameter> params)
{
    Relation temp;
    vector<int> pos_list;
    vector<string> variables;


    
    for (unsigned int i=0; i < params.size();i++)
    {
        bool duplicate = false;
        bool constant = params[i].isConstant(params[i].getParam());
        for (int j=0; j < variables.size();j++)
        {
            if (variables[j] == params[i].getParam())
            {
                duplicate = true;
            }
        }
        
        if (!constant && !duplicate)
        {
            pos_list.push_back(i);
            variables.push_back(params[i].getParam());
        }
    }
    
    
    temp = r.project(pos_list);
    
    return temp;
}
int Database::getCorrespondingQuery(string name)
{
    int temp = 0;
    for (unsigned int i=0; i < queries.size(); i++)
    {
        if (queries[i].name == name)
        {
            temp = i;
        }
    }
    return temp;
}

Relation Database::ruleSelect(Relation r, vector<Parameter> params)
{
    vector<string> variables;
    
    for (unsigned int i=0; i < params.size();i++)
    {
        Parameter p = params[i];
        
        if (p.isConstant(p.getParam()))
        {
            r = r.select(i, p.getParam());
        }
        else
        {
            bool duplicate = false;
            int index1 = 0;
            
            for (unsigned int j =0; j < variables.size(); j++)
            {
                if (variables[j] == p.getParam())
                {
                    duplicate = true;
                    index1 = j;
                }
            }
            
            if (duplicate)
            {
                r = r.select(index1,i);
            }
            else
            {
                variables.push_back(p.getParam());
            }
        }
    }
    
    return r;
}

void Database::print()
{
    typedef map<string, Relation>::iterator it;
    for (it iterator = relations.begin(); iterator != relations.end(); iterator++)
    {
        output += iterator->second.toString();// + endl;
        output += "\n";
    }
    

    
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
    
    for (unsigned int j=0; j < queries[i].parameters.size();j++)
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
        
        for (unsigned int k=0; k < variables.size(); k++)
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
    for (unsigned int j=0; j < queries[i].parameters.size(); j++)
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
    for (unsigned int i=0; i < vars.size(); i++)
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
    
    for (unsigned int j=0; j < queries[i].parameters.size();j++)
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
        
        for (unsigned int k=0; k < variables.size(); k++)
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
    for (unsigned int i=0; i < paramVariables.size();i++)
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
