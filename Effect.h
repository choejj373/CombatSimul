#pragma once
#include <vector>
// Game Object에 특정 효과를 부여 하는 클래스
class Effect
{
	int		m_expireTime;
	short	m_type;			// 공업, 방업, 방깍, 공깍, 체업, 
	int     m_value;		// 적용 값

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

