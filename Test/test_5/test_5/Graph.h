//
//  Graph.h
//  Project 5 - Graph Database
//
//  Created by Andy on 8/6/15.
//  Copyright (c) 2015 Andy Mockler. All rights reserved.
//

#ifndef __Project_5___Graph_Database__Graph__
#define __Project_5___Graph_Database__Graph__

#include <stdio.h>
#include <vector>
#include <map>

#include "Node.h"
#include "Rule.h"

class Graph {
public:
    Graph () {};
    Graph (std::vector<Rule> & rules);
    virtual ~Graph();
    
    std::vector<int> get_sort();
    
    std::string dependency_graph_to_string();
    std::string reverse_dependency_graph_to_string();
    std::string postorder_numbers_to_string();
    
    std::map<int, std::set<int>> get_sccs();
    
private:
    int postorder_number;
    std::vector<Rule> rules;
    
    std::map<int, Node> dependency_graph;
    std::map<int, Node> reverse_dependency_graph;
    
    std::map<int, std::set<int>> strongly_connected_components;
    
    void build_graphs();
    void add_dependencies(int rule_index);
    
    void dfs(int node_index);
    void dfs_forest();
    
    void find_scc();
    void scc_dfs(int index, std::set<int> & strongly_connected_component);
};

#endif /* defined(__Project_5___Graph_Database__Graph__) */
