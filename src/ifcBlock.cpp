#include "ifcBlock.h"
#pragma once

const std::vector<std::string> IfcBlock::GetProcessedLines()
{
	std::vector<std::string> lines;
	lines.push_back(m_blockStart);

	if (m_allLinesMerged.empty())
	{
		lines.insert(lines.end(), m_allLines.begin(), m_allLines.end());
	}
	else
	{
		lines.insert(lines.end(), m_allLinesMerged.begin(), m_allLinesMerged.end());
	}

	lines.push_back(m_blockEnd);

	return lines;
}

IfcBlock::IfcBlock(blockType btype)
{
	type = btype;
}

void IfcBlock::AddLine(std::string line)
{
	m_allLines.push_back(line);
}

void IfcBlock::Reset(blockType btype/*, const std::string& start, const std::string& end*/)
{
	type = btype;
	m_blockStart = "";
	m_blockEnd = "";
	m_allLines.clear();
}

int IfcBlock::MergeLines(bool onlyDataBlocks)
{
	if (onlyDataBlocks && type != DATA)
	{
		return 0;
	}

	if (m_allLines.size() < 2)
	{
		fprintf(stderr, "Invalid or empty block. Opening/closing tag or body missing");
		return 1; // invalid block
	}

	m_blockEnd = m_allLines.back();
	m_allLines.pop_back();
	m_blockStart = m_allLines.front();
	m_allLines.erase(m_allLines.begin());

	// remove whitespaces
	for (int i = 0; i < m_allLines.size(); i++)
	{
		std::string cleaned = "";
		m_allLines[i] = Helpers::RemoveUnquotedWhitespaceExplicit(m_allLines[i]);
	}

	// construct nice DATA lines
	for (int i = 0; i < m_allLines.size(); i++)
	{
		std::regex pattern("#[0-9]+=[A-Z]+"); // #number= CAPITALWORD, could be moved to function argument, if will be used for other text blocks
		std::smatch matchResult;

		if (std::regex_search(m_allLines[i], matchResult, pattern))
		{
			m_allLinesMerged.push_back(matchResult[0]);

			std::string suffix = matchResult.suffix().str();

			std::smatch secondResult;

			if (std::regex_search(suffix, secondResult, pattern))
			{
				m_allLines.insert(m_allLines.begin() + i + 1, suffix);
				m_allLinesMerged.back() += secondResult.prefix();
			}
			else
			{
				m_allLinesMerged.back() += matchResult.suffix();
			}
		}
		else
		{
			if (!m_allLinesMerged.empty())
			{
				m_allLinesMerged.back() += m_allLines[i];
			}
			else
			{
				// probably error
			}
		}
	}

	// check line ends
	char lineEnd = ';';
	if (!AreLineEndsCorrect(lineEnd))
	{
		fprintf(stderr, "Lines should end with " + lineEnd);
		return 2;
	}

	// check parentheses
	auto par = ValidateParentheses();
	if (par > 0)
	{
		fprintf(stderr, "ccc");
		return 1;
	}

	return 0;
}

bool IfcBlock::AreLineEndsCorrect(char endChar)
{
	if (type != DATA)
	{
		return true;
	}

	for (const auto& line : m_allLinesMerged)
	{
		if (line.back() != endChar)
		{
			return false;
		}
	}

	return true;
}

int IfcBlock::ValidateParentheses()
{
	if (type != DATA)
	{
		return 0;
	}

	for (const auto& line : m_allLinesMerged)
	{
		std::string parentheses = Helpers::CollectUnquotedParentheses(line);
		bool valid = Helpers::AreParenthesesValid(parentheses);

		if (!valid)
		{
			fprintf(stderr, "wrong parentheses");
			return 1;
		}
	}

	return 0;
}

