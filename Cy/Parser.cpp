#include "Parser.h"
#include "Scanner.h"
#include "Expr.h"


//Parser::Parser(std::vector<Token> tokens) {
//	tokens = tokens;
//}
//
//
//Expr Parser::Expression() {
//	return Equality();
//}
//
//Expr Parser::Comparison() {
//	Expr expr = Term();
//	while (Match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
//		Token op = Previous();
//		Expr right = Term();
//		expr = new Expr.Binary(expr, op, right);
//	}
//	return expr;
//}
//
//Expr Parser::Equality() {
//	Expr expr = Comparison();
//	while (Match(BANG_EQUAL, EQUAL_EQUAL)) {
//		Token op = Previous();
//		Expr right = Comparison();
//		expr = new Expr.Binary(expr, op, right);
//	}
//	return expr;
//}
//
//
//Expr Parser::Term() {
//	Expr expr = Factor();
//	while (Match(TokenType::MINUS, TokenType::PLUS)) {
//		Token op = Previous();
//		Expr right = Factor();
//		expr = new Expr.Binary(expr, op, right);
//	}
//	return expr;
//}
//
//
//Expr Parser::Factor() {
//	Expr expr = Unary();
//	while (Match(TokenType::SLASH, TokenType::STAR)) {
//		Token op = Previous();
//		Expr right = Unary();
//		expr = new Expr.Binary(expr, op, right);
//	}
//	return expr;
//}
//
//Expr Parser::Unary() {
//	if (Match(TokenType::BANG, TokenType::MINUS)) {
//		Token op = Previous();
//		Expr right = Unary();
//		return new Expr.Unary(op, right);
//	}
//	return Primary();
//}
//
//Expr Parser::Primary() {
//	if (Match(TokenType::FALSE)) {
//		return new Expr.Literal(false);
//	}
//	if (Match(TokenType::TRUE)) {
//		return new Expr.Literal(true);
//	}
//	if (Match(TokenType::NIL)) {
//		return new Expr.Literal(NULL);
//	}
//	if (Match(TokenType::NUMBER, TokenType::STRING)) {
//		return new Expr.Literal(Previous().literal);
//	}
//	if (Match(TokenType::LEFT_PAREN)) {
//		Expr expr = Expression();
//		Consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
//		return new Expr.Grouping(expr);
//	}
//	throw Error(Peek(), "Expect expression.");
//}
//
//Expr Parser::Parse() {
//	try {
//		return Expression();
//	} catch (ParseError error) {
//		return NULL;
//	}
//}
//
//bool Parser::Match(TokenType types...) {
//	for (TokenType type : { types }) {
//		if (Check(type)) {
//			Advance();
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool Parser::Check(TokenType type) {
//	if (IsAtEnd()) return false;
//	return Peek().type == type;
//}
//
//Token Parser::Advance() {
//	if (!IsAtEnd()) {
//		current++;
//	}
//	return Previous();
//}
//
//bool Parser::IsAtEnd() {
//	return current >= tokens.size();
//}
//
//Token Parser::Peek() {
//	return tokens[current];
//}
//
//Token Parser::Previous() {
//	return tokens[current - 1];
//}
//
//Token Parser::Consume(TokenType type, std::string message) {
//	if (Check(type)) {
//		return Advance();
//	}
//	throw Error(Peek(), message);
//}
//
//void Parser::Synchronise() {
//	Advance();
//	while (!IsAtEnd()) {
//		if (Previous().type == SEMICOLON) {
//			return;
//		}
//		switch (Peek().type) {
//			//case TokenType::CLASS:
//			//case TokenType::VAR:
//			case TokenType::FUN:
//			case TokenType::FOR:
//			case TokenType::IF:
//			case TokenType::WHILE:
//			case TokenType::PRINT:
//			case TokenType::RETURN:
//				return;
//		}
//		Advance();
//	}
//}
//
//
//ParseError Parser::Error(Token token, std::string message) {
//	Cy.Error(token, message);
//	return new ParseError();
//}
//
