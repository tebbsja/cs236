//
//  Relation.cpp
//  lab2
//
//  Created by Austin Tebbs on 3/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Relation.h"
#include <sstream>
#include <iostream>

void Relation::setName(string name)
{
    this->name = name;
}

void Relation::setScheme(Scheme scheme)
{
    s = scheme;
}

void Relation::addSchemeAttribute(string attribute)
{
    s.addAttribute(attribute);
}

string Relation::tupleString()
{
    stringstream ss;
    for (int i=0; i < tuples.size(); i++)
    {
        ss << " ";
        for (int j=0; j <s.attributes.size(); j++)
        {
            ss << " " << s.attributes[j] << "=" << atIndex(i).getTupleAtIndex(j);
        }
        
        ss << endl;
    }
    
    return ss.str();
}
Relation Relation::select(int pos, vector<string> values)
{
    Relation temp;
    temp.setName(this->name);
    temp.setScheme(this->s);
    
    for (auto t : tuples)
    {
        for (int i=0; i < values.size(); i++)
        {
            if (t[pos] == values[i])
            {
                temp.tuples.insert(t);
            }
        }
    }
    
    return temp;
}

vector<string> Relation::matchTuple(string value, int pos)
{
    vector<string> ret_vect;
    Tuple tempTuple;
    
    for (int i=0; i < tuples.size();i++)
    {
        for (int j=0; j < s.attributes.size();j++)
        {
            if (atIndex(i).getTupleAtIndex(j) == value)
            {
                ret_vect.push_back(atIndex(i).getTupleAtIndex(pos));
            }
        }
    }

    return ret_vect;
}

string Relation::toString()
{
    stringstream ss;
    
    ss << name << endl;
    if (s.attributes.size() == 0)
    {
        return ss.str(); 
    }
    for (int i=0; i < tuples.size();i++ )
    {
        ss << " ";
        
        for (int j=0; j < s.attributes.size();j++)
        {
            ss << " " << s.attributes[j] << "=" << atIndex(i).getTupleAtIndex(j);
        }
        
        ss << endl;
    }
    
    return ss.str();
}
Tuple Relation::atIndex(int i)
{
    return *next(tuples.begin(), i);
}
void Relation::clear()
{
    name = "";
    tuples.clear();
    s.attributes.clear();
    
}
void Relation::addTuple(Tuple t)
{
    tuples.insert(t);
}

Relation Relation::select(int pos, string value)
{
    Relation temp;
    temp.setName(this->name);
    temp.setScheme(this->s);
    
    for (auto t : tuples)
    {
        if (t[pos] == value)
        {
            temp.tuples.insert(t);
        }
    }
    
    return temp;
    
}
Relation Relation::select(int pos1, int pos2)
{
    Relation temp;
    temp.setName(this->name);
    temp.setScheme(this->s);
    for (auto t : tuples)
    {
        if (t[pos1] == t[pos2])
        {
            temp.tuples.insert(t);
        }
    }
    
    return temp;
    
}

Relation Relation::project(vector<int> pos)
{
    Relation temp;
    temp.setName(name);
    
    for (int i=0; i < pos.size();i++)
    {
        temp.s.attributes.push_back(s.attributes[pos[i]]);
    }
    
    for (Tuple t : tuples)
    {
        Tuple tmp;
        for (int i=0; i < pos.size(); i++)
        {
            tmp.push_back(t[pos[i]]);
        }
        temp.tuples.insert(tmp);
    }
    
    return temp;
}

Relation Relation::rename(vector<string> names)
{
    Relation temp;
    temp.setName(name);
    temp.tuples = tuples;
    
    for (int i=0; i < names.size(); i++)
    {
        temp.s.attributes.push_back(names[i]);
    }
    
    return temp;
    
}