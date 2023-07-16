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
/// USER_SKILL TABLE과 SKILL_LIST, EFFECT_LIST를 이용하면 Skill을 상속한 자식 클래스들의 갯수를 줄일 수 있고 줄여야 한다.
/// </summary>
class Skill
{
protected:
    //int m_coolTimeTick      = 0;
    //int m_prevProcessTick   = -1;
    LoopUpdater m_loopUpdater;
public:
    Skill() {}
    Skill( int coolTimeTick);
    virtual ~Skill();
    virtual void updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner) = 0;

  //  virtual void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object * owner) = 0;

};

class SkillDamage : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;

public:
    SkillDamage(int coolTimeTick);
    virtual void updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner) override;
//    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillDamageWide : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;

public:
    SkillDamageWide(int coolTimeTick);
    virtual void updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner);
    //void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillHeal : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;
    virtual void updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner);
public:  
    SkillHeal(int coolTimeTick);
    //void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillHealWide : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;

public:
    SkillHealWide(int coolTimeTick);
    virtual void updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner);
    //void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};
class SkillHealDot : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;
public:
    SkillHealDot(int coolTimeTick);
    virtual void updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner) ;
//    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillDamageDot : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;
public:
    SkillDamageDot(int coolTimeTick);
    virtual void updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner);
    //void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};