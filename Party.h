#pragma once
#include <string>
#include <list>
#include <memory>

class Object;
class CommandQ;
class SkillEffect;
class ContinuousEffect;

class Party
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
    void skillEffected(int nowTime, const std::shared_ptr<SkillEffect>& effect, const std::string& ownerName );
    void continuousEffected(const std::shared_ptr<ContinuousEffect>& effect, const std::string& ownerName);

private:


public:
    void addMember( Object* member);
    

};

