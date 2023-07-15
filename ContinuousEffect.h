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
	int				m_continuousTime = 0;			// 지속 시간, 0 이면 즉시 발동
	int				m_intervalTime = 0;				// 지속 효과중 주기적으로 발동되는 효과일 경우 주기 시간
	int				m_value = 0;					// 적용 값
	EFFECT_TYPE		m_type = EFFECT_TYPE::INVALID;			// HP ADD(힐), HP SUB(공격)
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

