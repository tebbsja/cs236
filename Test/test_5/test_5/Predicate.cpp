/*
 * Predicate.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#include <sstream>
#include "Predicate.h"

Predicate::~Predicate() {
	params.clear();
}

std::string Predicate::to_string() {
	std::stringstream s;

	s << name << "(";

	int num_params = params.size();
	for (int i = 0; i < num_params; i++)
	{
		s << params.at(i).value;
		if (i != (num_params - 1))
			s << ",";
	}

	s << ")";

	return s.str();
}
