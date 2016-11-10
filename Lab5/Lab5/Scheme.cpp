//
//  Scheme.cpp
//  lab2
//
//  Created by Austin Tebbs on 3/8/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Scheme.h"
#include <iostream>

using namespace std;

void Scheme::addAttribute(string value)
{
    attributes.push_back(value);
}

void Scheme::setValueAt(int i, string value)
{
    attributes.at(i) = value;
}
