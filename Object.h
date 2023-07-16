#pragma once
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <memory>

#include "effect.h"
#include "LoopUpdater.h"

class Skill;
class Party;
class Effect;
class CommandQ;
class SkillEffect;
class ContinuousEffect;

class Object
{
	std::vector<Skill*>                     m_skillList;

    // 지속 효과
    std::list<std::tuple<int, std::shared_ptr<ContinuousEffect>>> m_continuousEffects;
    // 지속 효과중 주기적 발동 효과
    std::list<std::tuple<int, std::shared_ptr<ContinuousEffect>>> m_continuousIntervalEffects;

	std::string m_name;
	int m_hp;

	int m_damage;
	int m_attackSpeed;

	Party* m_party;

    std::vector<int>    m_extraStat;
    LoopUpdater         m_loopUpdater;

public:
    virtual ~Object();
    Object(const char* name);
    void addSkill(Skill* skill) {
        m_skillList.push_back(skill);
    }

    void    setStat(int hp, int damage, int attackSpeed);

public:
    void    skillEffected(int nowTime, const std::shared_ptr<SkillEffect>& effect, const std::string& ownerName);
    void    addContinuousEffect(int nowTime, const std::shared_ptr<SkillEffect>& effect);
    void    applyEffect(EFFECT_TYPE type, int value, const std::string& ownerName);
    void    continuousEffected(std::shared_ptr<ContinuousEffect>& effect, const std::string& ownerName);

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

private:
    int     getDamage();

};

