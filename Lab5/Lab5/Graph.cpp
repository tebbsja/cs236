//
//  Graph.c
//  Lab5
//
//  Created by Austin Tebbs on 4/2/16.
//  Copyright © 2016 Austin Tebbs. All rights reserved.
//

#include "Graph.h"
#include <iostream>
#include <sstream>




Graph::Graph(vector<Rule> rule)
{
    this->rules = rule;
    this->scc = false;
    for (unsigned int i=0; i < rule.size(); i++)
    {
        dependency_graph.insert(pair<int, Node>(i, Node(rule[i], i)));
        reverse_dependency_graph.insert(pair<int, Node>(i, Node(rule[i], i)));
        checkForDependency(rule[i], i);
    }
    

    
    cur_postorder = 1;
    DFS_Forest();
    findSCC();

}

void Graph::checkForDependency(Rule rule, int k)
{

    for (int i=0; i < this->rules.size(); i++)
    {
        for (int j=0; j < this->rules[i].getPredicates().size();j++)
        {
            
            if (rule.getName().name == rules[i].getPredicates()[j].name)
            {
                dependency_graph[i].insert_adjacent_node(k);
                reverse_dependency_graph[k].insert_adjacent_node(i);
            }
        }
    }
    
}

void Graph::DFS(int i, set<int>& SCC_set)
{
    set<int> adj_nodes;
    

    if (!scc)
    {
        reverse_dependency_graph[i].mark_as_visited();
        adj_nodes = reverse_dependency_graph[i].adjacent_nodes;
    }
    else
    {
        dependency_graph[i].mark_as_visited();
        adj_nodes = dependency_graph[i].adjacent_nodes;
    }


    for (auto j : adj_nodes )
    {
        if (!scc)
        {
            if (!reverse_dependency_graph.at(j).visited)
            {
                DFS(j, SCC_set);
            }
        }
        else
        {
            if (!dependency_graph[j].visited)
            {
                DFS(j, SCC_set);
            }
        }

    }
    
    if (!scc)
    {
        reverse_dependency_graph[i].setPostOrder(cur_postorder);
        cur_postorder++;
    }
    else
    {
        SCC_set.insert(i);
    }
}

void Graph::DFS_Forest()
{
    for (auto node : reverse_dependency_graph)
    {
        set<int> set;
        if (!node.second.visited)
        {
            DFS(node.first, set);
        }
    }
}

void Graph::findSCC()
{
    vector<int> search_order;
    getSearchOrder(search_order);
    scc = true;
    for (int i=0; i < search_order.size(); i++)
    {
        set<int> SCC_set;
        if (!dependency_graph[search_order[i]].visited)
        {
            DFS(search_order[i], SCC_set);
        }
        
        SCCs.insert(pair<int, set<int>>(search_order[i], SCC_set));
    }

}

void Graph::getSearchOrder(vector<int>& order)
{

    for (int i = cur_postorder; i > 0; i--)
    {
        for (auto node : reverse_dependency_graph)
        {
            if (i == node.second.postorder_num)
            {
                order.push_back(node.first);
            }
        }
    }
}

string Graph::dependencyGraphToString()
{
    stringstream ss;
    ss << "Dependency Graph\n";
    for (auto node : dependency_graph)
    {
        ss << "  R" << node.first << ": " << node.second.adjacentNodesToString() << endl;
    }
    ss << endl;
    
    return ss.str();
}

string Graph::reverseGraphToString()
{
    stringstream ss;
    ss << "Reverse Graph\n";
    for (auto node : reverse_dependency_graph)
    {
        ss << "  R" << node.first << ": " << node.second.adjacentNodesToString() << endl;
    }
    ss << endl;
    
    return ss.str();
}

string Graph::postOrderToString()
{
    stringstream ss;
    ss << "Postorder Numbers\n";
    for (auto node : reverse_dependency_graph)
    {
        ss << "  R" << node.first << ": " << node.second.postorder_num << endl;
    }
    ss << endl;
    
    return ss.str();
}

string Graph::sccSearchOrder()
{
    stringstream ss;
    ss << "SCC Search Order\n";
    vector<int> search_order;
    getSearchOrder(search_order);
    for (int i=0; i < search_order.size(); i++)
    {
        ss << "  R" << search_order[i] << endl;
    }
    ss << endl;
    
    return ss.str();
}