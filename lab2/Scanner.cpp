//
//  Scanner.cpp
//  lab1
//
//  Created by Austin Tebbs on 1/19/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Scanner.h"
#include "Token.h"
#include <fstream>
#include <iostream>

void Scanner::identifyStringToken(string token, int line_num)
{

    if (token == "Queries"){
        Token temp = Token("QUERIES", token, line_num);
        tokens.push_back(temp);
    }
    else if (token == "Schemes"){
        Token temp = Token("SCHEMES", token, line_num);
        tokens.push_back(temp);
    }
    else if (token == "Facts"){
        Token temp = Token("FACTS", token, line_num);
        tokens.push_back(temp);
    }
    else if (token == "Rules"){
        Token temp = Token("RULES", token, line_num);
        tokens.push_back(temp);
    }
    else {
        Token temp = Token("ID", token, line_num);
        tokens.push_back(temp);
    }

}

int Scanner::literalStringIdent(string temp_line, int char_pos, int line_num)
{
    char curr_char = '0';
    string temp_string = "";
    int i =0;
        
        i = char_pos;
    
        curr_char = temp_line[i];
        
        temp_string += '\'';
        i++;
        
        while (temp_line[i] != '\'')
        {
            temp_string += temp_line[i];
            i++;
        }
        
        temp_string += temp_line[i];
    
        Token temp = Token("STRING", temp_string, line_num);
        tokens.push_back(temp);
        return i;
    
}

int Scanner::dfltTest(int pos, string temp_line, int line_num)
{
    char curr_char='0';
    int i = 0;
    string temp_string = "";
    i=pos;
    
    curr_char = temp_line[i];
        
    while (isalnum(temp_line[i]))
    {
        temp_string += curr_char;
        
        i++;
        curr_char = temp_line[i];
    }
    
    identifyStringToken(temp_string, line_num);
    i--;
    
    return i;

}

bool Scanner::isPronunciationMark(char curr_char)
{
    if (curr_char == ',' || curr_char == '.' || curr_char == '?' || curr_char == '(' || curr_char == ')')
    {
        return true;
    }
    
    return false;
    
}

void Scanner::simpleScan(char curr_char, int line_num)
{
    switch (curr_char)
    {
        case ',':
        {
            Token temp = Token("COMMA", ",", line_num);
            tokens.push_back(temp);
            break;
        }
        case '.':
        {
            Token temp = Token("PERIOD", ".", line_num);
            tokens.push_back(temp);
            break;
        }
        case '?':
        {
            Token temp = Token("Q_MARK", "?", line_num);
            tokens.push_back(temp);
            break;
        }
        case '(':
        {
            Token temp = Token("LEFT_PAREN", "(", line_num);
            tokens.push_back(temp);
            break;
        }
        case ')':
        {
            Token temp = Token("RIGHT_PAREN", ")", line_num);
            tokens.push_back(temp);
            break;
        }
    }
}

int Scanner::Comment(string temp_line, int i)
{
    while (temp_line[i] != '\n')
    {
        i++;
    }
    return i;
}

int Scanner::complexScan(char curr_char, string temp_line, int pos, int line_num)
{
    int i = 0;
    i = pos;
    
    switch (curr_char)
    {
        case '\'':
        {
            
            bool unterminating = true;
            string temp_string = "";
            
            for (int j=1; j < temp_line.size(); j++)
            {
                if (temp_line[j] == '\'')
                {
                    unterminating = false;
                }
            }
            
            if (unterminating)
            {
                errorToken(line_num);
            }
            else
            {
                i = literalStringIdent(temp_line, i, line_num);
            }
            
            break;
        }//colon dash
        case ':':
        {
            
            if(temp_line[i+1] == '-')
            {
                Token temp = Token("COLON_DASH", ":-", line_num);
                tokens.push_back(temp);
                i++;
                break;
            }
            else
            {
                Token temp = Token("COLON", ":", line_num);
                tokens.push_back(temp);
                break;
            }
        }
        case '#':
        {
            temp_line += '\n';
            i = Comment(temp_line, i);
            break;
        }
        default:
        {
            if (isalpha(curr_char))
            {
                i = dfltTest(i, temp_line, line_num);
            }
            else if(isspace(curr_char)){
                //do nothing
            }
            else
            {
                errorToken(line_num);
            }
            break;
        }
            
    }
  
    return i;
}

void Scanner::errorToken(int line_num)
{
    Token temp = Token("ERROR", "e", line_num);
    tokens.push_back(temp);
}

vector<Token> Scanner::readFileToVector(string file_name)
{
    char curr_char = '0';
    
    string temp_line = "";
    string read = "";
    int line_num = 0;
    
    ifstream my_file;
    my_file.open(file_name);
    
    if (my_file.fail() || my_file.bad())
    {
        cout << "CANNOT OPEN " << file_name << endl;
        errorToken(line_num);
        my_file.close();
    }
    
    else
    {
        while (!my_file.eof())
        {
            getline(my_file,temp_line);
            line_num++;
            
            for (int i=0; i < temp_line.size(); i++)
            {
                curr_char = temp_line[i];
                
                if (isPronunciationMark(curr_char))
                {
                    simpleScan(curr_char, line_num);
                }
                
                else
                {
                    i = complexScan(curr_char, temp_line, i, line_num);
                }
            }
            
        }
    }
    
    Token temp = Token("EoF", "", line_num);
    tokens.push_back(temp);
    my_file.close();
    
    return tokens;
    
}

vector<Token> Scanner::readFileToVector(char* file_name)
{
    char curr_char = '0';
    
    string temp_line = "";
    string read = "";
    int line_num = 0;
    
    ifstream my_file;
    my_file.open(file_name);
    
    if (my_file.fail() || my_file.bad())
    {
        cout << "CANNOT OPEN " << file_name << endl;
        errorToken(line_num);
        my_file.close();
    }
    
    else
    {
        while (!my_file.eof())
        {
           getline(my_file,temp_line);
            line_num++;

            for (int i=0; i < temp_line.size(); i++)
            {
                curr_char = temp_line[i];
                
                if (isPronunciationMark(curr_char))
                {
                    simpleScan(curr_char, line_num);
                }
                
                else
                {
                    i = complexScan(curr_char, temp_line, i, line_num);
                }
            }
            
        }
    }
    
    Token temp = Token("EoF", "", line_num);
    tokens.push_back(temp);
    my_file.close();
    
    return tokens;
    
}

void Scanner::print()
{

    for (int i=0; i < tokens.size(); i++)
    {
        if (tokens[i].token_type != "ERROR" && !error)
        {
            cout << tokens[i].toString() << endl;
            
        }
        else
        {
            error = true;
            cout << "Input Error on line " << tokens[i].line_num << endl;
            
            break;
        }
    }
    if (!error)
    {
        cout << "Total Tokens = " << tokens.size() << endl;
    }

    
    
}

void Scanner::print(char* file_name)
{
    ofstream output;
    output.open(file_name);
    for (int i=0; i < tokens.size(); i++)
    {
        if (tokens[i].token_type != "ERROR" && !error)
        {
            output << tokens[i].toString() << endl;
            
        }
        else
        {
            error = true;
            output << "Input Error on line " << tokens[i].line_num << endl;
            output.close();
            break;
        }
    }
    if (!error)
    {
        output << "Total Tokens = " << tokens.size() << endl;
    }
    output.close();

    
}


