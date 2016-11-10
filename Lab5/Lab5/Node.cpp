//
//  Node.cpp
//  Lab5
//
//  Created by Austin Tebbs on 4/2/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Node.h"
#include <iostream>
#include <sstream>


Node::Node(Rule rule, int index)
{
    this->name = rule.getName().name;
    this->index = index;
    this->rule = rule;
    this->visited = false;
    this->postorder_num = 0;
}

void Node::insert_adjacent_node(int index)
{
    adjacent_nodes.insert(index);
}

void Node::mark_as_visited()
{
    this->visited = true;
}

void Node::setPostOrder(int num)
{
    this->postorder_num = num;
}

string Node::adjacentNodesToString()
{
    stringstream ss;
    for (auto node : adjacent_nodes)
    {
        ss << "R" << node << " ";
    }
    return ss.str();
}