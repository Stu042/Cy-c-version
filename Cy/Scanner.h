#pragma once
#include <vector>
#include <string>
#include <map> 
#include "Token.h"



/**
 * @brief Scan a string and output the Token components of that string.
*/
class Scanner {
private:
	std::string filename;
	std::string source;
	std::vector<Token> tokens;
	size_t start = 1;
	size_t current = 0;
	size_t line = 1;
	int indentation = 0;

	static std::map<std::string, TokenType> keywords;

public:
	bool hadError = false;

	Scanner(std::string filename, std::string source);

	std::vector<Token> ScanTokens();

private:
	void ScanToken();
	bool IsAtEnd();
	char Advance();
	
	void AddToken(TokenType type);
	void AddToken(TokenType type, std::string str);
	void AddToken(TokenType type, double d);
	void AddToken(TokenType type, long i);
	void AddToken(TokenType type, Literal literalValue);

	void Identifier();
	void Number();
	void String();

	bool Match(char expected);
	char Peek();
	char PeekNext();

	bool IsAlpha(char c);
	bool IsAlphaNumeric(char c);
	bool IsDigit(char c);
};
// Token(Kind kind, string lexeme, string filename, int lineNo, int fileOffset);
