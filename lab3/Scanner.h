//
//  Scanner.h
//  lab1
//
//  Created by Austin Tebbs on 1/19/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Scanner_h
#define Scanner_h

#include "Token.h"
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class Scanner
{
private:
    vector<Token> tokens;
    
public:
    bool error = false;
    
    Scanner(){}
    ~Scanner(){}
    
    vector<Token> readFileToVector(char* file_name);
    void identifyStringToken(string token, int line_num);
    void print(char* file_name);
    int literalStringIdent(string line, int char_pos, int line_num);
    int dfltTest(int char_pos, string line, int line_num);
    bool isPronunciationMark(char curr_char);
    void simpleScan(char curr_char, int line_num);
    
    void errorToken(int line_num);
    int complexScan(char curr_char, string temp_line, int pos, int line_num);
    int Comment(string temp_line, int i);

    
};

#endif /* Scanner_h */
