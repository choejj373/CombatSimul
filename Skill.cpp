#include "Skill.h"
#include <iostream>


#include "Party.h"
#include "Object.h"
#include "commandq.h"
#include "command.h"
#include "SkillEffect.h"

Skill::Skill(int coolTimeTick, const std::shared_ptr<SkillEffect>& effect)
{
    m_loopUpdater.init(-1, coolTimeTick, 0);
    m_effect = effect;
}

Skill::~Skill()
{
    //std::cout << "~Skill" << std::endl;
}

void Skill::updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner)
{
    m_loopUpdater.Update(nowTime, [&](int time) {
        cmdQ.push_back(time, new CCmdSkill(enemy, ourTeam, owner, m_effect));
        });
}
