#pragma once
#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include <memory>
#include <vector> //Was Missing

using namespace std; //Was Missing

class Character
{
public:

    Character(Types::CharacterClass charcaterClass);
    ~Character();

    float Health;
    float BaseDamage;
    float DamageMultiplier;
    int PlayerIndex;

	shared_ptr<Character> target;

    bool IsDead = false;

    Types::GridBox currentBox;

    void TakeDamage(float amount);

    void Die();

    void StartTurn(Grid* battlefield , bool IsPlayerTurn);

    bool CheckCloseTargets(Grid* battlefield);

    void Attack(Character* target);

	void AttackTryPushAway(Character* target , Grid* battlefield);


};

