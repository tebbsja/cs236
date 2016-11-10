//
//  Token.cpp
//  lab1
//
//  Created by Austin Tebbs on 1/19/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Token.h"

Token::Token(string token_type, string token_value, int line_num)
{
    this->token_type = token_type;
    this->token_value= token_value;
    this->line_num = line_num;
}

string Token::toString()
{
    return "(" + token_type + ",\"" + token_value + "\"," + to_string(line_num) + ")";
}