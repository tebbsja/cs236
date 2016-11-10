/*
 * Parser.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#include "Parser.h"
#include <sstream>
#include <iostream>

Parser::Parser(std::vector<Token*> & tokens) {
	this->tokens = tokens;
	current_token_index = 0;
	current_token = this->tokens.at(current_token_index);
	program = DatalogProgram();

	current_predicate = Predicate("a");
	current_rule = Rule(Predicate("a"));

	try {
		match(Token::SCHEMES);
		match(Token::COLON);
		current_type = Token::SCHEMES;
		scheme();
		schemeList();

		match(Token::FACTS);
		match(Token::COLON);
		current_type = Token::FACTS;
		factList();

		match(Token::RULES);
		match(Token::COLON);
		current_type = Token::RULES;
		ruleList();

		match(Token::QUERIES);
		match(Token::COLON);
		current_type = Token::QUERIES;
		query();
		queryList();

		std::cout << "\tSuccess!" << std::endl;
	}
	catch (Token* current_token) {
		std::stringstream err;
		err << "Failure!" << std::endl;
		err << "\t(" << current_token->type_to_string[current_token->token_type] << ",\""
				<< current_token->value << "\","
				<< current_token->line << ")" << std::endl;
		program.error(err.str());
	}
}

Parser::~Parser() {
	tokens.clear();
}

void Parser::parameter () {
    if(current_token->token_type == Token::STRING) {
    	// Push the parameters into the current predicate as strings
    	current_predicate.params.push_back(Parameter(current_token->value, true));

    	// Put the string into the domain
    	program.domain.insert(current_token->value);

        match(Token::STRING);
    }
    else if (current_token->token_type == Token::ID) {
    	// Push the parameters into the current predicate as IDs
    	current_predicate.params.push_back(Parameter(current_token->value, false));
        match(Token::ID);
    }
    else {
        error();
    }
}

void Parser::parameterList() {
	// Keep calling the parameter function as long as there are parameters remaining in the list
    if (current_token->token_type == Token::COMMA) {
        match(Token::COMMA);
        parameter();
        parameterList();
    }
}

void Parser::predicate() {
    if (current_token->token_type == Token::ID) {
		current_predicate = Predicate(current_token->value);
        match(Token::ID);
        match(Token::LEFT_PAREN);
        parameter();
        parameterList();
        match(Token::RIGHT_PAREN);
        push_current_predicate();
    }
    else {
        error();
    }
}

void Parser::predicateList() {
    if (current_token->token_type == Token::COMMA) {
        match(Token::COMMA);
        predicate();
        predicateList();
    }
}

void Parser::query() {
    predicate();
    match(Token::Q_MARK);
}

void Parser::rule() {
	// Flag that you are starting a rule i.e. before the :-
	current_type = Token::COLON_DASH;
    predicate();

    // Flag that you have finished the rule head and are starting the body
    current_type = Token::RULES;
    match(Token::COLON_DASH);
    predicate();
    predicateList();
    match(Token::PERIOD);

    // Push the completed rule on
    program.rules.push_back(current_rule);
}

void Parser::fact() {
    predicate();
    match(Token::PERIOD);
}

void Parser::scheme() {
    predicate();
}

void Parser::queryList() {
    if (current_token->token_type != Token::END) {
        query();
        queryList();
    }
}

void Parser::ruleList() {
    if (current_token->token_type == Token::COMMA ||
        current_token->token_type == Token::ID) {
        rule();
        ruleList();
    }
}

void Parser::factList() {
    if (current_token->token_type == Token::COMMA ||
        current_token->token_type == Token::ID) {
        fact();
        factList();
    }
}

void Parser::schemeList() {
    if (current_token->token_type != Token::FACTS) {
        scheme();
        schemeList();
    }
}

void Parser::error () {
    throw current_token;
};

void Parser::match(Token::TType type) {
    if (type == current_token->token_type) {
        current_token_index++;
        current_token = tokens.at(current_token_index);
    }
    else {
        error();
    }
}

void Parser::push_current_predicate() {
	Token::TType container = current_type;

	switch(container) {
	case Token::SCHEMES:
		program.schemes.push_back(current_predicate);
		break;
	case Token::FACTS:
		program.facts.push_back(current_predicate);
		break;
	case Token::COLON_DASH:
		current_rule = Rule(current_predicate);
		break;
	case Token::RULES:
		current_rule.body.push_back(current_predicate);
		break;
	case Token::QUERIES:
		program.queries.push_back(current_predicate);
		break;
	default:
		break;
	}
}

DatalogProgram Parser::get_program() {
	return program;
}
