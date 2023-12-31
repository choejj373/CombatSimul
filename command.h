#pragma once

#include <memory>
class Party;
class Object;
class SkillEffect;
class ContinuousEffect;
/// <summary>
/// 
/// </summary>
class Command
{
protected:
	Party*	m_enemy;
	Object* m_owner;
	int		m_value;
public:
	Command() : m_enemy(nullptr), m_owner(nullptr),m_value(0) {}
	virtual ~Command() {}
	virtual void Exec(int nowTime) = 0;
};
/// <summary>
/// Object의 물리 공격용 Command
/// </summary>
class CCmdDamage : public Command {
	
public:
	CCmdDamage( Party* enemy, Object* owner, int damage)
	{
		m_enemy = enemy;
		m_owner = owner;
		m_value = damage;
	}

	void Exec(int nowTime);
};

class CCmdDamageWide : public Command{
public:
	CCmdDamageWide(Party* enemy, Object* owner, int damage)
	{
		m_enemy = enemy;
		m_owner = owner;
		m_value = damage;
	}

	void Exec(int nowTime);

};
/// <summary>
/// Object가 소유한 Skill에서 만들어진 Command
/// </summary>
class CCmdSkill : public Command {

	std::shared_ptr<SkillEffect>	m_effect;
	Party*							m_ally = nullptr;

public:
	virtual ~CCmdSkill();
	CCmdSkill(Party* enemy, Party* ally, Object* owner, const std::shared_ptr<SkillEffect>& effect)
	{
		m_ally		= ally;
		m_enemy		= enemy;
		m_owner		= owner;
		m_effect	= effect;
	}

	void Exec(int nowTime);
};

class CCmdEffect : public Command {
	std::shared_ptr<ContinuousEffect>	m_effect;

	Party* m_ally = nullptr;

public:
	virtual ~CCmdEffect();
	CCmdEffect(const std::shared_ptr<ContinuousEffect>& effect, Object* owner, Party* ally);

	void Exec(int nowTime);

};