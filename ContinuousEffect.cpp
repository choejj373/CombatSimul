#include "ContinuousEffect.h"
#include <iostream>

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

	m_loopUpdater.init(-1, intervalTime);

	//std::cout << "ContinuousEffect::ContinuousEffect" << std::endl;
}
ContinuousEffect::~ContinuousEffect()
{
	//std::cout << "ContinuousEffect::~ContinuousEffect" << std::endl;
}
void ContinuousEffect::updateFrame(CommandQ& cmdQ, int nowTime, Party* ally, Object* owner)
{
	std::shared_ptr<ContinuousEffect> sharedPtr = shared_from_this();
	m_loopUpdater.Update(nowTime, [&](int time) {
		cmdQ.push_back(time, new CCmdEffect(sharedPtr, owner, ally));
	});
}