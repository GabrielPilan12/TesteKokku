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
    //public GridBox currentBox;
    int PlayerIndex;
    //public Character Target{ get; set; }

    //Character *target;
	shared_ptr<Character> target;

    bool IsDead;
    char Icon;

    Types::GridBox currentBox;

    bool TakeDamage(float amount);

    int getIndex(vector<Types::GridBox*> v, int index);

    void Die();

    void WalkTo(bool CanWalk);

    void StartTurn(Grid* battlefield , bool IsPlayerTurn);

    bool CheckCloseTargets(Grid* battlefield);

    void Attack(Character* target);


};

