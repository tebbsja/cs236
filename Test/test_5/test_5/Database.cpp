/*
 * Database.cpp
 *
 *  Created on: Jul 27, 2015
 *      Author: mocklera
 */

#include <iostream>
#include <sstream>
#include <algorithm>
#include "Database.h"

using namespace std;
Database::Database() {
    
}

Database::~Database() {
    
}

void Database::load(DatalogProgram program) {
	this->program = program;
}

void Database::evaluate_schemes() {
	int num_schemes = program.schemes.size();
	for(int i = 0; i < num_schemes; i++) {
		add_scheme(i);
	}
}

void Database::add_scheme(int index) {
	std::string name = program.schemes.at(index).name;
	Relation r = Relation(name);

	int num_attributes = program.schemes.at(index).params.size();
	for (int i = 0; i < num_attributes; i++) {
		r.scheme.push_back(program.schemes.at(index).params.at(i).value);
	}

	add_relation_to_map(name, r);
}

void Database::evaluate_facts() {
	int num_facts = program.facts.size();
	for (int i = 0; i < num_facts; i++) {
		add_fact(i);
	}
}

void Database::add_fact(int index) {
	std::string name = program.facts.at(index).name;
	Tuple t = Tuple();

	int num_values = program.facts.at(index).params.size();
	for (int i = 0; i < num_values; i++) {
		t.push_back(program.facts.at(index).params.at(i).value);
	}

	relations.at(name).tuples.insert(t);
}

// i is the iterator for the queries
// j is the position of the parameter within the query
std::string Database::evaluate_queries() {
	std::stringstream s;

	s << "Query Evaluation\n\n";

	int num_queries = program.queries.size();
	for(int i = 0; i < num_queries; i++) {

		// Get the relation with the same scheme as the name of the query
		std::string relation_name = program.queries.at(i).name;
		s << program.queries.at(i).to_string() << "? ";

		Relation r = relations.at(relation_name);
		Relation r_temp = r; // Create a temporary relation to work on

		std::vector<Parameter> params = program.queries.at(i).params;
		Relation r_select = select(r_temp, params);
		Relation r_project = project(r_select, params);
		Relation r_rename = rename(r_project, params);


		// Print out result
		if ( r_select.tuples.size() > 0 ) {
			s << "Yes(" << r_select.tuples.size() << ")\n";

			s << "select\n";
			s << r_select.to_string();

			s << "project\n";
			s << r_project.to_string();

			s << "rename\n";
			s << r_rename.to_string();

		} else {
			s << "No\n";
		}
		s << "\n";
	}
	return s.str();
}

Relation Database::rename(Relation r, std::vector<Parameter> params) {
	std::vector<std::string> variables;
	int num_parameters = params.size();
	for (int i = 0; i < num_parameters; i++) {
		Parameter param = params.at(i);
		bool is_var = !param.is_string;
		bool duplicate = false;

		int num_var = variables.size();
		for (int j = 0; j < num_var; j++) {
			if (variables.at(j) == param.value) {
				duplicate = true;
			}
		}

		if (is_var && !duplicate) {
			variables.push_back(param.value);
		}
	}

	r = r.rename(variables);

	return r;
}

Relation Database::project(Relation r, std::vector<Parameter> params) {
	int num_params = params.size();
	std::vector<int> indices;

	std::vector<std::string> variables;
	for (int i = 0; i < num_params; i++) {
		bool is_var = !params.at(i).is_string;
		bool duplicate = false;

		int num_var = variables.size();
		for (int j = 0; j < num_var; j++) {
			if (variables.at(j) == params.at(i).value)
				duplicate = true;
		}

		if (is_var && !duplicate) {
			indices.push_back(i);
			variables.push_back(params.at(i).value);
		}
	}

	r = r.project(indices);

	return r;
}

Relation Database::project_rule(Relation r, std::vector<Parameter> params) {
	std::vector<int> indices;
	int scheme_size = r.scheme.size();
	for (auto param : params) {
		for (int i = 0; i < scheme_size; i++) {
			if (param.value == r.scheme.at(i)) {
				indices.push_back(i);
			}
		}
	}

	r = r.project(indices);

	return r;
}

Relation Database::select(Relation r_temp, std::vector<Parameter> params) {
	std::vector<std::string> variables;
	int num_params = params.size();
	for ( int i = 0; i < num_params; i++ ) {
		Parameter param = params.at(i);
		std::string val = param.value;

		if ( param.is_string ) {
			r_temp = r_temp.select(i, val);
		}
		else {
			bool duplicate = false;
			int index1;
			int num_var = variables.size();
			for (int k = 0; k < num_var; k++) {
				if (variables.at(k) == val) {
					index1 = k;
					duplicate = true;
				}
			}
			int index2 = i;

			if (duplicate) {
				r_temp = r_temp.select(index1, index2);
			}
			else {
				variables.push_back(val);
			}
		}
	}

	return r_temp;
}

std::string Database::evaluate_rules_from_graph() {
    std::stringstream s;
    int m = 0;
    std::vector<int> order = graph.get_sort();
    std::map<int, std::set<int>> sccs = graph.get_sccs();
    
    for (int index : order)
    {
        std::vector<Rule> rules_for_eval;
        bool add_newline = false;
        
        // Determine whether or not to output anything. If there is nothing in the connection, don't output anything.
        if (sccs.at(index).size() > 0)
        {
            add_newline = true;
            s << "\nSCC:";
            //cout << "\nSCC:";
            for (auto i : sccs.at(index)) {
                s << " R" << i;
                rules_for_eval.push_back(program.rules.at(i));
            }
            
            
            
           
        }
        //cout << "** " << rules_for_eval[0].to_string() << endl;
        cout << "size " << rules_for_eval.size() << endl;
        
        
        
        s << evaluate_rules(rules_for_eval);
        cout << "size " << rules_for_eval.size() << endl;
        cout << "****\n\n";
        
        
        
        // Continuation of the output rules above; don't output a trailing newline if there is no output.
        if (add_newline) s << std::endl;
    }
    
    s << "\nRule Evaluation Complete\n" << std::endl;
    
    s << relations_to_string();
    
    return s.str();
}

bool Database::determine_repeat(std::vector<Rule> rules) {
    bool should_repeat = false;
    
    std::string head_name = rules.at(0).head.name;
    
    for (auto rule : rules.at(0).body) {
        if (rule.name == head_name) {
            should_repeat = true;
        }
    }
    
    return should_repeat;
}

std::string Database::evaluate_rules(std::vector<Rule> & rules) {
	std::stringstream s;
	int start_count, end_count, total_iterations;
    

	total_iterations = 0;

    bool should_repeat = true;
    if (rules.size() == 1) {
        should_repeat = determine_repeat(rules);
    }
    
	do {
		total_iterations++;
		start_count = total_tuples();
		for (auto rule : rules) {
			Relation result;
			std::vector<Relation> temp_relations;

			for (auto predicate : rule.body) {
				std::string relation_name = predicate.name;
				Relation r = relations.at(relation_name);
				Relation r_temp = r; // temporary relation to work on

				r_temp = select(r_temp, predicate.params);
				r_temp = project(r_temp, predicate.params);
				r_temp = rename(r_temp, predicate.params);

				temp_relations.push_back(r_temp);
			}

			// Populate the result with the first relation processed above
			result = temp_relations.at(0);

			// Do any necessary joins for other relations in the vector
			int num_relations = temp_relations.size();
			if ( num_relations > 1 ) {
				for (int i = 1; i < num_relations; i++) {
					Relation r2 = temp_relations.at(i);
					result = result.join(r2);
				}
			}

			// Project and rename to match the rule head
			result = project_rule(result, rule.head.params);
			result = rename(result, rule.head.params);

			// Union
			s << "\n" << rule.to_string();
			s << relations[rule.head.name].do_union(result);
		}
		end_count = total_tuples();
	} while ((end_count - start_count) > 0 && should_repeat);

	return s.str();
}

std::string Database::initialize_graph() {
    std::stringstream s;
    graph = Graph(program.rules);
    s << graph.dependency_graph_to_string();
    s << graph.reverse_dependency_graph_to_string();
    s << graph.postorder_numbers_to_string();
    return s.str();
}

void Database::add_relation_to_map(std::string name, Relation relation) {
	relations.insert(std::pair<std::string, Relation>(name, relation));
}

Relation Database::get_relation(std::string name) {
	Relation r = relations.at(name);
	return r;
}

std::string Database::relations_to_string() {
	std::stringstream s;

	for (auto item : relations) {
		std::string name = item.first;
		s << name << "\n";

		Relation r = item.second;
		int num_attributes = r.scheme.size();
		for (auto tuple : r.tuples) {
			s << " ";
			for (int i = 0; i < num_attributes; i++) {
				s << " " << r.scheme.at(i) << "=" << tuple.at(i);
			}
			s << "\n";
		}
		s << "\n";
	}

	return s.str();
}

int Database::total_tuples() {
	int count = 0;

	for (auto relation : relations) {
		for ( auto tuple : relation.second.tuples ) {
			count++;
		}
	}

	return count;
}
