//
//  Parameter.h
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Parameter_h
#define Parameter_h

#include <stdio.h>
#include <string>

using namespace std;

class Parameter
{
public:
    string name, value;
    
    Parameter(){}
    Parameter(string name, string value);
    ~Parameter(){}
    
    string getParam();
    
    bool isConstant(string to_test);
    
};

#endif /* Parameter_h */
