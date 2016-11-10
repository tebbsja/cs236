#include <iostream>
#include <fstream>
#include "Scanner.h"
#include "Token.h"
#include "Parser.h"


using namespace std;


int main (int argc, char* argv[])
{
    Scanner x;
    vector<Token> y;
    y = x.readFileToVector(argv[1]);
    
    Parser z(y);
    z.parse();
    z.print(argv[2]);
        
    return 0;

}
