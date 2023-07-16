#pragma once
#include <vector>
#include "effect.h"
/// <summary>
/// Skill �ߵ��� ���� ��Ÿ���� ȿ�� Class
/// </summary>
class SkillEffect
{
protected:
	int					m_continuousTime;	// ���� �ð�, 0 �̸� ��� �ߵ�
	EFFECT_TYPE			m_type;				// HP ADD(��), HP SUB(����)
	int					m_value;			// ���� ��

	EFFECT_TARGET_TYPE	m_targetType;		// �ڱ� �ڽ�, �Ʊ�, ��
	short				m_targetMaxCount;	// �ִ� ���� ��
	short				m_findTargetType;	//? ���� �����, ü���� ���� ����, ���ݷ��� ���� ���� ��;

protected://������ ��ų ȿ���� �ֱ��� �ߵ��Ǵ� effect�� ���� ����(��: dot��)
	int					m_intervalTime;					// ���� ȿ���� �ֱ������� �ߵ��Ǵ� ȿ���� ��� �ֱ� �ð�
	EFFECT_TARGET_TYPE	m_continuousTargetType;			// ������ ��ųȿ���� ��� Ÿ�� ���(����� self ����)
	//short				m_continuousTargetMaxCount;		// 
	//short				m_continuousFindTargetType;;	//? ���� �����, ü���� ���� ����, ���ݷ��� ���� ���� ��;

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

