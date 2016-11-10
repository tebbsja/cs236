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
#include <algorithm>

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
    for (unsigned int i=0; i < tuples.size(); i++)
    {
        ss << " ";
        for (unsigned int j=0; j <s.attributes.size(); j++)
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
        for (unsigned int i=0; i < values.size(); i++)
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
    
    for (unsigned int i=0; i < tuples.size();i++)
    {
        for (unsigned int j=0; j < s.attributes.size();j++)
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
    for (unsigned int i=0; i < tuples.size();i++ )
    {
        ss << " ";
        
        for (unsigned int j=0; j < s.attributes.size();j++)
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
    
    //sort(pos.begin(), pos.end());
    for (unsigned int i=0; i < pos.size();i++)
    {
        temp.s.attributes.push_back(s.attributes[pos[i]]);
    }
    
    for (Tuple t : tuples)
    {
        Tuple tmp;
        for (unsigned int i=0; i < pos.size(); i++)
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
    
    for (unsigned int i=0; i < names.size(); i++)
    {
        temp.s.attributes.push_back(names[i]);
    }
    
    return temp;
    
}

Relation Relation::join(Relation r)
{
    Relation temp;

    Scheme s1 = this->s;
    Scheme s2 = r.s;
    set<Tuple> tuples1 = tuples;
    set<Tuple> tuples2 = r.tuples;
    temp.s = this->s;
    temp.s = makeScheme(r);
    temp.setName("test");

    
    for (Tuple t1 : tuples1)
    {

        for (Tuple t2 : tuples2)
        {
            if (joinable(s1,s2,t1,t2))
            {
                temp.addTuple(joinTuples(s1, s2, t1, t2));
            }
        }
    }
    
    //cout << "returning: " << temp.toString() << endl;
    
    return temp;
}
Tuple Relation::joinTuples(Scheme s1, Scheme s2, Tuple t1, Tuple t2)
{
    Tuple temp = t1;


    for (unsigned int i=0; i < t2.size(); i++)
    {
        if (!count(s1.attributes.begin(), s1.attributes.end(), s2.attributes[i]))
        {
            temp.addTuple(t2[i]);
        }
        
    }
    
    
    return temp;
}

bool Relation::joinable(Scheme s1, Scheme s2, Tuple t1, Tuple t2)
{
    bool joinable = true;
    for (unsigned int i=0; i < s1.attributes.size(); i++)
    {
        for (unsigned int j=0; j < s2.attributes.size(); j++)
        {
            if (s1.attributes[i] == s2.attributes[j] && t1[i] != t2[j])
            {
                joinable = false;
            }
        }
    }
    return joinable;
}

bool Relation::unique(string attribute)
{
    bool unique = true;
    for (unsigned int i=0; i < s.attributes.size(); i++)
    {
        if (s.attributes[i] == attribute){
            unique = false;
        }
    }
    
    return unique;
}
Scheme Relation::makeScheme(Relation r)
{
    Scheme temp;
    
    for (unsigned int i=0; i < this->s.attributes.size(); i++)
    {
        temp.addAttribute(this->s.attributes[i]);
    }
    
    for (unsigned int i=0; i < this->s.attributes.size(); i++)
    {
        if (unique(r.s.attributes[i]))
        {
            temp.addAttribute(r.s.attributes[i]);
        }
    }

    return temp;
}

string Relation::performUnion(Relation& r)
{
    stringstream ss;
    
    for (Tuple t : r.tuples)
    {
        if (!this->tuples.count(t))
        {
            addTuple(t);
            ss << "\n ";
            
            for (unsigned int i =0; i < this->s.attributes.size(); i++)
            {
                ss << " " << this->s.attributes[i] << "=" << t.getTupleAtIndex(i);
            }
        }
    }
    
    
    ss << endl;
    
    return ss.str();
}
