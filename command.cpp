#include "command.h"
#include "Party.h"
#include "Object.h"
#include "SkillEffect.h"

void CCmdDamage::Exec(){
	if (m_owner->isDead())
		return;

	m_target->damaged(m_value, m_owner->getName() );

};

void CCmdDamageWide::Exec() {
	if (m_owner->isDead())
		return;
	m_target->damagedAll(m_value, m_owner->getName());
};

CCmdSkill::~CCmdSkill()
{
}
void CCmdSkill::Exec()
{
	if (m_owner->isDead())
		return;

	switch (m_effect->getTargetType())
	{
	case TARGET_TYPE::SELF:
		m_owner->heal(m_effect->getValue(), m_owner->getName());
		break;
	case TARGET_TYPE::ALLY:
		m_ally->skillEffected(m_effect, m_owner->getName());
		break;
	case TARGET_TYPE::ENEMY:
		m_target->skillEffected(m_effect, m_owner->getName());
	default:
		break;
	}
}