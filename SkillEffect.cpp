#include "SkillEffect.h"
#include <memory>
SkillEffect::SkillEffect()
{
	m_intervalTime		= 0;
	m_findTargetType	= 0;
	m_continuousTime	= 0;

	m_type				= EFFECT_TYPE::INVALID;		// HP ADD(��), HP SUB(����)
	m_value				= 0;					// ���� ��
	m_targetType		= EFFECT_TARGET_TYPE::INVALID;	// �ڱ� �ڽ�, �Ʊ�, ��
	m_targetMaxCount	= 0;					// 
}

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

bool SkillEffect::updateFrame(std::vector<int>& values, int nowTime)
{
	if (values.size() < static_cast<short>(m_type) + 1)
		return false;

	values[static_cast<short>(m_type)] += m_value;
	return true;
}

