#include "Party.h"
#include <algorithm>
#include <iostream>
#include "Object.h"
Party::~Party()
{
    for (auto member : m_memberList)
        delete member;

    m_memberList.clear();

   // std::cout << "~Party" << std::endl;
}

void Party::damagedAll(int damage, std::string& attacker)
{
    std::for_each(m_memberList.begin(), m_memberList.end(), [&](Object* obj)->void {
        obj->damaged(damage, attacker); });
}
void Party::healAll(int hp, std::string& healer)
{
    std::for_each(m_memberList.begin(), m_memberList.end(), [&](Object* obj)->void {
        obj->heal( hp , healer); });
}
bool Party::damaged(int damage, std::string& attacker)
{
    for (auto member : m_memberList)
    {
        if (member->damaged(damage, attacker ))
            return true;
    }
    return false;


}

bool Party::heal(int _hp, std::string& healer)
{
    for (auto member : m_memberList)
    {
        if (member->heal(_hp, healer))
            return true;
    }
    return false;
}

int Party::getHp()
{
    int hp = 0;
    std::for_each(m_memberList.begin(), m_memberList.end(), [&](Object* obj)->void {
        hp += obj->getHp(); });
    return hp;
}

bool Party::isDead()
{
    for (auto member : m_memberList )
    {
        if ( !member->isDead()) {
            return false;
        }
    };
    return true;
}

void Party::addMember( Object* member) {
    m_memberList.push_back(member);
}

void Party::updateFrame(CommandQ& cmdQ, int nowTick, Party* enemy) {
    std::for_each(m_memberList.begin(), m_memberList.end(), [&](Object* obj)->void {
        obj->updateFrame( cmdQ, nowTick, enemy, this ); });
}