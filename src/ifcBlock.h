#pragma once

#include <iostream>
#include <vector>
#include <regex>
#include "helpers.h"


enum blockType { DATA, NONDATA };

class IfcBlock
{
	// lines string could be replaced by a structured record
	std::vector<std::string> m_allLines;
	std::vector<std::string> m_allLinesMerged;
	std::string m_blockStart;
	std::string m_blockEnd;
	
public:
	const std::vector<std::string> GetProcessedLines(); //{ return m_allLinesMerged.empty() ? m_allLines : m_allLinesMerged; }

	blockType type;

	IfcBlock(blockType btype);
	//IfcBlock(const std::string &start, const std::string &end);
	void AddLine(std::string line);
	bool inline HasContent() { return !m_allLines.empty(); }
	void Reset(blockType btype/*, const std::string& start, const std::string& end*/);
	int MergeLines(bool onlyDataBlocks);
	bool AreLineEndsCorrect(char endChar);
	int ValidateParentheses();

};