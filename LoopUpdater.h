#pragma once
#include <functional>

class LoopUpdater
{
	int m_prevUpdateTime;
	int m_intervalTime;
public:
	
	LoopUpdater();
	void Update(int nowTime, const std::function<void(int)>& f);
	void init(int initUpdateTime, int intervalTime);
};

