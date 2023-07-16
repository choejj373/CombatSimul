#include "LoopUpdater.h"


LoopUpdater::LoopUpdater()
{
	m_prevUpdateTime = -1;
	m_intervalTime = 0;
}

void LoopUpdater::init(int initUpdateTime, int intervalTime)
{
	m_prevUpdateTime = initUpdateTime;
	m_intervalTime = intervalTime;
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
				f(m_prevUpdateTime);
			}
		}
	}
}
