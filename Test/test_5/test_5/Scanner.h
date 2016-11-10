/*
 * Scanner.h
 *
 *  Created on: Jun 29, 2015
 *      Author: mocklera
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "Token.h"
#include <vector>
#include <fstream>

class Scanner {
public:
	Scanner(char* input_file);
	virtual ~Scanner();
	std::vector<Token*> getTokens();
	void scan();
private:
	void scan_punctuation(char token, Token::TType type);
	void scan_colon();
	void scan_comment();
	void scan_string();
	void scan_id(char token);
	bool is_keyword(std::string id);
	void add_token(char t, Token::TType type);
	void add_token(std::string t, Token::TType type);
	void clearTokens();

	std::vector<Token*> tokens;
	int line;
	std::ifstream file;
	int error;
};

#endif /* SCANNER_H_ */
