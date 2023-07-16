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
/// USER_SKILL TABLE�� SKILL_LIST, EFFECT_LIST�� �̿��ϸ� Skill�� ����� �ڽ� Ŭ�������� ������ ���� �� �ְ� �ٿ��� �Ѵ�.
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
