/*
 * Token.h
 *
 *  Created on: Jun 29, 2015
 *      Author: mocklera
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <map>

class Token {
public:
	enum TType{COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, END, ERROR} token_type;

	Token(std::string value, int line, Token::TType type);
	virtual ~Token();
	
	std::string value;
	int line;
	std::map<TType, std::string> type_to_string; // type_to_string[token_type]
};

#endif /* TOKEN_H_ */
