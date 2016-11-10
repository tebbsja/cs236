/*
 * Parameter.h
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <string>

class Parameter {
public:
	Parameter(std::string value, bool is_string) : is_string(is_string), value(value) {};
	virtual ~Parameter() {};
	bool is_string;
	std::string value;
};

#endif /* PARAMETER_H_ */
