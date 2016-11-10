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
    
    //q.createRelations();
    
    //q.print();
    
    cout << q.output;
    
    Relation f;
    Relation g;
    
    //cout << f.tupleString() << endl;
    //cout << g.toString() << endl;
    
    //Scheme s = f.makeScheme(g);
    
    /*for (int i=0; i < s.attributes.size(); i++)
    {
        cout << s.attributes[i] << " ";
    }*/
    
    //q.evalRules();
    
    //q.print(argv[2]);
    
    
    

    
    
    return 0;
    
}
