#include "SkillEffect.h"
#include <memory>
SkillEffect::SkillEffect()
{
	m_findTargetType	= 0;
	m_expireTime		= 0;

	m_type				= TYPE::INVALID;		// HP ADD(��), HP SUB(����)
	m_value				= 0;					// ���� ��
	m_targetType		= TARGET_TYPE::INVALID;	// �ڱ� �ڽ�, �Ʊ�, ��
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
	if (nowTime >= m_expireTime)// expire �ð��� �̸� ��� �صθ� �����ٵ��ϴ� 
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
