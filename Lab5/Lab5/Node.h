//
//  Node.h
//  Lab5
//
//  Created by Austin Tebbs on 4/2/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <stdio.h>
#include <string>
#include <set>
#include "Rule.h"

using namespace std;

class Node
{
public:
    
    Node(Rule rule, int index);
    Node(){}
    
    string name;
    int index;
    Rule rule;
    void insert_adjacent_node(int i);
    set<int> adjacent_nodes;
    bool visited;
    void mark_as_visited();
    
    string adjacentNodesToString();
    
    void setPostOrder(int num);
    
    int postorder_num;
    
};

#endif /* Node_h */
