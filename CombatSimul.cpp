// CombatSimul.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <chrono>
#include <algorithm>
#include <tuple>
#include <windows.h>
#include "Party.h"
#include "Object.h"
#include "Skill.h"

#include <memory>
#include <vector>
#include "CommandQ.h"
#include "command.h"

using namespace std::chrono;
using namespace std;

Skill* MakeSkill(int type, int coolTime)
{
    Skill* newSkill = nullptr;
   // std::cout << type << ", " << coolTime << std::endl;
    switch (type)
    {
    case 1:
        newSkill = new SkillDamage( coolTime );
        break;
    case 2:
        newSkill = new SkillHeal( coolTime );
        break;
    case 3:
        newSkill = new SkillDamageWide(coolTime);
        break;
    case 4:
        newSkill = new SkillHealWide(coolTime);
        break;
    case 5:
        newSkill = new SkillHealDot(coolTime);
        break;
    case 6:
        newSkill = new SkillDamageDot(coolTime);
        break;
    case 7:
        newSkill = new SkillAtkUp(coolTime);
        break;
    default:
        throw std::runtime_error("Invalid Skill Type");
        break;
    };
    return newSkill;
}
void test(std::vector<int>& p1_value, std::vector<int>& p2_value)
{
  
    auto p1 = new Party("a");
    auto p2 = new Party("b");
    std::string name;
    int index = 0;
    try {
        auto iterA = p1_value.begin();
        index = 1;
        do {
            name = "a";
            name.append(std::to_string(index));

            auto member = new Object(name.c_str());
            member->setStat(*iterA, *(iterA + 1), *(iterA + 2)); std::advance(iterA, 3);
            member->addSkill(MakeSkill(*(iterA), *(iterA + 1))); std::advance(iterA, 2);
            member->addSkill(MakeSkill(*(iterA), *(iterA + 1))); std::advance(iterA, 2);
            member->addSkill(MakeSkill(*(iterA), *(iterA + 1))); std::advance(iterA, 2);
            member->addSkill(MakeSkill(*(iterA), *(iterA + 1))); std::advance(iterA, 2);
            p1->addMember(member);

            index++;
            
        } while (iterA != p1_value.end());


        auto iterB = p2_value.begin();
        index = 1;
        do {
            name = "b";
            name.append(std::to_string(index));

            auto member = new Object(name.c_str());

            member->setStat(*iterB, *(iterB + 1), *(iterB + 2)); std::advance(iterB, 3);
            member->addSkill(MakeSkill(*(iterB), *(iterB + 1))); std::advance(iterB, 2);
            member->addSkill(MakeSkill(*(iterB), *(iterB + 1))); std::advance(iterB, 2);
            member->addSkill(MakeSkill(*(iterB), *(iterB + 1))); std::advance(iterB, 2);
            member->addSkill(MakeSkill(*(iterB), *(iterB + 1))); std::advance(iterB, 2);

            p2->addMember(member);

            index++;
        } while (iterB != p2_value.end());
    }
    catch(std::runtime_error e)
    { 
        std::cout << e.what() << std::endl;
    }


    // 1tick == 1ms 이라고 가정하면 최대 120초동안 시뮬을 돌린다.

    int max = 1000 * 120;
    int i = 0;

    CommandQ cmdQ;

    for (; i < max; i += 10 )
    {
        p1->updateFrame(cmdQ, i, p2);
        p2->updateFrame(cmdQ, i, p1);

        cmdQ.sort();

        for (size_t i = 0; i < cmdQ.size(); ++i)
        {
            std::tuple<int, Command*> item = cmdQ.at(i);
            Command* cmd = std::get<1>(item);
            cmd->Exec(std::get<0>(item));
            delete cmd;
        }

        cmdQ.clear();

        if (p2->isDead()) {
            std::cout << "Elapsed Tick:" << i << ", Winner:" + p1->getName() + ", hp:" << p1->getHp() << " enemy hp:" << p2->getHp() << std::endl;
            break;
        }

        if (p1->isDead()) {
            std::cout << "Elapsed Tick:" << i << ", Winner:" + p2->getName() + ", hp:" << p2->getHp() << " enemy hp:" << p1->getHp() << std::endl;
            break;
        }
    }
    if ( i >= max)
    {
        std::cout << "timeout " << p1->getName() << ":" << p1->getHp() << ", " << p2->getName() << ":" << p2->getHp() << std::endl;
    }

    delete p1;
    delete p2;
}

#include "PRNG.h"

int main()
{
    //std::ostringstream sss;
    //sss << "Elapsed Tick:" << 1 << ", Winner:" << "111" << ", hp:" << 2 << " enemy hp:" << 3 << std::endl;

    //std::string result = sss.str();

    //std::cout << result;



    //    

    auto tp1 = system_clock::now(); // 현재 시간 리턴


    std::vector<int> p1_value = {
           50000, 500, 1000,
               1,500,
               1,500,
               1,1000,
               2,1500,
           20000, 500, 1000,
               3,1000,
               1,1500,
               1,2000,
               4,2500,
           20000, 500, 1000,
               5,10000,
               1,2500,
               1,3000,
               6,10000,
           10000, 500, 1000,
               7,4000,
               1,4500,
               1,5000,
               1, 5000,
           30000, 500, 1000,
               1,4000,
               1,4500,
               1,5000,
               1,5000
    };

    std::vector<int> p2_value{
        50000, 500, 1000,
            1, 500,
            1, 500,
            1, 1000,
            2, 1500,
        20000, 500, 1000,
            3, 1000,
            1, 1500,
            1, 2000,
            4, 2500,
        20000, 500, 1000,
            5, 10000,
            1, 2500,
            1, 3000,
            6, 10000,
        20000, 500, 1000,
            7, 4000,
            1, 4500,
            1, 5000,
            1, 5000,
        20000, 500, 1000,
            1, 4000,
            1, 4500,
            1, 5000,
            1, 5000
    };

    test( p1_value, p2_value );

    auto tp2 = system_clock::now(); // 현재 시간 리턴

    std::cout << duration_cast<milliseconds>(tp2 - tp1) << std::endl;


   

    system("pause");
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
