#pragma once
#include <string>
#include <list>
#include <memory>
#include "ICombatObject.h"
class Object;
class CommandQ;
class SkillEffect;

class Party : public ICombatObject
{
    std::list<Object*> m_memberList;
    std::string m_name;
public:
    virtual ~Party();
    Party( const char* name) : m_name(name) {}

    void damagedAll(int damage, const std::string&);
    void healAll(int hp, const std::string&);
    bool damaged(int damage, const std::string&);
    bool heal(int _hp, const std::string&);

    int getHp();
    bool isDead();
    const std::string& getName() const { return m_name; }

    void updateFrame( CommandQ&, int nowTick, Party* enemy);

public:
    void skillEffected(const std::shared_ptr<SkillEffect>& effect, const std::string& ownerName );

private:


public:
    void addMember( Object* member);
    

};

