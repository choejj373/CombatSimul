#include "Party.h"
#include <algorithm>
#include <iostream>
#include "Object.h"
#include "SkillEffect.h"

Party::~Party()
{
    for (auto member : m_memberList)
        delete member;

    m_memberList.clear();

   // std::cout << "~Party" << std::endl;
}

void Party::damagedAll(int damage, const std::string& attacker)
{
    std::for_each(m_memberList.begin(), m_memberList.end(), [&](Object* obj)->void {
        obj->damaged(damage, attacker); });
}
void Party::healAll(int hp, const std::string& healer)
{
    std::for_each(m_memberList.begin(), m_memberList.end(), [&](Object* obj)->void {
        obj->heal( hp , healer); });
}
bool Party::damaged(int damage, const std::string& attacker)
{
    for (auto member : m_memberList)
    {
        if (member->damaged(damage, attacker ))
            return true;
    }
    return false;


}

bool Party::heal(int _hp, const std::string& healer)
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

void Party::skillEffected(const std::shared_ptr<SkillEffect>& effect, const std::string& ownerName){
    if (effect->isContinuous())// 지속 효과 일 경우
    {
        // effect에 정의된 findTargetType에 따라서 타겟을 찾아 effect를 넣어준다.
        // effect shared_ptr 써야 될듯;; 여러곳에서 참조한다.
    }
    else// 즉시 효과 발동 일 경우
    {
        // effect->getFindTargetType()에 따라서 별도로 Target을 찾아야 한다.
        int i = 0;
        for ( auto iter = m_memberList.begin(); i < effect->getTargetMaxCount() && iter != m_memberList.end() ; ++i, ++iter)
        {
            switch (effect->getType())
            {
            case TYPE::ADDHP:
                (*iter)->heal(effect->getValue(), ownerName);
                break;
            case TYPE::SUBHP:
                (*iter)->damaged(effect->getValue(), ownerName);
                break;
            default:
                break;
            }
        }
    }
}