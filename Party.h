#pragma once
#include <string>
#include <list>

#include "ICombatObject.h"
class Object;
class CommandQ;
class Party : public ICombatObject
{
    std::list<Object*> m_memberList;
    std::string m_name;
public:
    virtual ~Party();
    Party( const char* name) : m_name(name) {}

    void damagedAll(int damage, std::string&);
    void healAll(int hp, std::string&);
    bool damaged(int damage, std::string&);
    bool heal(int _hp, std::string&);

    int getHp();
    bool isDead();
    std::string& getName() { return m_name; }

    void updateFrame( CommandQ&, int nowTick, Party* enemy);

public:
    void addMember( Object* member);
    

};

