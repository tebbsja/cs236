//
//  Token.h
//  lab1
//
//  Created by Austin Tebbs on 1/19/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Token_h
#define Token_h


#include <vector>
#include <string>

#include <stdio.h>


using namespace std;

class Token
{
private:
    
    
public:
    string token_type = "";
    string token_value = "";
    int line_num = 0;
    
    Token(){}
    Token(string token_type, string token_value, int line_num);
    ~Token(){}
    
    string toString();
    
};

#endif /* Token_h */
