#pragma once
#include <string>

class Party;
class ICombatObject {

public:
    virtual ~ICombatObject() {};
    //virtual void damagedAll(int damage, std::string&) = 0;
    //virtual void healAll(int hp, std::string&) = 0;
    virtual bool damaged(int damage, const std::string&) = 0;
    virtual bool heal(int _hp, const std::string&) = 0;

    virtual int getHp() = 0;
    virtual bool isDead() = 0;
    virtual const std::string& getName() const = 0;

    //virtual Party* getParty() = 0;
    //virtual void updateFrame(int nowTick, ICombatObject* enemy) = 0;


};
