#pragma once
#include <sstream>
#include <regex>
#include <stack>


static class Helpers
{
public:
	static int CountOccurrences(const std::vector<std::string>& lines, char oc, bool excludeEscaped);
	static int CountOccurrences(const std::string& line, char oc, bool excludeEscaped);

	static std::string RemoveUnquotedWhitespaceExplicit(const std::string& s);
	static inline bool IsParenthese(const char& c) 
	{
		return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
	}
	static std::string CollectUnquotedParentheses(const std::string& s);
	static bool AreParenthesesValid(const std::string& str);


};