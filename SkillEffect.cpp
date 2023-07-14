#include "SkillEffect.h"
#include <memory>
SkillEffect::SkillEffect()
{
	m_findTargetType	= 0;
	m_expireTime		= 0;

	m_type				= TYPE::INVALID;		// HP ADD(힐), HP SUB(공격)
	m_value				= 0;					// 적용 값
	m_targetType		= TARGET_TYPE::INVALID;	// 자기 자신, 아군, 적
	m_targetMaxCount	= 0;					// 
}
SkillEffect::SkillEffect(int expireTime, TYPE type, int value, TARGET_TYPE targetType, short targetMaxCount)
{
	m_findTargetType	= 0;
	m_expireTime		= expireTime;
	m_type				= type;
	m_value				= value;
	m_targetType		= targetType;
	m_targetMaxCount	= targetMaxCount;
}

bool SkillEffect::isExpired(int nowTime)
{
	if (nowTime >= m_expireTime)// expire 시간을 미리 계산 해두면 좋을텐데일단 
		return true;

	return false;
}

bool SkillEffect::updateFrame(std::vector<int>& values, int nowTime)
{
	if (isExpired(nowTime))
		return false;

	if (values.size() < static_cast<short>(m_type) + 1)
		return false;

	values[static_cast<short>(m_type)] += m_value;
	return true;
}
