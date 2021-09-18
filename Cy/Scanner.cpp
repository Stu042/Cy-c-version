#include "Scanner.h"
#include "Error.h"
#include "Token.h"
#include "Utils.h"
#include <string>
#include <map>
#include <vector>


std::map<std::string, TokenType> Scanner::keywords = {
	{ "else", TokenType::ELSE },
	{ "false", TokenType::FALSE },
	{ "for", TokenType::FOR },
	{ "if", TokenType::IF },
	{ "null", TokenType::NIL },
	{ "print", TokenType::PRINT },
	{ "return", TokenType::RETURN },
	{ "super", TokenType::SUPER },
	{ "this", TokenType::THIS },
	{ "true", TokenType::TRUE },
	{ "while", TokenType::WHILE },
	{ "#", TokenType::THREAD_NO },
};


Scanner::Scanner(std::string afilename, std::string asource) {
	filename = afilename;
	source = asource;
}


std::vector<Token> Scanner::ScanTokens() {
	while (!IsAtEnd()) {		// We are at the beginning of the next lexeme.
		start = current;
		ScanToken();
	}
	tokens.push_back(Token(TokenType::END_OF_FILE, "", filename, 0, line, start, source));
	return tokens;
}


void Scanner::ScanToken() {
	char c = Advance();
	switch (c) {
	case '(':
		AddToken(TokenType::LEFT_PAREN);
		break;
	case ')':
		AddToken(TokenType::RIGHT_PAREN);
		break;
	case '{':
		AddToken(TokenType::LEFT_BRACE);
		break;
	case '}':
		AddToken(TokenType::RIGHT_BRACE);
		break;
	case ',':
		AddToken(TokenType::COMMA);
		break;
	case '.':
		AddToken(TokenType::DOT);
		break;
	case '-':
		AddToken(TokenType::MINUS);
		break;
	case '+':
		AddToken(TokenType::PLUS);
		break;
	case ':':
		AddToken(TokenType::COLON);
		break;
	case ';':
		AddToken(TokenType::SEMICOLON);
		break;
	case '*':
		AddToken(TokenType::STAR);
		break;
	case '#':
		AddToken(TokenType::THREAD_NO);
		break;
	case '!':
		AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
		break;
	case '=':
		AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
		break;
	case '<':
		AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
		break;
	case '>':
		AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
		break;
	case '/':
		if (Match('/')) {	// A comment goes until the end of the line.
			while (Peek() != '\n' && !IsAtEnd()) {
				Advance();
			}
			AddToken(TokenType::IGNORED);
		} else {
			AddToken(TokenType::SLASH);
		}
		break;
	case ' ':
	case '\r':	// Ignore most whitespace.
		AddToken(TokenType::IGNORED);
		break;
	case '\t':
		AddToken(TokenType::TAB);
		indentation++;
		break;
	case '\n':
		AddToken(TokenType::NEWLINE);
		indentation = 0;
		line++;
		break;
	case '"':
		String();
		break;
	default:
		if (IsDigit(c)) {
			Number();
		} else if (IsAlpha(c)) {
			Identifier();
		} else {
			Error(filename, line, start - GetStartOfLineIndex(start, source), GetLine(start, source), "Unexpected character.");
			hadError = true;
		}
		break;
	}
}


void Scanner::Identifier() {
	while (IsAlphaNumeric(Peek())) {
		Advance();
	}
	// See if the identifier is a reserved word.
	std::string text = source.substr(start, current - start);
	TokenType type;
	std::map<std::string, TokenType>::iterator it = keywords.find(text);
	if (it != keywords.end()) {
		type = it->second;
	} else {
		type = TokenType::IDENTIFIER;
	}
	AddToken(type);
}


void Scanner::Number() {
	while (IsDigit(Peek()))
		Advance();
	// Look for a fractional part.
	if (Peek() == '.' && IsDigit(PeekNext())) {
		// Consume the "."
		Advance();
		while (IsDigit(Peek()))
			Advance();
		size_t idx = 0;
		AddToken(TokenType::NUMBER, std::stod(source.substr(start, current - start), &idx));
	} else {
		size_t idx = 0;
		AddToken(TokenType::NUMBER, std::stol(source.substr(start, current - start), &idx));
	}
}

void Scanner::String() {
	while (Peek() != '"' && !IsAtEnd()) {
		if (Peek() == '\n')
			line++;
		Advance();
	}
	// Unterminated string.
	if (IsAtEnd()) {
		Error(filename, line, start - GetStartOfLineIndex(start, source), GetLine(start, source), "Unterminated string.");
		hadError = true;
		return;
	}
	// Trim the surrounding quotes.
	std::string value = source.substr(start + 1, current - start - 1);
	AddToken(TokenType::STRING, value);
	Advance();
}


// if current char is expected then inc index and return true
bool Scanner::Match(char expected) {
	if (IsAtEnd())
		return false;
	if (source[current] != expected)
		return false;
	current++;
	return true;
}

char Scanner::Peek() {
	if (IsAtEnd())
		return '\0';
	return source[current];
}

char Scanner::PeekNext() {
	if ((current + 1) >= source.length())
		return '\0';
	return source[current + 1];
}

bool Scanner::IsAlpha(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::IsAlphaNumeric(char c) {
	return IsAlpha(c) || IsDigit(c);
}

bool Scanner::IsDigit(char c) {
	return c >= '0' && c <= '9';
}

bool Scanner::IsAtEnd() {
	return current >= source.length();
}

char Scanner::Advance() {
	current++;
	return source[current - 1];
}

void Scanner::AddToken(TokenType type) {
	std::string text = source.substr(start, current - start);
	tokens.push_back(Token(type, text, filename, indentation, line, start, source));
}
void Scanner::AddToken(TokenType type, std::string str) {
	std::string text = source.substr(start + 1, current - start - 1);
	tokens.push_back(Token(type, text, str, filename, indentation, line, start, source));
}
void Scanner::AddToken(TokenType type, double f) {
	std::string text = source.substr(start, current - start);
	tokens.push_back(Token(type, text, Literal(f), filename, indentation, line, start, source));
}
void Scanner::AddToken(TokenType type, long i) {
	std::string text = source.substr(start, current - start);
	tokens.push_back(Token(type, text, Literal(i), filename, indentation, line, start, source));
}

void Scanner::AddToken(TokenType type, Literal literalValue) {
	std::string text = source.substr(start, current - start);
	tokens.push_back(Token(type, text, literalValue, filename, indentation, line, start, source));
}

