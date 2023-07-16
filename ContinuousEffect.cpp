#include "ContinuousEffect.h"
#include <iostream>

#include "CommandQ.h"
#include "command.h"


ContinuousEffect::ContinuousEffect(
	int continuousTime, 
	int intervalTime, 
	int value, 
	EFFECT_TARGET_TYPE targetType, 
	short targetMaxCount, 
	EFFECT_TYPE type,
	int expireTime )
{
	m_continuousTime = continuousTime;
	m_intervalTime = intervalTime;
	m_value = value;
	m_targetType = targetType;
	m_targetMaxCount = targetMaxCount;
	m_type = type;

	m_loopUpdater.init(-1, intervalTime, expireTime);

	//std::cout << "ContinuousEffect::ContinuousEffect" << std::endl;
}
ContinuousEffect::~ContinuousEffect()
{
	//std::cout << "ContinuousEffect::~ContinuousEffect" << std::endl;
}
void ContinuousEffect::updateFrame(CommandQ& cmdQ, int nowTime, Party* ally, Object* owner, std::vector<int>& extraStat )
{
	if (m_intervalTime > 0)
	{
		std::shared_ptr<ContinuousEffect> sharedPtr = shared_from_this();
		m_loopUpdater.Update(nowTime, [&](int time) {
			cmdQ.push_back(time, new CCmdEffect(sharedPtr, owner, ally));
			});
	}
	else
	{
		extraStat.at( static_cast<size_t>(m_type) ) += getValue();
	}
}