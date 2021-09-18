#pragma once
#include <vector>
#include "Token.h"
#include "Expr.h"
//
//class Parser {
//private:
//	std::vector<Token> tokens;
//	size_t current = 0;
//	bool hadError = false;
//
//	//static class ParseError : std::exception {}
//
//public:
//
//	Parser(std::vector<Token> tokens);
//
//private:
//	Expr Expression();
//	Expr Comparison();
//	Expr Equality();
//	Expr Term();
//	Expr Factor();
//	Expr Unary();
//	Expr Primary();
//
//	Expr Parse();
//
//	bool Match(TokenType types...);
//	bool Check(TokenType type);
//	Token Advance();
//	bool IsAtEnd();
//	Token Peek();
//	Token Previous();
//	Token Consume(TokenType type, std::string message);
//
//	void Parser::Synchronise();
//
//	ParseError Error(Token token, std::string message);
//	void Error(Token token, std::string message);
//};
