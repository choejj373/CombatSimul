#pragma once

#include "ICombatObject.h"
#include <memory>
class Party;
class Object;
class SkillEffect;

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

class CCmdSkill : public Command {

	std::shared_ptr<SkillEffect>	m_effect;
	Party*							m_ally = nullptr;

public:
	virtual ~CCmdSkill();
	CCmdSkill(Party* target, Party* ally, Object* owner, const std::shared_ptr<SkillEffect>& effect)
	{
		m_ally		= ally;
		m_target	= target;
		m_owner		= owner;
		m_effect	= effect;
	}

	void Exec();
};