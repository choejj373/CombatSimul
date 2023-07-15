#pragma once
#include <string>
#include <memory>

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
    int m_coolTimeTick      = 0;
    int m_prevProcessTick   = -1;

public:
    Skill() {}
    Skill( int coolTimeTick);
    virtual ~Skill();
    void updateFrame(CommandQ& cmdQ, int nowTick, Party* enemy, Party* ourTeam, Object* owner);

    virtual void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object * owner) = 0;

};

class SkillDamage : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;

public:
    SkillDamage(int coolTimeTick);
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillDamageWide : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;

public:
    SkillDamageWide(int coolTimeTick);
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillHeal : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;

public:  
    SkillHeal(int coolTimeTick);
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillHealWide : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;

public:
    SkillHealWide(int coolTimeTick);
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};
class SkillHealDot : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;
public:
    SkillHealDot(int coolTimeTick);
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};

class SkillDamageDot : public Skill {
    std::shared_ptr<SkillEffect>    m_effect;
public:
    SkillDamageDot(int coolTimeTick);
    void process(CommandQ& cmdQ, int processTime, Party* enemy, Party* ourTeam, Object* owner);
};