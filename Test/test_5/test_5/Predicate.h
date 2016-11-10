/*
 * Predicate.h
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#ifndef PREDICATE_H_
#define PREDICATE_H_

#include "Parameter.h"
#include <string>
#include <vector>

class Predicate {
public:
	Predicate(){};
	Predicate(std::string name) : name(name) {};
	virtual ~Predicate();
	std::string name;
	std::vector<Parameter> params;
	std::string to_string();
};

#endif /* PREDICATE_H_ */
