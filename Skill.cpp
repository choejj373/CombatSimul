#include "Skill.h"
#include "ICombatObject.h"
#include "Party.h"
#include "Object.h"
#include <iostream>
#include "commandq.h"
#include "command.h"

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



void SkillDamage::process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner)
{
    //std::string name = owner->getName() + "(Skill)";

    cmdQ.push_back( processTime, new CCmdDamage( enemy, owner, 500 ));
    //enemy->damaged(500, name );
    //std::cout << owner->getName() << "(skill) is attack" << "(500) " <<  "to " << enemy->getName();
}


void SkillDamageWide::process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner)
{
    //std::string name = owner->getName() + "(Skill)";
    //enemy->damagedAll(100, name);
    cmdQ.push_back(processTime, new CCmdDamageWide(enemy, owner, 100));
    //std::cout << owner->getName() << "(skill) is attackWide" << "(100) " << "to " << enemy->getName();
}

void SkillHeal::process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner)
{
    //std::string name = owner->getName() + "(Skill)";
    //owner->getParty()->heal(300, name );
    cmdQ.push_back(processTime, new CCmdHeal( ourTeam, owner, 300));
    //std::cout << owner->getName() << "(skill) is heal"  << "(300) " << "to " << owner->getName();
}

void SkillHealWide::process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner)
{
    //std::string name = owner->getName() + "(Skill)";
    //owner->getParty()->healAll(100, name);
    cmdQ.push_back(processTime, new CCmdHealWide( ourTeam, owner, 100));
    //std::cout << owner->getName() << "(skill) is healWide" << "(100) " << " to " << owner->getName();
}


