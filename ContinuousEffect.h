#pragma once

#include <memory>
#include "effect.h"
#include "LoopUpdater.h"

class Object;
class CommandQ;
class Party;
class ExtraStat;
class ContinuousEffect : public std::enable_shared_from_this<ContinuousEffect>
{
public:


protected:
	int				m_continuousTime = 0;			// 지속 시간, 0 이면 즉시 발동
	int				m_intervalTime = 0;				// 지속 효과중 주기적으로 발동되는 효과일 경우 주기 시간
	int				m_value = 0;					// 적용 값
	EFFECT_TYPE		m_type = EFFECT_TYPE::INVALID;			// HP ADD(힐), HP SUB(공격)
	//int				m_prevProcessTime = -1;
	EFFECT_TARGET_TYPE	m_targetType = EFFECT_TARGET_TYPE::INVALID;
	short			m_targetMaxCount = 0;					// 

	LoopUpdater					m_loopUpdater;
	std::shared_ptr<ExtraStat>	m_extraStat;
public:
	virtual ~ContinuousEffect();
	ContinuousEffect(int continuousTime, 
		int intervalTime, 
		int value, 
		EFFECT_TARGET_TYPE targetType, 
		short targetMaxCount, 
		EFFECT_TYPE type , 
		int expireTime,
		const std::shared_ptr<ExtraStat>& extraStat );

public:
	EFFECT_TARGET_TYPE	getTargetType() const { return m_targetType; }
	int					getValue() const { return m_value; }
	short				getTargetMaxCount() const { return m_targetMaxCount; }
	EFFECT_TYPE			getType() const { return m_type; }

	void				updateFrame(CommandQ& cmdQ, int nowTime, Party* ally, Object* owner );
};

