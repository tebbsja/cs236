//
//  main.cpp
//  Lab5
//
//  Created by Austin Tebbs on 4/2/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Scanner.h"
#include "Token.h"
#include "Parser.h"
#include "Database.h"


using namespace std;


//int main (int argc, char* argv[])
int main()
{
    
    Scanner x;
    vector<Token> y;
    //y = x.readFileToVector(argv[1]);
    
    
    Parser z(x.readFileToVector("/Users/Austin/Desktop/C++/cs236/lab5/lab5/in61.txt"));
    
    
    //Parser z(y);
    z.parse();
    
    
    
    Database q(z.getDP());
    
    
    
    
   // q.print(argv[2]);
    
    cout << q.output.str();
    
    
    
    return 0;
    
}
