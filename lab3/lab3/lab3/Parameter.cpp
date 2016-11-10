//
//  Parameter.cpp
//  lab2
//
//  Created by Austin Tebbs on 2/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Parameter.h"

Parameter::Parameter(string namex, string valuex)
{
    name = namex;
    value = valuex;
}
bool Parameter::isConstant(string to_test)
{
    if (to_test[0] == '\'')
    {
        return true;
    }
    
    return false;
}

string Parameter::getParam()
{
    if (name == "")
    {
        return value;
    }
    else{
        return name;
    }
}