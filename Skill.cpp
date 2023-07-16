#include "Skill.h"
#include <iostream>


#include "Party.h"
#include "Object.h"
#include "commandq.h"
#include "command.h"
#include "SkillEffect.h"

Skill::Skill(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick, 0);
}

Skill::~Skill()
{
    //std::cout << "~Skill" << std::endl;
}

void Skill::updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner)
{
    m_loopUpdater.Update(nowTime, [&](int time) {
        cmdQ.push_back(time, new CCmdSkill(enemy, ourTeam, owner, m_effect));
        });
}

SkillDamage::SkillDamage(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick, 0);
    m_effect = std::make_shared<SkillEffect>(0, EFFECT_TYPE::SUBHP, 400, EFFECT_TARGET_TYPE::ENEMY, 1);
}

SkillDamageWide::SkillDamageWide(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick, 0);
    m_effect = std::make_shared<SkillEffect>(0, EFFECT_TYPE::SUBHP, 150, EFFECT_TARGET_TYPE::ENEMY, 5);
}



SkillHealWide::SkillHealWide(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick,0);
    m_effect = std::make_shared<SkillEffect>(0, EFFECT_TYPE::ADDHP, 150, EFFECT_TARGET_TYPE::ALLY, 5);
}


SkillHeal::SkillHeal(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick,0);
    m_effect = std::make_shared<SkillEffect>(0, EFFECT_TYPE::ADDHP, 300, EFFECT_TARGET_TYPE::ALLY, 1 );
}

SkillHealDot::SkillHealDot(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick,0);
    m_effect = std::make_shared<SkillEffect>(5000, EFFECT_TYPE::ADDHP, 200, EFFECT_TARGET_TYPE::ALLY, 1, 1000);
}

SkillDamageDot::SkillDamageDot(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick,0);
    m_effect = std::make_shared<SkillEffect>(7000, EFFECT_TYPE::SUBHP, 100, EFFECT_TARGET_TYPE::ENEMY, 1, 1000);
}

SkillAtkUp::SkillAtkUp(int coolTimeTick)
{
    m_loopUpdater.init(-1, coolTimeTick,0);
    m_effect = std::make_shared<SkillEffect>(5000, EFFECT_TYPE::ATKUP, 100, EFFECT_TARGET_TYPE::ALLY, 1, 0);
}