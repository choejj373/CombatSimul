#pragma once
#include <vector>
#include "effect.h"

class SkillEffect
{
public:
	

protected:
	int					m_continuousTime	= 0;					// ���� �ð�, 0 �̸� ��� �ߵ�
	EFFECT_TYPE			m_type				= EFFECT_TYPE::INVALID;		// HP ADD(��), HP SUB(����)

	int					m_value				= 0 ;					// ���� ��

	EFFECT_TARGET_TYPE	m_targetType		= EFFECT_TARGET_TYPE::INVALID;	// �ڱ� �ڽ�, �Ʊ�, ��
	short				m_targetMaxCount	= 0;					// 
	
	
	short				m_findTargetType = 0;;	//? ���� �����, ü���� ���� ����, ���ݷ��� ���� ���� ��;

protected://������ ��ų ȿ���� �ֱ��� �ߵ��Ǵ� effect�� ���� ����(��: dot��)
	int					m_intervalTime = 0;									// ���� ȿ���� �ֱ������� �ߵ��Ǵ� ȿ���� ��� �ֱ� �ð�
	EFFECT_TARGET_TYPE	m_continuousTargetType = EFFECT_TARGET_TYPE::SELF;	// ������ ��ųȿ���� ��� Ÿ�� ���(����� self ����)
	//short				m_continuousTargetMaxCount = 0;						// 
	//short				m_continuousFindTargetType = 0;;					//? ���� �����, ü���� ���� ����, ���ݷ��� ���� ���� ��;

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
	//���� ȿ���� ��� Object���� ȣ���ϴ� �Լ�
	bool updateFrame(std::vector<int>& values, int nowTime);

};

