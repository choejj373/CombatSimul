#pragma once
#include <vector>
// Game Object�� Ư�� ȿ���� �ο� �ϴ� Ŭ����
class Effect
{
	int		m_expireTime;
	short	m_type;			// ����, ���, ���, ����, ü��, 
	int     m_value;		// ���� ��

public:
	Effect(int expireTime, short type, int value) 
	{
		m_expireTime	= expireTime;
		m_type			= type;
		m_value			= value;
	}

	bool isExpired(int nowTime)
	{ 
		if (nowTime >= m_expireTime)
			return true;

		return false;
	}

	bool updateFrame(std::vector<int>& values, int nowTime)
	{
		if (isExpired(nowTime))
			return false;

		if (values.size() < m_type)
			return false;

		values[m_type - 1] += m_value;
		return true;
	}

};

