#pragma once
#include <sstream>
#include <regex>
#include <stack>
//#include <boost/regex.hpp>


static class Helpers
{
public:
	static inline void RemoveWhitespace(std::string& s)
	{
		s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
	}

	static inline std::string RemoveWhitespaceConst(const std::string& str)
	{
		auto s = str;
		s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
		return s;
	}

	static int CountOccurrences(const std::vector<std::string>& lines, char oc, bool excludeEscaped);
	static int CountOccurrences(const std::string& line, char oc, bool excludeEscaped);

	static std::string Helpers::RemoveWhitespaces(const std::string& s);

	static std::string RemoveUnquotedWhitespaceExplicit(const std::string& s);
	static inline bool IsParenthese(const char& c) 
	{
		return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
	}
	static std::string CollectUnquotedParentheses(const std::string& s);
	static bool AreParenthesesValid(const std::string& str);


};