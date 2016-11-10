/*
 * Rule.h
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#ifndef RULE_H_
#define RULE_H_

#include "Predicate.h"
#include <vector>

class Rule {
public:
	Rule(){};
	Rule(Predicate head) : head(head) {};
	virtual ~Rule();
	Predicate head;
	std::vector<Predicate> body;
	std::string to_string();
};

#endif /* RULE_H_ */
