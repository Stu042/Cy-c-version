#pragma once
#include <string>


// Display error and mark hadError.
void Error(std::string filename, size_t line, size_t fileOffset, std::string linestr, std::string message);
