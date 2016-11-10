/*
 * DatalogProgram.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#include <sstream>
#include <iostream>
#include "DatalogProgram.h"

DatalogProgram::~DatalogProgram() {
	schemes.clear();
	facts.clear();
	rules.clear();
	queries.clear();
	domain.clear();
}

std::string DatalogProgram::to_string() {
	std::stringstream prog;

	if (has_error) {
		prog << error_message;
		return prog.str();
	}

	prog << "Success!" << std::endl;

	// Schemes
	prog << predicate_vector_to_string(schemes, "Schemes");

	// Facts
	prog << predicate_vector_to_string(facts, "Facts");

	// Rules
	int num_rules = rules.size();
	prog << "Rules(" << num_rules << "):\n";
	for (int i = 0; i < num_rules; i++)
	{
		Rule rule = rules.at(i);
		prog << "\t" << rule.head.to_string() << " :- ";

		int body_size = rule.body.size();
		for (int i = 0; i < body_size; i++)
		{
			prog << rule.body.at(i).to_string();
			if (i != (body_size - 1))
				prog << ",";
		}
		prog << std::endl;
	}

	// Queries
	prog << predicate_vector_to_string(queries, "Queries");

	// Domain
	int domain_size = domain.size();
	prog << "Domain(" << domain_size << "):\n";
	for (std::string item : domain)
	{
		prog << "\t" << item << std::endl;
	}

	return prog.str();
}

std::string DatalogProgram::predicate_vector_to_string(std::vector<Predicate> vec, std::string name) {
	std::stringstream o;

	int size = vec.size();
	o << name << "(" << size << "):" << std::endl;
	for (int i = 0; i < size; i++)
	{
		o << "\t" << vec.at(i).to_string() << std::endl;
	}

	return o.str();
}

void DatalogProgram::error(std::string message) {
	has_error = true;
	error_message = message;
}
