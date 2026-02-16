#pragma once

#include "helpers.h"

int Helpers::CountOccurrences(const std::vector<std::string>& lines, char oc, bool excludeEscaped)
{
	int count = 0;

	for (int i = 0; i < lines.size(); i++)
	{
		count += CountOccurrences(lines[i], oc, excludeEscaped);
	}

	return count;
}

int Helpers::CountOccurrences(const std::string& line, char oc, bool excludeEscaped)
{
	int count = 0;

	for (std::string::size_type i = 0; i < line.size(); ++i)
	{
		if (line[i] == oc)
		{
			if (excludeEscaped)
			{
				if (i == 0 || (i > 0 && line[i - 1] != '\\'))
				{
					count++;
				}
			}
			else
			{
				count++;
			}
		}
	}

	return count;
}

std::string Helpers::RemoveWhitespaces(const std::string& str)
{
	// https://regex101.com/r/wC6gZ2/1

	//std::regex pattern("\'\.*\'");
	std::regex pattern("\'\[^']*\'");
	//std::regex pattern("[^\\]\'[^']*[^\\]\'"); // don't undestand why [^'] does the job instead of \. Why will a contained ' not triggered as closing quote

	std::smatch matchResult;
	std::string gec = regex_replace(str, pattern, "");
	std::regex_search(str, matchResult, pattern);
	return gec;
//	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
}

std::string Helpers::RemoveUnquotedWhitespaceExplicit(const std::string& s)
{
	std::string result;
	char quote = '\'';

	if (s.length() > 1)
	{
		bool withinQuotes = s[0] == quote; // this will turn false for a moment in the case of escaped quote (''), but that doesn't make the result less correct.
		result += s[0];

		for (std::string::size_type i = 1; i < s.size(); ++i)
		{
			if (withinQuotes || (!withinQuotes && !std::isspace(s[i])))
			{
				result += s[i];
			}

			if (s[i] == quote)
			{
				withinQuotes = !withinQuotes;
			}
		}
	}

	return result;
}

std::string Helpers::CollectUnquotedParentheses(const std::string& s)
{
	std::string result;
	char quote = '\'';

	if (s.length() > 1)
	{
		bool withinQuotes = s[0] == quote; // this will turn false for a moment in the case of escaped quote (''), 
											// but that doesn't make the result less correct as long as those strings are not extracted

		for (std::string::size_type i = 0; i < s.size(); ++i)
		{
			if (!withinQuotes && IsParenthese(s[i]))
			{
				result += s[i];
			}

			if (s[i] == quote)
			{
				withinQuotes = !withinQuotes;
			}
		}
	}

	return result;
}

bool Helpers::AreParenthesesValid(const std::string& s)
{
	std::stack<char> st;

	//if (s.length() % 2 != 0)
	//{
	//	return false;
	//}

	for (auto ch : s)
	{
		if (ch == '(' || ch == '[')
		{
			st.push(ch);
		}
		else if (ch == ')') 
		{
			if (st.empty() || st.top() != '(')
			{
				return false;
			}

			st.pop();
		}
		else if (ch == ']')
		{
			if (st.empty() || st.top() != '[')
			{
				return false;
			}

			st.pop();
		}
	}

	return st.empty();
}

