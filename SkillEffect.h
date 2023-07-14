#pragma once
#include <vector>
// Game Object�� Ư�� ȿ���� �ο� �ϴ� Ŭ����
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
	int			m_expireTime		= 0;					// ���� �ð�, 0 �̸� ��� �ߵ�
	TYPE		m_type				= TYPE::INVALID;		// HP ADD(��), HP SUB(����)
	int			m_value				= 0 ;					// ���� ��
	TARGET_TYPE	m_targetType		= TARGET_TYPE::INVALID;	// �ڱ� �ڽ�, �Ʊ�, ��
	short		m_targetMaxCount	= 0;					// 
	
	
	short		m_findTargetType = 0;;	//? ���� �����, ü���� ���� ����, ���ݷ��� ���� ���� ��;
	
	

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
	//���� ȿ���� ��� Object���� ȣ���ϴ� �Լ�
	bool updateFrame(std::vector<int>& values, int nowTime);

};

