//
//  Graph.h
//  Lab5
//
//  Created by Austin Tebbs on 4/2/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include "Node.h"
#include "Rule.h"
#include <map>
#include <set>
#include <vector>


using namespace std;

class Graph
{
public:
    Graph(){}
    Graph(vector<Rule> rules);
    map<int, Node> dependency_graph;
    map<int, Node> reverse_dependency_graph;
    map<int, set<int>> SCCs;
    void checkForDependency(Rule rule, int i);
    
    void DFS_Forest();
    void DFS(int i, set<int>& SCC_set);
    void findSCC();
    void getSearchOrder(vector<int>& order);
    
    string dependencyGraphToString();
    string reverseGraphToString();
    string postOrderToString();
    string sccSearchOrder();
    
    int cur_postorder;
    
private:
    
    vector<Rule> rules;
    bool scc;
    
    
};

#endif /* Graph_h */
