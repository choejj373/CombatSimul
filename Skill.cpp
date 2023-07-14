#include "Skill.h"
#include <iostream>

#include "ICombatObject.h"
#include "Party.h"
#include "Object.h"
#include "commandq.h"
#include "command.h"
#include "SkillEffect.h"

Skill::Skill(int coolTimeTick)
{
    m_coolTimeTick = coolTimeTick;
    m_prevProcessTick = -1;
}

Skill::~Skill()
{
    //std::cout << "~Skill" << std::endl;
}

void Skill::updateFrame(CommandQ& cmdQ, int nowTick, Party* enemy, Party* ourTeam, Object* owner)
{
    if (m_prevProcessTick == -1 )
    {
        m_prevProcessTick = nowTick;
        process(cmdQ, m_prevProcessTick, enemy, ourTeam, owner);
    }
    else
    {
        while (nowTick >= m_prevProcessTick + m_coolTimeTick)
        {
            m_prevProcessTick += m_coolTimeTick;
            process(cmdQ, m_prevProcessTick, enemy, ourTeam, owner);
        }
    }
}

SkillDamage::SkillDamage(int coolTimeTick)
{
    m_coolTimeTick = coolTimeTick;
    m_effect = std::make_shared<SkillEffect>(0, TYPE::SUBHP, 500, TARGET_TYPE::ENEMY, 1);
}

void SkillDamage::process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner)
{
    cmdQ.push_back( processTime, new CCmdSkill(ourTeam, ourTeam, owner, m_effect));
}


SkillDamageWide::SkillDamageWide(int coolTimeTick)
{
    m_coolTimeTick = coolTimeTick;
    m_effect = std::make_shared<SkillEffect>(0, TYPE::SUBHP, 100, TARGET_TYPE::ENEMY, 5);
}

void SkillDamageWide::process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner)
{
    cmdQ.push_back(processTime, new CCmdSkill(ourTeam, ourTeam, owner, m_effect));
}


SkillHealWide::SkillHealWide(int coolTimeTick)
{
    m_coolTimeTick = coolTimeTick;
    m_effect = std::make_shared<SkillEffect>(0, TYPE::ADDHP, 100, TARGET_TYPE::ALLY, 5);
}

void SkillHealWide::process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner)
{
    cmdQ.push_back(processTime, new CCmdSkill(ourTeam, ourTeam, owner, m_effect));
}


SkillHeal::SkillHeal(int coolTimeTick)
{
    m_coolTimeTick = coolTimeTick;
    m_effect = std::make_shared<SkillEffect>(0, TYPE::ADDHP, 300, TARGET_TYPE::ALLY, 1 );
}

void SkillHeal::process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner)
{
    cmdQ.push_back(processTime, new CCmdSkill(ourTeam, ourTeam, owner, m_effect));
}
