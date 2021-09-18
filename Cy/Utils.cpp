#include <string>


size_t GetStartOfLineIndex(size_t start, std::string source) {
	size_t startIndex = start;
	if (source[startIndex] == '\n' && startIndex > 0) {
		--startIndex;
	}
	while (source[startIndex] != '\n' && startIndex > 0)
		--startIndex;
	if (source[startIndex] == '\n') {
		startIndex += 1;
	}
	return startIndex;
}


size_t GetLineIndex(size_t position, std::string source) {
	size_t startIndex = GetStartOfLineIndex(position, source);
	return position - startIndex;
}


size_t GetEndOfLineIndex(size_t start, std::string source) {
	size_t endIndex = start;
	while (source[endIndex] != '\n' && endIndex < source.length())
		endIndex++;
	return endIndex;
}


std::string GetLine(size_t start, std::string source) {
	size_t startIndex = GetStartOfLineIndex(start, source);
	size_t endIndex = GetEndOfLineIndex(start, source);
	return source.substr(startIndex, endIndex - startIndex);
}


size_t VariableTab(std::string text, size_t size) {
	size_t length = text.length();
	if (length >= size) {
		return 0;
	}
	return size - length;
}


std::string ReplaceTabsWithSpaces(std::string linestr, int tabSize = 4) {
	std::string out;
	int outIndex = 0;
	for (int index = 0; index < linestr.length(); index++) {
		if (linestr[index] == '\t') {
			int remainder = outIndex % tabSize;
			int tsize = tabSize - remainder;
			out += std::string(tsize, ' ');
			outIndex += tsize;
		} else {
			out += linestr[index];
			outIndex++;
		}
	}
	return out;
}
