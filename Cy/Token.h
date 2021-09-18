#pragma once
#include <string>
#include <ostream>
#include "Error.h"
#include "Literal.h"



enum TokenType {
	// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
	COLON, THREAD_NO,

	// One or two character tokens.
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals.
	IDENTIFIER, STRING, NUMBER,

	// Keywords.
	ELSE, FALSE, FUN, FOR, IF, NIL,
	PRINT, RETURN, SUPER, THIS, TRUE, WHILE,

	TAB, NEWLINE, END_OF_FILE,
	IGNORED
};



class Token {
public:
	const static char* typeString[];
	TokenType type;			// type of token, i.e. BANG, IF, ELSE, FALSE, END_OF_FILE, etc...
	std::string filename;	// name of file token is in
	std::string lexeme;		// the string found
	size_t lineNo;			// line number token is on
	size_t fileOffset;		// offset from start of file
	size_t lineOffset;		// index from start of line
	Literal literal;		// if token represents a value this is where it is stored.
	std::string source;		// source file

	Token(TokenType type, std::string lexeme, std::string filename, int indentation, size_t lineNo, size_t fileOffset, std::string source);
	Token(TokenType type, std::string lexeme, Literal literalValue, std::string filename, int indentation, size_t lineNo, size_t fileOffset, std::string source);

	friend std::ostream& operator<<(std::ostream& os, const Token& token);
};
