#include "command.h"
#include "Party.h"
#include "Object.h"

void CCmdDamage::Exec(){
	if (m_owner->isDead())
		return;

	m_target->damaged(m_value, m_owner->getName() );

};

void CCmdHeal::Exec() {
	if (m_owner->isDead())
		return;
	
	m_target->heal(m_value, m_owner->getName());
};


void CCmdDamageWide::Exec() {
	if (m_owner->isDead())
		return;
	m_target->damagedAll(m_value, m_owner->getName());
};

void CCmdHealWide::Exec() {
	if (m_owner->isDead())
		return;

	m_target->healAll(m_value, m_owner->getName());
};

