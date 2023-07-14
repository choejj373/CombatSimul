#include "CommandQ.h"
#include <algorithm>
#include <tuple>

static bool CompareTime(std::tuple<int, Command*>& v1, std::tuple<int, Command* >& v2)
{
	return get<0>(v1) < get<0>(v2);//tuple 0번째 값으로 비교

}

void CommandQ::push_back(int execTime, Command* cmd) 
{ 
	m_list.push_back(std::make_tuple( execTime, cmd) ); 
}
std::tuple<int, Command*> CommandQ::front()
{
	return m_list.front(); 
}
auto CommandQ::end() 
{ 
	return m_list.end(); 
}

void CommandQ::sort()
{
	std::sort(m_list.begin(), m_list.end(), CompareTime );
}

void CommandQ::pop_front()
{
	m_list.erase( m_list.begin());
}
