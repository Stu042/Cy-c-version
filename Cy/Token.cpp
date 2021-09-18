#include <string>
#include <iomanip>
#include "Token.h"
#include "Error.h"
#include "Utils.h"


const char* Token::typeString[] = {
	"LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
	"COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",
	"COLON", "THREAD_NO",

	// One or two character tokens.
	"BANG", "BANG_EQUAL",
	"EQUAL", "EQUAL_EQUAL",
	"GREATER", "GREATER_EQUAL",
	"LESS", "LESS_EQUAL",

	// Literals.
	"IDENTIFIER", "STRING", "NUMBER",

	// Keywords.
	"ELSE", "FALSE", "FUN", "FOR", "IF", "NIL",
	"PRINT", "RETURN", "SUPER", "THIS", "TRUE", "WHILE",

	"TAB", "NEWLINE", "EOF",
	"IGNORED"
};



Token::Token(TokenType type, std::string lexeme, std::string filename, int indentation, size_t lineNo, size_t fileOffset, std::string source) {
	this->type = type;
	this->lexeme = std::string(lexeme);
	this->filename = filename;
	this->literal.type = LiteralType::NONE;
	this->literal.value.i = 0;
	this->lineNo = lineNo;
	this->fileOffset = fileOffset;
	this->lineOffset = GetLineIndex(fileOffset, source);
	this->source = source;
}

Token::Token(TokenType type, std::string lexeme, Literal literalValue, std::string filename, int indentation, size_t lineNo, size_t fileOffset, std::string source) {
	this->type = type;
	this->lexeme = std::string(lexeme);
	this->literal = literalValue;
	this->filename = filename;
	this->lineNo = lineNo;
	this->fileOffset = fileOffset;
	this->lineOffset = GetLineIndex(fileOffset, source);
	this->source = source;
}



std::ostream& operator<<(std::ostream& os, const Token& token) {
	std::string literalTypeText;
	std::string literalValueText;
	std::string lexemeText;
	switch (token.literal.type) {
	case LiteralType::INT:
		literalTypeText = "INT";
		literalValueText = std::to_string(token.literal.value.i);
		lexemeText = token.lexeme.c_str();
		break;
	case LiteralType::FLOAT:
		literalTypeText = "FLOAT";
		literalValueText = std::to_string(token.literal.value.f);
		lexemeText = token.lexeme.c_str();
		break;
	case LiteralType::STRING:
		literalTypeText = "STRING";
		literalValueText = token.literal.value.s;
		lexemeText = token.lexeme.c_str();
		break;
	case LiteralType::NONE:
		literalTypeText = "*";
		literalValueText = "*";
		if (token.type == TokenType::NEWLINE) {
			lexemeText = "\\n";
		} else if (token.type == TokenType::TAB) {
			lexemeText = "\\t";
		} else {
			lexemeText = token.lexeme;
			lexemeText.erase(std::remove(lexemeText.begin(), lexemeText.end(), '\r'), lexemeText.end());
		}
		break;
	default:
		Error(token.filename, token.lineNo, token.lineNo, GetLine(token.fileOffset, token.source), "Unknown literal type in Token::string()");
	}
	os << std::left << std::setw(16) << token.typeString[token.type] <<
		std::setw(32) << lexemeText.substr(0, 31) <<
		std::setw(8) << literalTypeText <<
		std::setw(8) << literalValueText <<
		" Line:" << std::setw(4) << token.lineNo <<
		" Offset:" << std::setw(3) << token.lineOffset <<
		" Index:" << std::setw(5) << token.fileOffset;
	return os;
}
