#pragma once
#include <string>

class ICombatObject;
class Party;
class Object;
class CommandQ;
class Skill
{
    int m_coolTimeTick;
    int m_prevProcessTick;

public:
    Skill( int coolTimeTick);
    virtual ~Skill();
    void updateFrame(CommandQ& cmdQ, int nowTick, Party* enemy, Party* ourTeam, Object* owner);

    virtual void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object * owner) = 0;

};

class SkillDamage : public Skill {
public:
    SkillDamage(int coolTimeTick) : Skill(coolTimeTick) {}
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillDamageWide : public Skill {
public:
    SkillDamageWide(int coolTimeTick) : Skill(coolTimeTick) {}
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillHeal : public Skill {
public:  
    SkillHeal(int coolTimeTick) : Skill(coolTimeTick) {}
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillHealWide : public Skill {
public:
    SkillHealWide(int coolTimeTick) : Skill(coolTimeTick) {}
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};