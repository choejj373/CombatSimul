#pragma once
#include <string>
#include <memory>

#include "LoopUpdater.h"

class ICombatObject;
class Party;
class Object;
class CommandQ;
class SkillEffect;
/// <summary>
/// USER_SKILL TABLE과 SKILL_LIST, EFFECT_LIST를 이용하면 Skill을 상속한 자식 클래스들의 갯수를 줄일 수 있고 줄여야 한다.
/// </summary>
class Skill
{
protected:
    LoopUpdater                     m_loopUpdater;
    std::shared_ptr<SkillEffect>    m_effect;
public:
    Skill() = delete;
    Skill( int coolTimeTick, const std::shared_ptr<SkillEffect>& effect );
    virtual ~Skill();
    virtual void updateFrame(CommandQ& cmdQ, int nowTime, Party* enemy, Party* ourTeam, Object* owner);
};
