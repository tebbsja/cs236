/*
 * Rule.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#include <sstream>
#include "Rule.h"

Rule::~Rule() {
	body.clear();
}

std::string Rule::to_string() {
	std::stringstream s;

	s << this->head.name << "(";

	int num_head_params = this->head.params.size();
	for (int i = 0; i < num_head_params; i++) {
		s << this->head.params.at(i).value;
		if ( i != (num_head_params - 1))
			s << ",";
	}

	s << ") :- ";

	int num_predicates = this->body.size();
	for (int i = 0; i < num_predicates; i++) {
		s << this->body.at(i).to_string();
		if ( i != (num_predicates - 1))
			s << ",";
	}

	return s.str();
}
