#include "Skill.h"
#include <iostream>


#include "Party.h"
#include "Object.h"
#include "commandq.h"
#include "command.h"
#include "SkillEffect.h"

Skill::Skill(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick);
}

Skill::~Skill()
{
    //std::cout << "~Skill" << std::endl;
}


SkillDamage::SkillDamage(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick);
    m_effect = std::make_shared<SkillEffect>(0, EFFECT_TYPE::SUBHP, 400, EFFECT_TARGET_TYPE::ENEMY, 1);
}

void SkillDamage::updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner)
{
    m_loopUpdater.Update(nowTime, [&](int time) {
        cmdQ.push_back( time, new CCmdSkill(enemy, ourTeam, owner, m_effect));
    });
}


SkillDamageWide::SkillDamageWide(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick);
    m_effect = std::make_shared<SkillEffect>(0, EFFECT_TYPE::SUBHP, 150, EFFECT_TARGET_TYPE::ENEMY, 5);
}

void SkillDamageWide::updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner)
{
    m_loopUpdater.Update(nowTime, [&](int time) {
        cmdQ.push_back(time, new CCmdSkill(enemy, ourTeam, owner, m_effect));
        });
}


SkillHealWide::SkillHealWide(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick);
    m_effect = std::make_shared<SkillEffect>(0, EFFECT_TYPE::ADDHP, 150, EFFECT_TARGET_TYPE::ALLY, 5);
}

void SkillHealWide::updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner)
{
    m_loopUpdater.Update(nowTime, [&](int time) {
        cmdQ.push_back(time, new CCmdSkill(ourTeam, ourTeam, owner, m_effect));
        });
}

SkillHeal::SkillHeal(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick);
    m_effect = std::make_shared<SkillEffect>(0, EFFECT_TYPE::ADDHP, 300, EFFECT_TARGET_TYPE::ALLY, 1 );
}

void SkillHeal::updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner)
{
    m_loopUpdater.Update(nowTime, [&](int time) {
        cmdQ.push_back(time, new CCmdSkill(ourTeam, ourTeam, owner, m_effect));
        });
}


SkillHealDot::SkillHealDot(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick);
    m_effect = std::make_shared<SkillEffect>(5000, EFFECT_TYPE::ADDHP, 200, EFFECT_TARGET_TYPE::ALLY, 1, 1000);
}

void SkillHealDot::updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner)
{
    m_loopUpdater.Update(nowTime, [&](int time) {
        cmdQ.push_back(time, new CCmdSkill(ourTeam, ourTeam, owner, m_effect));
        });
}


SkillDamageDot::SkillDamageDot(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick);
    m_effect = std::make_shared<SkillEffect>(7000, EFFECT_TYPE::SUBHP, 100, EFFECT_TARGET_TYPE::ENEMY, 1, 1000);
}

void SkillDamageDot::updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner)
{
    m_loopUpdater.Update(nowTime, [&](int time) {
        cmdQ.push_back(time, new CCmdSkill(enemy, ourTeam, owner, m_effect));
        });
}
