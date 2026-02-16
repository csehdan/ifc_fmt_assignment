#pragma once

#include "ifcParser.h"

void IfcParser::InitCount()
{
	nQuotes = 0;
	nOpenParentheses = 0;
	nCloseParentheses = 0;
	nOpenBrackets = 0;
	nCloseBrackets = 0;
	nOpenCurlyBrackets = 0;
	nCloseCurlyBrackets = 0;
}

int IfcParser::ValidateQuotesEtc(bool onlyQuotes)
{
	if (nQuotes % 2 != 0)
	{
		return 1;
	}

	if (onlyQuotes)
	{
		return 0;
	}

	if (nOpenParentheses != nCloseParentheses)	
	{
		return 2;
	}

	if (nOpenBrackets != nCloseBrackets)
	{
		return 3;
	}

	if (nOpenCurlyBrackets != nCloseCurlyBrackets)
	{
		return 4;
	}

	return 0;
}

IfcParser::IfcParser(const std::string& iFile, const std::string& oFile)
{
	m_iFilePath = iFile;
	m_oFilePath = oFile;

	m_dataBlockStart = "DATA;";
	m_dataBlockEnd = "ENDSEC;";

	InitCount();
}

int IfcParser::ReadInputFile(bool ignoreEmptyLines)
{
	std::ifstream inFile(m_iFilePath);

	int retVal = 0;

	if (inFile.is_open())
	{
		std::string x="";

		auto inDataBlock = false;

		IfcBlock block(NONDATA);

		InitCount();

		while (getline(inFile, x))
		{
			if (ignoreEmptyLines && x.empty())
			{
				continue;
			}

			nQuotes += Helpers::CountOccurrences(x, '\'', true);
			nOpenParentheses += Helpers::CountOccurrences(x, '(', true);
			nCloseParentheses += Helpers::CountOccurrences(x, ')', true);
			nOpenBrackets += Helpers::CountOccurrences(x, '[', true);
			nCloseBrackets += Helpers::CountOccurrences(x, ']', true);
			nOpenCurlyBrackets += Helpers::CountOccurrences(x, '{', true);
			nCloseCurlyBrackets += Helpers::CountOccurrences(x, '}', true);

			if (inDataBlock)
			{
				if (x == m_dataBlockEnd)
				{
					inDataBlock = false;

					block.AddLine(x);
					m_blocks.push_back(block);
					block.Reset(NONDATA);
					continue;
				}
				else if (x == m_dataBlockStart)
				{
					fprintf(stderr, "Data block nonsense");
					return 1;
				}
			}
			else
			{
				if (x == m_dataBlockStart)
				{
					if (block.HasContent())
					{
						m_blocks.push_back(block);
					}

					block.Reset(DATA);
					inDataBlock = true;
				}
				//if (x == endsec) we don't handle now
			}

			block.AddLine(x);
		}

		m_blocks.push_back(block);

		int validQuotes = ValidateQuotesEtc();

		if (validQuotes > 0)
		{
			fprintf(stderr, "Quotes not terminated");
			retVal = 3;
		}
	}
	else 
	{
		fprintf(stderr, "File read error.");
		retVal = 2;
	}

	return retVal;
}

int IfcParser::Format()
{
	for (int i = 0; i < m_blocks.size(); i++)
	{
		int success = m_blocks[i].MergeLines(true);
		if (success > 0)
		{
			return 1;
		}
	}

	return 0;
}

void IfcParser::PrintConsole()
{
	auto lines = GetAllProcessedLines();

	for (const auto& line : lines)
	{
		std::cout << line << std::endl;
	}
}

void IfcParser::PrintFile(const std::string& fileName)
{
	// todo: check if file exists already
	std::ofstream oFile(fileName);
	for (const auto& line : GetAllProcessedLines())
	{
		oFile << line << std::endl;
	}

	oFile.close();
}

std::vector<std::string> IfcParser::GetAllProcessedLines()
{
	std::vector<std::string> allProcessedLines;

	for (auto& block : m_blocks)
	{
		auto lines = block.GetProcessedLines();

		for (const auto& line : lines)
		{
			allProcessedLines.push_back(line);
		}
	}
	return allProcessedLines;
}