#pragma once

#include <memory>
#include "effect.h"

class Object;
class CommandQ;
class Party;
class ContinuousEffect
{
public:


protected:
	int				m_continuousTime = 0;			// ���� �ð�, 0 �̸� ��� �ߵ�
	int				m_intervalTime = 0;				// ���� ȿ���� �ֱ������� �ߵ��Ǵ� ȿ���� ��� �ֱ� �ð�
	int				m_value = 0;					// ���� ��
	EFFECT_TYPE		m_type = EFFECT_TYPE::INVALID;			// HP ADD(��), HP SUB(����)
	int				m_prevProcessTime = -1;
	EFFECT_TARGET_TYPE	m_targetType = EFFECT_TARGET_TYPE::INVALID;
	short			m_targetMaxCount = 0;					// 

public:
	ContinuousEffect(int continuousTime, int intervalTime, int value, EFFECT_TARGET_TYPE targetType, short targetMaxCount, EFFECT_TYPE type  );

public:
	EFFECT_TARGET_TYPE	getTargetType() const { return m_targetType; }
	int			getValue() const { return m_value; }
	short		getTargetMaxCount() const { return m_targetMaxCount; }
	EFFECT_TYPE		getType() const { return m_type; }

	void	updateFrame(CommandQ& cmdQ, int nowTime, Party* ally, Object* owner, std::shared_ptr<ContinuousEffect>& effect );
};

