#include "Object.h"
#include <algorithm>
#include <iostream>


#include "Party.h"
#include "Skill.h"
#include "commandq.h"
#include "command.h"
#include "SkillEffect.h"
#include "ContinuousEffect.h"
#include "effect.h"
Object::Object( const char* name)
{
    m_prevAttackTick = -1;
    m_hp = 0;

    m_damage = 0;
    m_attackSpeed = 0;

    m_party = nullptr;

    m_name = name;

    m_extraStat.resize( static_cast<size_t>(EFFECT_TYPE::MAX));

    //std::cout << "Object::Object" << std::endl;
}
Object::~Object()
{
    for (auto skill : m_skillList)
        delete skill;

    m_skillList.clear();

    m_continuousEffectList.clear();

    //std::cout << "Object::~Object" << std::endl;

}

void Object::setStat(int hp, int damage, int attackSpeed)
{
    m_loopUpdater.init(-1, attackSpeed);

    m_hp = hp;
    m_damage = damage;
    m_attackSpeed = attackSpeed;
}

int Object::getDamage()
{
    return m_damage + m_extraStat.at( static_cast<size_t>(EFFECT_TYPE::ATKUP) );
}

void Object::updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam) {

    if (isDead())
        return;

    // m_continuousEffectList 처리
    updateContinuousEffect(cmdQ, nowTime, ourTeam );

    m_loopUpdater.Update(nowTime, [&](int time) {
            cmdQ.push_back( time, new CCmdDamage(enemy, this, getDamage()));
        });


    std::for_each(m_skillList.begin(), m_skillList.end(), [&]( Skill* skill) -> void{
        skill->updateFrame(cmdQ, nowTime, enemy, ourTeam, this);
    });
 
}

bool Object::damaged(int damage, const std::string& attacker ) {

    if (isDead()) {
        return false;
    }

    m_hp -= damage;

    std::cout << m_name <<"(hp:" << std::to_string(m_hp) << ") is Damaged(damage:" << std::to_string(damage) <<") from " << attacker << std::endl;

    if( isDead() )
        std::cout << m_name << " is Dead" << std::endl;

    return true;
}

bool Object::heal(int _hp, const std::string& healer) {
    if (isDead()) {
        return false;
    }

    m_hp += _hp;

    std::cout << getName() << "(HP:" << std::to_string(m_hp) << ") is Healed(hp:" << std::to_string(_hp) << ")  from " << healer << std::endl;
    return true;
}
/// <summary>
/// </summary>
/// <param name="effect"></param>
/// 
void Object::addContinuousEffect(int nowTime, const std::shared_ptr<SkillEffect>& effect)
{
    std::shared_ptr<ContinuousEffect> newEffect = std::make_shared<ContinuousEffect>(
        effect->getContinuousTime(),
        effect->getIntervalTime(),
        effect->getValue(),
        effect->getContinuousTargetType(),//현재 self만 적용
        1,
        effect->getType()
    );
    m_continuousEffectList.push_back(std::make_tuple( nowTime + effect->getContinuousTime(), newEffect) );
}
/// <summary>
/// 3. list를 돌면서 effect들로부터 효과값들을 누적시켜 가져와서 추가 스텟 저장 변수에 저장
/// ( 혹은 리스트를 돌때 초기화된 스텟 저장 변수를 넣어준다.
/// </summary>
/// <param name="nowTick"></param>
void Object::updateContinuousEffect(CommandQ& cmdQ, int nowTime, Party* ally)
{

    std::fill(m_extraStat.begin(), m_extraStat.end(),0);

    for (auto it = m_continuousEffectList.begin(); it != m_continuousEffectList.end(); ++it)
    {
        auto effect = std::get<1>(*it);
        effect->updateFrame(cmdQ, nowTime, ally, this, m_extraStat);
    }

    auto it = m_continuousEffectList.begin();
    while (it != m_continuousEffectList.end())
    {
        if (std::get<0>(*it) <= nowTime)
            it = m_continuousEffectList.erase(it);
        else
            it++;
    }

}


void Object::continuousEffected(std::shared_ptr<ContinuousEffect>& effect, const std::string& ownerName)
{
    applyEffect(effect->getType(), effect->getValue(), ownerName);
}

void Object::applyEffect(EFFECT_TYPE type, int value, const std::string& ownerName)
{
    switch (type)
    {
    case EFFECT_TYPE::ADDHP:
        this->heal(value, ownerName);
        break;
    case EFFECT_TYPE::SUBHP:
        this->damaged(value, ownerName);
        break;
    default:
        break;
    }
}