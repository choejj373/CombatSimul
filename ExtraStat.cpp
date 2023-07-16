#include "ExtraStat.h"
#include "effect.h"

ExtraStat::ExtraStat()
{
	m_extraStat.resize(static_cast<size_t>(EFFECT_TYPE::MAX));
}

void ExtraStat::addValue(size_t pos, int value)
{
	m_extraStat.at(pos) += value;
}
void ExtraStat::subValue(size_t pos, int value)
{
	m_extraStat.at(pos) -= value;
}
int ExtraStat::getValue(size_t pos)
{
	return m_extraStat.at(pos);
}