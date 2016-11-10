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
    //x.print(argv[2]);
    
    Parser z(x.readFileToVector("/Users/Austin/Desktop/C++/cs236/lab3/lab3/lab3/in61.txt"));
    //Parser z(y);
    //x.print();
    z.parse();
    //z.print(argv[3]);
    
    //cout << z.getDP().toString();
    //z.print();
    Database q(z.getDP());
    
    q.createRelations();
    
    q.print();
    
    cout << q.output;
    //q.print(argv[2]);
    
    
    
    return 0;
    
}
