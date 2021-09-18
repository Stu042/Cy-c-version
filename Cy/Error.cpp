#include <string>
#include <iostream>
#include <algorithm>
#include "Error.h"
#include "Utils.h"



void displayCharAtIndex(size_t lineOffset, std::string linestr, char spacer, char pointer) {
	for (int a = 0; a < lineOffset; a++) {
		if (linestr[a] == '\t') {
			int pos = 4 - (a % 4);
			std::cout << std::string(4, spacer);
		} else {
			std::cout << spacer;
		}
	}
	std::cout << pointer << std::endl;
}


void Error(std::string filename, size_t line, size_t lineOffset, std::string linestr, std::string message) {
	std::string newLine = ReplaceTabsWithSpaces(linestr, 4);

	std::cout << "Error in " << filename << ": " << message << std::endl;
	std::cout << "\t" << line << " " << ReplaceTabsWithSpaces(linestr, 4) << std::endl;
	std::cout << "\t" << std::string(std::to_string(line).length() + 1, ' ');
	displayCharAtIndex(lineOffset, linestr, ' ', char(179));
	std::cout << "\t" << std::string(std::to_string(line).length() + 1, ' ');
	displayCharAtIndex(lineOffset, linestr, '-', char(217));
}
