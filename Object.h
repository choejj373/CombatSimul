#pragma once
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <memory>
#include "ICombatObject.h"
#include "effect.h"

class Skill;
class Party;
class Effect;
class CommandQ;
class SkillEffect;
class ContinuousEffect;
class Object : public ICombatObject
{
	std::vector<Skill*>                     m_skillList;

    std::list<std::tuple<int, std::shared_ptr<ContinuousEffect>>> m_continuousEffectList;

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

    void    addContinuousEffect(int nowTime, const std::shared_ptr<SkillEffect>& effect);
    void    continuousEffected(ContinuousEffect* effect, const std::string& ownerName);
    void    applyEffect(EFFECT_TYPE type, int value, const std::string& ownerName);
private:
    void    updateContinuousEffect(CommandQ& cmdQ, int nowTime, Party* ally);

public:
    void    updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam );

    bool    damaged(int damage, const std::string&);
    bool    heal(int _hp, const std::string& );

    int     getHp() { return m_hp; }
    bool    isDead() const { return (m_hp <= 0) ? true : false; }
    bool    isAlive() const { return isDead() ? false : true; }

    const std::string& getName() const  { return m_name; }

};

