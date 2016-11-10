/*
 * Parser.h
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include "Scanner.h"
#include "Parameter.h"
#include "DatalogProgram.h"

class Parser {
public:
	Parser(std::vector<Token*> & tokens);
	virtual ~Parser();

	DatalogProgram get_program();

private:
	std::vector<Token*> tokens;
	Token * current_token;
	int current_token_index;

	Token::TType current_type;

	DatalogProgram program;

	Predicate current_predicate;
	Rule current_rule;

	void push_current_predicate();

	void parameter();
	void parameterList();
	void predicate();
	void predicateList();
	void scheme();
	void fact();
	void query();
	void rule();
	void queryList();
	void ruleList();
	void factList();
	void schemeList();

	void error();
	void match(Token::TType type);
};

#endif /* PARSER_H_ */
