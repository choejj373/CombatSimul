#pragma once
#include <vector>
class Command;
class CommandQ
{
	std::vector<std::tuple<int,Command*>> m_list;
public:
	CommandQ() { m_list.reserve(100); }
	void push_back(int execTime, Command* cmd);
	std::tuple<int, Command*> front();
	auto end();
	void sort();
	void pop_front();
	size_t size() { return m_list.size(); }
	std::tuple<int, Command*> at(size_t index) { return m_list.at(index); }
	void clear() { m_list.clear(); }

	
};