#include "LoopUpdater.h"


LoopUpdater::LoopUpdater()
{
	m_prevUpdateTime = -1;
	m_intervalTime = 0;
	m_expireTime = 0;
}

void LoopUpdater::init(int initUpdateTime, int intervalTime, int expireTime )
{
	m_prevUpdateTime	= initUpdateTime;
	m_intervalTime		= intervalTime;
	m_expireTime		= expireTime;
}
void LoopUpdater::Update(int nowTime, const std::function<void(int)>& f)
{
	if (m_intervalTime > 0)
	{
		if (m_prevUpdateTime == -1)
		{
			m_prevUpdateTime = nowTime;
			f(m_prevUpdateTime);
		}
		else
		{
			while (nowTime >= m_prevUpdateTime + m_intervalTime)
			{
				m_prevUpdateTime += m_intervalTime;
				if ( m_expireTime > 0 && m_prevUpdateTime > m_expireTime)
					break;
				f(m_prevUpdateTime);
			}
		}
	}
}
