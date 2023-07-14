#include "Object.h"
#include "Party.h"
#include "Skill.h"
#include <algorithm>
#include <iostream>
#include "commandq.h"
#include "command.h"
Object::Object( const char* name)
{
    m_prevAttackTick = -1;
    m_hp = 0;

    m_damage = 0;
    m_attackSpeed = 0;

    m_party = nullptr;

    m_name = name;
}
Object::~Object()
{
    for (auto skill : m_skillList)
        delete skill;

    m_skillList.clear();
}

void Object::updateFrame(CommandQ& cmdQ, int nowTick, Party* enemy, Party* ourTeam) {

    if (isDead())
        return;

    //물리 공격
    if (m_prevAttackTick == -1)
    {
        m_prevAttackTick = nowTick;
        cmdQ.push_back(m_prevAttackTick, new CCmdDamage(enemy, this, m_damage));

    }
    else {
        while (nowTick >= m_prevAttackTick + m_attackSpeed) {
            m_prevAttackTick += m_attackSpeed;

            cmdQ.push_back(m_prevAttackTick, new CCmdDamage(enemy, this, m_damage));
        }
    }

    std::for_each(m_skillList.begin(), m_skillList.end(), [&]( Skill* skill) -> void{
        skill->updateFrame(cmdQ, nowTick, enemy, ourTeam, this);
    });
 
}

bool Object::damaged(int damage, std::string& attacker ) {

    if (isDead()) {
        return false;
    }

    m_hp -= damage;

 //   std::cout << m_name <<"(hp:" << std::to_string(m_hp) << ") is Damaged(damage:" << std::to_string(damage) <<") from " << attacker << std::endl;

    if( isDead() )
        std::cout << m_name << " is Dead" << std::endl;

    return true;
}

bool Object::heal(int _hp, std::string& healer) {
    if (isDead()) {
        return false;
    }

    m_hp += _hp;

//    std::cout << getName() << "(HP:" << std::to_string(m_hp) << ") is Healed(hp:" << std::to_string(_hp) << ")  from " << healer << std::endl;
    return true;
}
