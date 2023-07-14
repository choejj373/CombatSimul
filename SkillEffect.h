#pragma once
#include <vector>
// Game Object에 특정 효과를 부여 하는 클래스
enum class TYPE : short {
	INVALID = -1,
	ADDHP,
	SUBHP,
	MAX
};

enum class TARGET_TYPE : short {
	INVALID = -1,
	SELF,
	ALLY,
	ENEMY,
};

class SkillEffect
{
protected:
	int			m_expireTime		= 0;					// 지속 시간, 0 이면 즉시 발동
	TYPE		m_type				= TYPE::INVALID;		// HP ADD(힐), HP SUB(공격)
	int			m_value				= 0 ;					// 적용 값
	TARGET_TYPE	m_targetType		= TARGET_TYPE::INVALID;	// 자기 자신, 아군, 적
	short		m_targetMaxCount	= 0;					// 
	
	
	short		m_findTargetType = 0;;	//? 가장 가까운, 체력이 가장 적은, 공격력이 가장 높은 등;
	
	

public:
	SkillEffect();
	SkillEffect(int expireTime, TYPE type, int value, TARGET_TYPE targetType, short targetMaxCount );

	bool isExpired(int nowTime);

	int  getValue() const { return m_value; }
	TYPE getType() const { return m_type; }
	TARGET_TYPE	getTargetType() const { return m_targetType; }
	short getTargetMaxCount() const { return m_targetMaxCount; }

	bool isContinuous() const { return (m_expireTime == 0) ? false : true; }

public: 
	//지속 효과일 경우 Object에서 호출하는 함수
	bool updateFrame(std::vector<int>& values, int nowTime);

};

