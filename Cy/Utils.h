#pragma once
#include <string>



/**
 * @brief Get the index of the start of the line.
 * @param start Index from start of file.
 * @param source Text of file.
 * @return Index of end of line.
*/
size_t GetStartOfLineIndex(size_t start, std::string source);

/**
 * @brief Return index from start of the line.
 * @param position Offset from start of text
 * @param source Text
 * @return Index
*/
size_t GetLineIndex(size_t position, std::string source);

/**
 * @brief Get the index of the end of the line.
 * @param start Index from start of file.
 * @param source Text of file.
 * @return Index of end of line.
*/
size_t GetEndOfLineIndex(size_t start, std::string source);

/**
 * @brief Return line containing the index at file fileOffset start in source.
 * @param start Index from start of file.
 * @param source Text of file.
 * @return String of text of full line.
*/
std::string GetLine(size_t start, std::string source);

/**
 * @brief Return number of spaces equal to tab of size after text.
 * @param text Text before tab
 * @param size Tab size
 * @return Amount of spaces t5o equal the next tab space.
*/
size_t VariableTab(std::string text, size_t size);

/**
 * @brief Convert tabs to spaces.
 * @param linestr String to convert.
 * @param tabSize Tab size to use.
 * @return string with spaces instead of tabs.
*/
std::string ReplaceTabsWithSpaces(std::string linestr, int tabSize = 4);
