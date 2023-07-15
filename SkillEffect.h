#pragma once
#include <vector>
#include "effect.h"

class SkillEffect
{
public:
	

protected:
	int					m_continuousTime	= 0;					// 지속 시간, 0 이면 즉시 발동
	EFFECT_TYPE			m_type				= EFFECT_TYPE::INVALID;		// HP ADD(힐), HP SUB(공격)

	int					m_value				= 0 ;					// 적용 값

	EFFECT_TARGET_TYPE	m_targetType		= EFFECT_TARGET_TYPE::INVALID;	// 자기 자신, 아군, 적
	short				m_targetMaxCount	= 0;					// 
	
	
	short				m_findTargetType = 0;;	//? 가장 가까운, 체력이 가장 적은, 공격력이 가장 높은 등;

protected://지속형 스킬 효과중 주기적 발동되는 effect에 대한 값들(예: dot등)
	int					m_intervalTime = 0;									// 지속 효과중 주기적으로 발동되는 효과일 경우 주기 시간
	EFFECT_TARGET_TYPE	m_continuousTargetType = EFFECT_TARGET_TYPE::SELF;	// 지속형 스킬효과일 경우 타겟 대상(현재는 self 고정)
	//short				m_continuousTargetMaxCount = 0;						// 
	//short				m_continuousFindTargetType = 0;;					//? 가장 가까운, 체력이 가장 적은, 공격력이 가장 높은 등;

public:
	SkillEffect();
	SkillEffect(int continuousTime, 
		EFFECT_TYPE type, 
		int value, 
		EFFECT_TARGET_TYPE targetType, 
		short targetMaxCount, 
		int intervalTime = 0 );

	int					getValue() const { return m_value; }
	EFFECT_TYPE			getType() const { return m_type; }
	EFFECT_TARGET_TYPE	getTargetType() const { return m_targetType; }
	short				getTargetMaxCount() const { return m_targetMaxCount; }
	int					getContinuousTime() { return m_continuousTime; }
	int					getIntervalTime() const { return m_intervalTime; }
	EFFECT_TARGET_TYPE	getContinuousTargetType() const { return m_continuousTargetType; }

	bool isContinuous() const { return (m_continuousTime == 0) ? false : true; }

public: 
	//지속 효과일 경우 Object에서 호출하는 함수
	bool updateFrame(std::vector<int>& values, int nowTime);

};

