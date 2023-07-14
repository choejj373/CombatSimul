#pragma once

#include "ICombatObject.h"

class Party;
class Object;
class Command
{
protected:
	Party* m_target;
	Object* m_owner;
	int m_value;
public:
	Command() : m_target(nullptr), m_owner(nullptr),m_value(0) {}
	virtual ~Command() {}
	virtual void Exec() = 0;
};

class CCmdDamage : public Command {
	
public:
	CCmdDamage( Party* target, Object* owner, int damage)
	{
		m_target = target;
		m_owner = owner;
		m_value = damage;
	}

	void Exec();
};

class CCmdHeal : public Command {
public:
	CCmdHeal(Party* target, Object* owner, int hp)
	{
		m_target = target;
		m_owner = owner;
		m_value = hp;
	}
	void Exec();

};

class CCmdDamageWide : public Command{
public:
	CCmdDamageWide(Party* target, Object* owner, int damage)
	{
		m_target = target;
		m_owner = owner;
		m_value = damage;
	}

	void Exec();

};

class CCmdHealWide : public Command {
public:
	CCmdHealWide(Party* target, Object* owner, int hp)
	{
		m_target = target;
		m_owner = owner;
		m_value = hp;
	}

	void Exec();

};