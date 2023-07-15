#include "command.h"
#include "Party.h"
#include "Object.h"
#include "SkillEffect.h"
#include "ContinuousEffect.h"

void CCmdDamage::Exec(int nowTime){
	if (m_owner->isDead())
		return;

	m_target->damaged(m_value, m_owner->getName() );

};

void CCmdDamageWide::Exec(int nowTime) {
	if (m_owner->isDead())
		return;
	m_target->damagedAll(m_value, m_owner->getName());
};

CCmdSkill::~CCmdSkill()
{
}
void CCmdSkill::Exec(int nowTime)
{
	if (m_owner->isDead())
		return;

	switch (m_effect->getTargetType())
	{
	case EFFECT_TARGET_TYPE::SELF:
		m_owner->heal(m_effect->getValue(), m_owner->getName());//? heal->skillEffected
		break;
	case EFFECT_TARGET_TYPE::ALLY:
		m_ally->skillEffected(nowTime, m_effect, m_owner->getName());
		break;
	case EFFECT_TARGET_TYPE::ENEMY:
		m_target->skillEffected(nowTime, m_effect, m_owner->getName());
	default:
		break;
	}
}


CCmdEffect::CCmdEffect(std::shared_ptr<ContinuousEffect>& effect, Object* owner, Party* ally)
{ 
	m_effect = effect; 
	m_owner = owner; 
	m_ally = ally;
	//std::cout << "CCmdEffect::CCmdEffect" << std::endl;
}
CCmdEffect::~CCmdEffect()
{
	//std::cout << "CCmdEffect::~CCmdEffect" << std::endl;
}
void CCmdEffect::Exec(int nowTime)
{
	if (m_owner->isDead())
		return;

	switch (m_effect->getTargetType())
	{
	case EFFECT_TARGET_TYPE::SELF:
		m_owner->continuousEffected(m_effect, m_owner->getName());//? heal->continuousEffected
		break;
	//case EFFECT_TARGET_TYPE::ALLY:
	//	m_ally->continuousEffected(m_effect, m_owner->getName());
	//	break;
	//case EFFECT_TARGET_TYPE::ENEMY:
	//	m_target->skillEffected(nowTime, m_effect, m_owner->getName());
	default:
		break;
	}
}