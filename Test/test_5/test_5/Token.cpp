/*
 * Token.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: mocklera
 */

#include "Token.h"

Token::Token(std::string value, int line, Token::TType type) {
	this->value = value;
	this->line = line;
	this->token_type = type;
	type_to_string = {
		{ COMMA, "COMMA" },
		{ PERIOD, "PERIOD" },
		{ Q_MARK, "Q_MARK"},
		{ LEFT_PAREN, "LEFT_PAREN" },
		{ RIGHT_PAREN, "RIGHT_PAREN" },
		{ COLON, "COLON" },
		{ COLON_DASH, "COLON_DASH" },
		{ SCHEMES, "SCHEMES" },
		{ FACTS, "FACTS" },
		{ RULES, "RULES" },
		{ QUERIES, "QUERIES" },
		{ ID, "ID" },
		{ STRING, "STRING" },
		{ END, "EOF" },
		{ ERROR, "Error" }
	};
}

Token::~Token() {
	type_to_string.clear();
}
