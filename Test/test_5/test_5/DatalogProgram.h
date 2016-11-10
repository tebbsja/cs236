/*
 * DatalogProgram.h
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_

#include <string>
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"

class DatalogProgram {
public:
	DatalogProgram(){has_error = false;};
	virtual ~DatalogProgram();

	std::string to_string();
	std::string predicate_vector_to_string(std::vector<Predicate> vec, std::string name);

	std::vector<Predicate> schemes;
	std::vector<Predicate> facts;
	std::vector<Rule> rules;
	std::vector<Predicate> queries;
	std::set<std::string> domain;

	void error(std::string message);

private:
	bool has_error;
	std::string error_message;
};

#endif /* DATALOGPROGRAM_H_ */
