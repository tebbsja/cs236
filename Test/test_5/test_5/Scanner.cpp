/*
 * Scanner.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: mocklera
 */

#include <cctype>
#include <iostream>
#include <sstream>
#include "Token.h"
#include "Scanner.h"

Scanner::Scanner(char* input_file) {
	error = -1;
	line = 1;
	file.open(input_file);
}

Scanner::~Scanner() {
	clearTokens();
	file.close();
}

std::vector<Token*> Scanner::getTokens() {
	return tokens;
}

void Scanner::scan() {
	char token = file.get();
	while (token != EOF && error == -1) {
		switch (token) {
		case ',':
			scan_punctuation(token, Token::COMMA);
			break;
		case '.':
			scan_punctuation(token, Token::PERIOD);
			break;
		case '?':
			scan_punctuation(token, Token::Q_MARK);
			break;
		case '(':
			scan_punctuation(token, Token::LEFT_PAREN);
			break;
		case ')':
			scan_punctuation(token, Token::RIGHT_PAREN);
			break;
		case ':':
			scan_colon();
			break;
		case '#':
			scan_comment();
			break;
		case '\'':
			scan_string();
			break;
		case '\n':
			line++;
			break;
		default:
			scan_id(token);
			break;
		}
		token = file.get();
	}

	if (error == -1) {
		line++;
		add_token("", Token::END);
	}
}

void Scanner::scan_punctuation(char token, Token::TType type) {
	add_token(token, type);
}

void Scanner::scan_colon() {
	if ( file.peek() == '-' ) {
		// Throw out the -
		file.get();
		// Create a :- token
		add_token(":-", Token::COLON_DASH);
	}
	else {
		// Create a : token
		add_token(":", Token::COLON);
	}
}

void Scanner::scan_comment() {
	// As long as the next character isn't a new line, throw it out.
	while (file.peek() != '\n') {
		file.get();
	}
}

void Scanner::scan_string() {
	std::stringstream input_str;
	input_str << '\'';
	char token = file.get();
	while (token != '\'' && token != '\n') {
		input_str << token;
		token = file.get();
		// If the string isn't complete, make an error.
		if (token == '\n')
			error = line;
	}
	if(error == -1) {
		input_str << '\'';
		add_token(input_str.str(), Token::STRING);
	}
	else {
		add_token("", Token::ERROR);
	}
}

void Scanner::scan_id(char token) {
	std::stringstream id;

	// Make sure the char isn't whitespace
	if (!std::isspace(static_cast<unsigned char>(token))) {
		// Check if the first char is a digit or other invalid input
		if (std::isdigit(token) || !std::isalnum(static_cast<unsigned char>(token)) ) {
			std::cout << "Found an error\n";
			error = line;
		}

		id << token;
		while (std::isalnum(static_cast<unsigned char>(file.peek()))) {
			char next = file.get();
			id << next;
		}

		if (error != -1) {
			add_token("", Token::ERROR);
		}
		else {
			std::string id_str = id.str();
			if(!is_keyword(id_str)) {
				add_token(id_str, Token::ID);
			}
		}
	}
}

bool Scanner::is_keyword(std::string id) {
	bool is_keyword;

	if ( id == "Schemes" ) {
		add_token(id, Token::SCHEMES);
		is_keyword = true;
	}
	else if ( id == "Facts" ) {
		add_token(id, Token::FACTS);
		is_keyword = true;
	}
	else if ( id == "Rules" ) {
		add_token(id, Token::RULES);
		is_keyword = true;
	}
	else if ( id == "Queries" ) {
		add_token(id, Token::QUERIES);
		is_keyword = true;
	}
	else {
		is_keyword = false;
	}

	return is_keyword;
}

void Scanner::add_token(char t, Token::TType type) {
	std::stringstream to_s;
	to_s << t;
	Token* tok = new Token(to_s.str(), line, type);
	tokens.push_back(tok);
}

void Scanner::add_token(std::string t, Token::TType type) {
	Token* tok = new Token(t, line, type);
	tokens.push_back(tok);
}

void Scanner::clearTokens() {
	int num = tokens.size();
	for (int i = 0; i < num; i++) {
		Token* t = tokens.at(i);
		delete t;
	}
	tokens.clear();
}
