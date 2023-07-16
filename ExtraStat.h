#pragma once
#include <vector>
class ExtraStat
{
	std::vector<int>    m_extraStat;
public:
	ExtraStat();

	void addValue(size_t pos, int value);
	void subValue(size_t pos, int value);
	int getValue(size_t pos);
};

