//
//  Scheme.h
//  lab2
//
//  Created by Austin Tebbs on 3/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Scheme_h
#define Scheme_h

#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class Scheme
{
public:
    Scheme(){}
    ~Scheme(){}
    
    vector<string> attributes;
    void addAttribute(string value);
    void setValueAt(int i, string value);
};
#endif /* Scheme_h */
