#include "SkillEffect.h"
#include <memory>

SkillEffect::SkillEffect(int continuousTime, EFFECT_TYPE type, int value, EFFECT_TARGET_TYPE targetType, short targetMaxCount, int intervalTime)
{
	m_intervalTime		= intervalTime;
	m_findTargetType	= 0;
	m_continuousTime	= continuousTime;
	m_type				= type;
	m_value				= value;
	m_targetType		= targetType;
	m_targetMaxCount	= targetMaxCount;
}

