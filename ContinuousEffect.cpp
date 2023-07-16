#include "ContinuousEffect.h"
#include <iostream>

#include "CommandQ.h"
#include "command.h"
#include "ExtraStat.h"

ContinuousEffect::ContinuousEffect(
	int continuousTime,
	int intervalTime,
	int value,
	EFFECT_TARGET_TYPE targetType,
	short targetMaxCount,
	EFFECT_TYPE type,
	int expireTime,
	const std::shared_ptr<ExtraStat>& extraStat)
{
	m_continuousTime = continuousTime;
	m_intervalTime = intervalTime;
	m_value = value;
	m_targetType = targetType;
	m_targetMaxCount = targetMaxCount;
	m_type = type;


	m_loopUpdater.init(-1, intervalTime, expireTime);

	if (m_continuousTime > 0 && m_intervalTime == 0)
	{
		m_extraStat = extraStat;
		m_extraStat->addValue(static_cast<size_t>(m_type), m_value);
	}
	//std::cout << "ContinuousEffect::ContinuousEffect" << std::endl;
}
ContinuousEffect::~ContinuousEffect()
{
	if( m_extraStat.get() != nullptr )
		m_extraStat->subValue(static_cast<size_t>(m_type), m_value);

	//std::cout << "ContinuousEffect::~ContinuousEffect" << std::endl;
}
void ContinuousEffect::updateFrame(CommandQ& cmdQ, int nowTime, Party* ally, Object* owner )
{
	if (m_intervalTime > 0)
	{
		std::shared_ptr<ContinuousEffect> sharedPtr = shared_from_this();
		m_loopUpdater.Update(nowTime, [&](int time) {
			cmdQ.push_back(time, new CCmdEffect(sharedPtr, owner, ally));
			});
	}
}