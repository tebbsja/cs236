#include <iostream>
#include <fstream>
#include "Scanner.h"
#include "Token.h"
#include "Parser.h"


using namespace std;


int main (int argc, char* argv[])
//int main()
{
    Scanner x;
    vector<Token> y;
    y = x.readFileToVector(argv[1]);
    //x.print(argv[2]);
    
    //Parser z(x.readFileToVector("/Users/Austin/Desktop/C++/cs236/lab2/lab2/in61.txt"));
    Parser z(y);
    //x.print();
    cout << endl;
    z.parse();
    z.print(argv[3]);
    
    //x.print();
    

    
    return 0;

}
