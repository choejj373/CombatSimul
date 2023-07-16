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

    m_continuousEffects.clear();
    m_continuousIntervalEffects.clear();

    //std::cout << "Object::~Object" << std::endl;

}

void Object::setStat(int hp, int damage, int attackSpeed)
{
    m_loopUpdater.init(-1, attackSpeed, 0);

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
        effect->getType(),
        nowTime + effect->getContinuousTime()
    );

    if( effect->getIntervalTime() == 0 )
        m_continuousEffects.push_back(std::make_tuple( nowTime + effect->getContinuousTime(), newEffect) );
    else
        m_continuousIntervalEffects.push_back(std::make_tuple(nowTime + effect->getContinuousTime(), newEffect));

}
/// <summary>
/// </summary>
/// <param name="nowTick"></param>
void Object::updateContinuousEffect(CommandQ& cmdQ, int nowTime, Party* ally)
{
    // 주기적으로 발동되는 지속 효과 update
    for (auto it = m_continuousIntervalEffects.begin(); it != m_continuousIntervalEffects.end(); ++it)
    {
        auto effect = std::get<1>(*it);
        effect->updateFrame(cmdQ, nowTime, ally, this, m_extraStat);
    }



    for(auto it = m_continuousEffects.begin();  it != m_continuousEffects.end(); )
    {
        if (std::get<0>(*it) <= nowTime)
            it = m_continuousEffects.erase(it);
        else
            it++;
    }
    
    for(auto it = m_continuousIntervalEffects.begin(); it != m_continuousIntervalEffects.end();)
    {
        if (std::get<0>(*it) <= nowTime)
            it = m_continuousIntervalEffects.erase(it);
        else
            it++;
    }


    std::fill(m_extraStat.begin(), m_extraStat.end(), 0);
    // stat up등의 지속 효과 update
    for (auto it = m_continuousEffects.begin(); it != m_continuousEffects.end(); ++it)
    {
        auto effect = std::get<1>(*it);
        effect->updateFrame(cmdQ, nowTime, ally, this, m_extraStat);
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

void  Object::skillEffected(int nowTime, const std::shared_ptr<SkillEffect>& effect, const std::string& ownerName)
{
    if (effect->isContinuous())// 지속 효과 일 경우
    {
        addContinuousEffect(nowTime, effect);
    }
    else// 즉시 효과 발동 일 경우
    {
        applyEffect(effect->getType(), effect->getValue(), ownerName);
    }
}