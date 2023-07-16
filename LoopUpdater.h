#pragma once
#include <functional>

class LoopUpdater
{
	int m_prevUpdateTime;
	int m_intervalTime;
	int m_expireTime;
public:
	
	LoopUpdater();
	void Update(int nowTime, const std::function<void(int)>& f);
	void init(int initUpdateTime, int intervalTime, int expireTime );
};

