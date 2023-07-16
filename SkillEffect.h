#pragma once
#include <vector>
#include "effect.h"
/// <summary>
/// Skill 발동시 실제 나타나는 효과 Class
/// </summary>
class SkillEffect
{
protected:
	int					m_continuousTime;	// 지속 시간, 0 이면 즉시 발동
	EFFECT_TYPE			m_type;				// HP ADD(힐), HP SUB(공격)
	int					m_value;			// 적용 값

	EFFECT_TARGET_TYPE	m_targetType;		// 자기 자신, 아군, 적
	short				m_targetMaxCount;	// 최대 적용 수
	short				m_findTargetType;	//? 가장 가까운, 체력이 가장 적은, 공격력이 가장 높은 등;

protected://지속형 스킬 효과중 주기적 발동되는 effect에 대한 값들(예: dot등)
	int					m_intervalTime;					// 지속 효과중 주기적으로 발동되는 효과일 경우 주기 시간
	EFFECT_TARGET_TYPE	m_continuousTargetType;			// 지속형 스킬효과일 경우 타겟 대상(현재는 self 고정)
	//short				m_continuousTargetMaxCount;		// 
	//short				m_continuousFindTargetType;;	//? 가장 가까운, 체력이 가장 적은, 공격력이 가장 높은 등;

public:
	SkillEffect(
		int continuousTime, 
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


};

