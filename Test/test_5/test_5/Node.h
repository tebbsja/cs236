//
//  Node.h
//  Project 5 - Graph Database
//
//  Created by Andy on 8/6/15.
//  Copyright (c) 2015 Andy Mockler. All rights reserved.
//

#ifndef __Project_5___Graph_Database__Node__
#define __Project_5___Graph_Database__Node__

#include <stdio.h>
#include <set>

class Node {
public:
    Node();
    virtual ~Node();
    
    void insert_adjacent_node(int rule_index);
    std::string print_adjacent_nodes();
    void mark_visited();
    void set_postorder_number(int num);
    std::set<int> get_adjacent_nodes();
    bool get_visited();
    int get_postorder_number();

private:
    bool visited;
    
    // Postorder number that it can be assigned. This will act as the name or identifier for the node
    int postorder_number;
   
    // Some way of keeping track of adjacent nodes; All you really need is the node name, or just the number. Make your life easy and store JUST THE NUMBER.
    std::set<int> adjacent_nodes;
};

#endif /* defined(__Project_5___Graph_Database__Node__) */