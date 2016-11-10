/*
 * Database.h
 *
 *  Created on: Jul 27, 2015
 *      Author: mocklera
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <map>
#include "DatalogProgram.h"
#include "Relation.h"
#include "Graph.h"

class Database {
public:
	Database();
	virtual ~Database();
	void load(DatalogProgram program);
	void evaluate_schemes();
	void evaluate_facts();
    std::string evaluate_rules(std::vector<Rule> & rules);
	std::string evaluate_queries();
	std::string relations_to_string();
    std::string initialize_graph();
    std::string evaluate_rules_from_graph();

private:
	DatalogProgram program;
	std::map<std::string, Relation> relations;
	void add_scheme(int index);
	void add_fact(int index);
	void add_relation_to_map(std::string name, Relation relation);
	Relation get_relation(std::string name);
	Relation query_project(Relation r, int index);
	Relation query_rename(Relation r, int index);
	Scheme join_scheme(Scheme s1, Scheme s2);

	Relation select(Relation r, std::vector<Parameter> params);
	Relation project(Relation r, std::vector<Parameter> params);
	Relation project_rule(Relation r, std::vector<Parameter> params);
	Relation rename(Relation r, std::vector<Parameter> params);
	Relation join(std::vector<Relation> relations);
	Relation r_union();

    bool determine_repeat(std::vector<Rule> rules);
	int total_tuples();
    
    Graph graph;
};

#endif /* DATABASE_H_ */
