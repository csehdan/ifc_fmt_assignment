#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "ifcBlock.h"

class IfcParser
{
	std::string m_iFilePath;
	std::string m_oFilePath;

	std::string m_dataBlockStart;
	std::string m_dataBlockEnd;

	std::vector<IfcBlock> m_blocks;

	int nQuotes;
	int nOpenParentheses;
	int nCloseParentheses;
	int nOpenBrackets;
	int nCloseBrackets;
	int nOpenCurlyBrackets;
	int nCloseCurlyBrackets;

	void InitCount();
	int ValidateQuotesEtc(bool onlyQuotes = true);

public:
	const decltype(m_blocks)& blocks() { return m_blocks; }

	IfcParser(const std::string& iFile, const std::string& oFile);
	int ReadInputFile(bool ignoreEmptyLines = false); //return value indicates success

	int Format();

	void PrintConsole();
	void PrintFile(const std::string& fileName);
	std::vector<std::string> GetAllProcessedLines();

};