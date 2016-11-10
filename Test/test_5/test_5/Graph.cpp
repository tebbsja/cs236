//
//  Graph.cpp
//  Project 5 - Graph Database
//
//  Created by Andy on 8/6/15.
//  Copyright (c) 2015 Andy Mockler. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "Graph.h"

using namespace std;

    int m = 0;

Graph::Graph(std::vector<Rule> & rules) {
    postorder_number = 1;
    this->rules = rules;
    
    this->build_graphs();
    this->dfs_forest();
    this->find_scc();
    

}

Graph::~Graph() {
    dependency_graph.clear();
    reverse_dependency_graph.clear();
    rules.clear();
    strongly_connected_components.clear();
}

std::string Graph::dependency_graph_to_string() {
    std::stringstream s;
    
    s << "\nDependency Graph";
    for ( auto item : dependency_graph ) {
        s << "\n  R" << item.first << ":";
        s << item.second.print_adjacent_nodes();
    }
    s << std::endl;
    
    return s.str();
}

std::string Graph::reverse_dependency_graph_to_string() {
    std::stringstream s;
    
    s << "\nReverse Graph";
    for ( auto item : reverse_dependency_graph ) {
        s << "\n  R" << item.first << ":";
        s << item.second.print_adjacent_nodes();
    }
    s << std::endl;
    
    return s.str();
}

std::string Graph::postorder_numbers_to_string() {
    std::stringstream s;
    
    s << "\nPostorder Numbers";
    for (auto item : reverse_dependency_graph) {
        s << "\n  R" << item.first << ": ";
        s << item.second.get_postorder_number();
    }
    s << std::endl;
    
    s << "\nSCC Search Order";
    std::vector<int> search_order = get_sort();
    for (auto index : search_order) {
        s << "\n  R" << index;
    }
    s << std::endl;
    
    return s.str();
}

void Graph::build_graphs() {
    // Insert nodes into the graphs for each rule
    unsigned long num_rules = rules.size();
    for (int i = 0; i < num_rules; i++) {
        Node d_node = Node();
        Node r_d_node = Node();
        dependency_graph.insert(std::pair<int, Node>(i, d_node));
        reverse_dependency_graph.insert(std::pair<int, Node>(i, r_d_node));
    }
    
    // Add dependencies (forward and reverse) for each rule
    int rule_index = 0;
    for (Rule rule : rules) {
        add_dependencies(rule_index);
        rule_index++;
    }
}

void Graph::add_dependencies(int rule_index) {
    Rule dependency_rule = rules.at(rule_index);

    

    
    int dependent_rule_index = 0;
    // Check every other rule for dependencies
    for (Rule dependent_rule : rules) {
        
        // Check them by comparing the name of the predicates with the rule you're working on
        for (Predicate predicate : dependent_rule.body) {
            
            // If you find the dependency rule in the predicate of the dependent rule,
            // add the dependency to the node.
            if ( dependency_rule.head.name == predicate.name ) {
                dependency_graph.at(dependent_rule_index).insert_adjacent_node(rule_index);
                reverse_dependency_graph.at(rule_index).insert_adjacent_node(dependent_rule_index);
                //cout << rule_index << " " << dependent_rule_index << endl;
            }
            
        }
        dependent_rule_index++;
    }
    

}

void Graph::dfs(int node_index) {
    
    
    Node & node = reverse_dependency_graph.at(node_index);
    node.mark_visited();
    
    std::set<int> adjancent_nodes = node.get_adjacent_nodes();
    for (auto index : adjancent_nodes) {
        if (!reverse_dependency_graph.at(index).get_visited()) {
            dfs(index);
        }
        
    }
    node.set_postorder_number(postorder_number);
    postorder_number++;
}

void Graph::dfs_forest() {
    for (auto item : reverse_dependency_graph) {
        if (!item.second.get_visited()) {
            dfs(item.first);
        }
    }
}

std::vector<int> Graph::get_sort() {
    std::vector<int> order;
    
    int pnum = postorder_number;
    for (int i = pnum; i > 0; i--) {
        for (auto item : reverse_dependency_graph) {
            if ( i == item.second.get_postorder_number() ) {
                order.push_back(item.first);
            }
        }
    }
    
    return order;
}

void Graph::find_scc() {
    std::vector<int> order = get_sort();
    
    int num_components = static_cast<int>(order.size());
    
    for (int i = 0; i < num_components; i++) {
        int node_index = order.at(i);
        std::set<int> strongly_connected_component;
        if (!dependency_graph.at(node_index).get_visited()) {
            scc_dfs(node_index, strongly_connected_component);
        }
        strongly_connected_components.insert(std::pair<int, std::set<int>>(node_index, strongly_connected_component));
    }
    
//    FOR TESTING STRONGLY CONNECTED COMPONENTS
//        OUTPUTS THE NODE NAME (e.g. R2) ALONG WITH ALL ASSOCIATED RULES
//
//    for (int i = 0; i < num_components; i++) {
//        int node_index = order.at(i);
//        std::cout << "\t\t\t\tR" << node_index;
//        std::set<int> scc = strongly_connected_components.at(node_index);
//        for (auto index : scc) {
//            std::cout << "  " << rules.at(index).to_string();
//        }
//        std::cout << std::endl;
//    }
    
}

void Graph::scc_dfs(int index, std::set<int> & strongly_connected_component) {
    Node & node = dependency_graph.at(index);
    node.mark_visited();
    std::set<int> adjacent_nodes = node.get_adjacent_nodes();
    
    for ( auto index : adjacent_nodes ) {
        if (!dependency_graph.at(index).get_visited()) {
            scc_dfs(index, strongly_connected_component);
        }
    }

    strongly_connected_component.insert(index);
}

std::map<int, std::set<int>> Graph::get_sccs() {
    return this->strongly_connected_components;
}























