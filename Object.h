#pragma once
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include "ICombatObject.h"

class Skill;
class Party;
class Effect;
class CommandQ;
class Object : public ICombatObject
{
	std::vector<Skill*> m_skillList;

    std::list<Effect*> m_buffList;
    std::list<Effect*> m_debuffList;

	std::string m_name;
	int m_prevAttackTick;
	int m_hp;

	int m_damage;
	int m_attackSpeed;

	Party* m_party;

public:
    virtual ~Object();
    Object(const char* name);
    void addSkill(Skill* skill) {
        m_skillList.push_back(skill);
    }

    void setStat( int hp, int damage, int attackSpeed) {
        m_hp = hp;
        m_damage = damage;
        m_attackSpeed = attackSpeed;
    }

public:
    void updateFrame(CommandQ& cmdQ, int nowTick, Party* enemy, Party* ourTeam );

    bool    damaged(int damage, const std::string&);
    bool    heal(int _hp, const std::string& );

    int     getHp() { return m_hp; }
    bool    isDead() { return (m_hp <= 0) ? true : false; }

    const std::string& getName() const  { return m_name; }

};

