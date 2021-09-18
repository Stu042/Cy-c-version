#pragma once
#include <string>


enum class LiteralType {
	NONE, INT, FLOAT, STRING
};


class Literal {
public:
	LiteralType type;
	union Value {
		long long i;
		long double f;
		char* s;
	}value;

	Literal(LiteralType type = LiteralType::NONE) {
		this->type = LiteralType::NONE;
		this->value.i = 0;
	}
	Literal(long i) {
		this->type = LiteralType::INT;
		this->value.i = i;
	}
	Literal(double f) {
		this->type = LiteralType::FLOAT;
		this->value.f = f;
	}
	Literal(std::string s) {
		this->type = LiteralType::STRING;
		this->value.s = new char[s.length() + 1];
		strcpy(this->value.s, s.c_str());
	}
	~Literal() {
		if (this->type == LiteralType::STRING) {
			delete this->value.s;
		}
	}
};
