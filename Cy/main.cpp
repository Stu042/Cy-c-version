// Cy.cpp : Defines the entry point for the application.
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include "main.h"
#include "Scanner.h"
#include "Error.h"
#include "Parser.h"


// compile the source
unsigned int Compile(std::string filename, std::string source) {
	Scanner scanner = Scanner(filename, source);
	std::vector<Token> tokens = scanner.ScanTokens();
	if (!scanner.hadError) {	// For now, just print the tokens.
		std::cout << "Tokens:" << std::endl;
		size_t count = tokens.size();
		for (Token token : tokens) {
			std::cout << token << std::endl;
		}
		//Parser parser = new Parser(tokens);
		//Expr expression = parser.Parse();

		//if (parser.hadError) {		// Stop if there was a syntax error.
		//	return -1;
		//}

		//new AstPrinter().print(expression);
		return 0;
	}
	return -2;
}


// Compile a file
void CompileFile(std::string path) {
	std::ifstream t(path);
	std::string str;
	t.seekg(0, std::ios::end);
	str.reserve((size_t)t.tellg());
	t.seekg(0, std::ios::beg);
	str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	int scannerResult = Compile(path, str);
	if (scannerResult != 0) {
		exit(scannerResult);
	}
}


int main(int argc, char* argv[]) {
	if (argc == 2) {
		CompileFile(argv[1]);
	} else {
		std::cout << "Usage: cy [filename.cy]" << std::endl;
		return 64;
	}
	return 0;
}
