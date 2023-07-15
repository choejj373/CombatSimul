#include "ContinuousEffect.h"
#include "CommandQ.h"
#include "command.h"

ContinuousEffect::ContinuousEffect(int continuousTime, int intervalTime, int value, EFFECT_TARGET_TYPE targetType, short targetMaxCount, EFFECT_TYPE type)
{
	m_continuousTime = continuousTime;
	m_intervalTime = intervalTime;
	m_value = value;
	m_targetType = targetType;
	m_targetMaxCount = targetMaxCount;
	m_type = type;

	m_prevProcessTime = -1;
}

void ContinuousEffect::updateFrame(CommandQ& cmdQ, int nowTime, Party* ally, Object* owner)
{
	if (m_intervalTime > 0)
	{
		if (m_prevProcessTime == -1)
		{
			m_prevProcessTime = nowTime;
			cmdQ.push_back(m_prevProcessTime, new CCmdEffect(this, owner, ally));//shared_ptr�� �������ε� this�� �� �ѱ�� �ȵ�;;
		}
		else
		{
			while (nowTime >= m_prevProcessTime + m_intervalTime)
			{
				m_prevProcessTime += m_intervalTime;
				cmdQ.push_back(m_prevProcessTime, new CCmdEffect(this, owner, ally));//shared_ptr�� �������ε� this�� �� �ѱ�� �ȵ�;;
			}
		}
	}
}