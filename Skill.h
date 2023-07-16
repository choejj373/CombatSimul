#pragma once
#include <string>
#include <memory>

#include "LoopUpdater.h"

class ICombatObject;
class Party;
class Object;
class CommandQ;
class SkillEffect;
/// <summary>
/// USER_SKILL TABLE�� SKILL_LIST, EFFECT_LIST�� �̿��ϸ� Skill�� ����� �ڽ� Ŭ�������� ������ ���� �� �ְ� �ٿ��� �Ѵ�.
/// </summary>
class Skill
{
protected:
    //int m_coolTimeTick      = 0;
    //int m_prevProcessTick   = -1;
    LoopUpdater                     m_loopUpdater;
    std::shared_ptr<SkillEffect>    m_effect;
public:
    Skill() {}
    Skill( int coolTimeTick);
    virtual ~Skill();
    virtual void updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner);

  //  virtual void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object * owner) = 0;

};

class SkillDamage : public Skill {
public:
    SkillDamage(int coolTimeTick);
};

class SkillDamageWide : public Skill {
public:
    SkillDamageWide(int coolTimeTick);
};

class SkillHeal : public Skill {
public:  
    SkillHeal(int coolTimeTick);
};

class SkillHealWide : public Skill {
public:
    SkillHealWide(int coolTimeTick);
};
class SkillHealDot : public Skill {
public:
    SkillHealDot(int coolTimeTick);
};

class SkillDamageDot : public Skill {
public:
    SkillDamageDot(int coolTimeTick);
};

class SkillAtkUp : public Skill {
public:
    SkillAtkUp(int coolTimeTick);
};