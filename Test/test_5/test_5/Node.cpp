//
//  Node.cpp
//  Project 5 - Graph Database
//
//  Created by Andy on 8/6/15.
//  Copyright (c) 2015 Andy Mockler. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "Node.h"

Node::Node() {
    visited = false;
    postorder_number = -1;
}

Node::~Node() {
    adjacent_nodes.clear();
}

void Node::insert_adjacent_node(int rule_index) {
    adjacent_nodes.insert(rule_index);
}

std::string Node::print_adjacent_nodes() {
    std::stringstream s;
    for ( auto node : adjacent_nodes ) {
        s << " R" << node;
    }
    return s.str();
}

void Node::mark_visited() {
    this->visited = true;
}

void Node::set_postorder_number(int num) {
    this->postorder_number = num;
}

std::set<int> Node::get_adjacent_nodes() {
    return this->adjacent_nodes;
}

bool Node::get_visited() {
    return this->visited;
}

int Node::get_postorder_number() {
    return this->postorder_number;
}