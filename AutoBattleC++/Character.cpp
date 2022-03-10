#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include "Character.h"
#include <vector>
#include <algorithm>

using namespace std;
Character::Character(Types::CharacterClass charcaterClass)
{
	Types::GridBox currentBox(0, 0, false, 0);

}

Character::~Character() 
{

}

bool Character::CheckCloseTargets(Grid* battlefield)
{
	currentBox.xIndex = target->target->currentBox.xIndex;
	currentBox.yIndex = target->target->currentBox.yIndex;

	//verify if not at the top, then if it not, then verify up
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].xIndex != 0)
	{
		if (battlefield->grids[((currentBox.xIndex - 1) * battlefield->xLenght) + currentBox.yIndex].ocupied == true)
		{
			printf("Found a Close Target at the Top \n");
			return true;
		}
	}


	//Verify if not at the bottom, then if not, then Verify Down
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].xIndex != (battlefield->xLenght - 1))
	{
		if (battlefield->grids[((currentBox.xIndex + 1) * battlefield->xLenght) + currentBox.yIndex].ocupied == true)
		{
			printf("Found a Close Target at the Bottom \n");
			return true;
		}
	}

	//Verify if not at the Leftmost, then if not, then Verify to the Left
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].yIndex != 0)
	{
		if (battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex - 1)].ocupied == true)
		{
			printf("Found a Close Target to the Left \n");
			return true;
		}
	}

	//Verify if not at the rightmost, then if not, then Verify to the Right

	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].yIndex != (battlefield->yLength - 1))
	{
		if (battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex + 1)].ocupied == true)
		{
			printf("Found a Close Target to the Right \n");
			return true;
		}
	}

	return false;
}


void Character::StartTurn(Grid* battlefield, bool IsPlayerTurn) 
{
	//Verify if Player is Alive
	if (target->target->Health <= 0)
	{
		IsDead = true;
		return;
	}

	if (PlayerIndex == 0)
	{
		printf("\nPlayer Action:\n");
	}
	else
	{
		printf("\nEnemy Action:\n");
	}


	if (CheckCloseTargets(battlefield)) //Checks if there is any Close Attack Target (Diagonals are not Considered)
	{

		Attack(&*target);

		//Special Feature implemented since I was born in May, this will try to push the attack target to some direction
		AttackTryPushAway(&*target , battlefield);
		
		return;
	}
	else
	{   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target

		//Makes the Current Character Position Free because it will move
		battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + currentBox.yIndex].ocupied = false;

		if (currentBox.xIndex > target->currentBox.xIndex)
		{
			//CHARACTER GO UP
			printf("\nCharacter MUST GO UP\n");
			battlefield->grids[((currentBox.xIndex - 1) * battlefield->xLenght) + currentBox.yIndex].ocupied = true;

			if (IsPlayerTurn)
			{

				battlefield->PlayerCurrentLocation->xIndex = battlefield->PlayerCurrentLocation->xIndex - 1;
				currentBox = *battlefield->PlayerCurrentLocation;
			}
			else
			{
				battlefield->EnemyCurrentLocation->xIndex = battlefield->EnemyCurrentLocation->xIndex - 1;
				currentBox = *battlefield->EnemyCurrentLocation;
			}

			currentBox.ocupied = true;
			target->target->currentBox = currentBox;

			battlefield->drawBattlefield(5, 5);

			return;
		}
		else if (currentBox.xIndex < target->currentBox.xIndex)
		{
			//CHARACTER GO DOWN
			printf("\nCharacter MUST GO DOWN\n");
			battlefield->grids[((currentBox.xIndex + 1) * battlefield->xLenght) + currentBox.yIndex].ocupied = true;

			if (IsPlayerTurn)
			{
				battlefield->PlayerCurrentLocation->xIndex = battlefield->PlayerCurrentLocation->xIndex + 1;
				currentBox = *battlefield->PlayerCurrentLocation;
			}
			else
			{
				battlefield->EnemyCurrentLocation->xIndex = battlefield->EnemyCurrentLocation->xIndex + 1;
				currentBox = *battlefield->EnemyCurrentLocation;
			}

			currentBox.ocupied = true;
			target->target->currentBox = currentBox;

			battlefield->drawBattlefield(5, 5);

			return;
		}

		if (currentBox.yIndex > target->currentBox.yIndex)
		{
			//CHARACTER GO LEFT
			printf("\nCharacter MUST GO LEFT\n");

			battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex - 1)].ocupied = true;

			if (IsPlayerTurn)
			{
				battlefield->PlayerCurrentLocation->yIndex = battlefield->PlayerCurrentLocation->yIndex - 1;
				currentBox = *battlefield->PlayerCurrentLocation;
			}
			else
			{
				battlefield->EnemyCurrentLocation->yIndex = battlefield->EnemyCurrentLocation->yIndex - 1;
				currentBox = *battlefield->EnemyCurrentLocation;
			}

			currentBox.ocupied = true;
			target->target->currentBox = currentBox;

			battlefield->drawBattlefield(5, 5);

			return;

		}
		else if (currentBox.yIndex < target->currentBox.yIndex)
		{
			//CHARACTER GO RIGHT
			printf("\nCharacter MUST GO RIGHT\n");

			battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex + 1)].ocupied = true;

			if (IsPlayerTurn)
			{
				battlefield->PlayerCurrentLocation->yIndex = battlefield->PlayerCurrentLocation->yIndex + 1;
				currentBox = *battlefield->PlayerCurrentLocation;
			}
			else
			{
				battlefield->EnemyCurrentLocation->yIndex = battlefield->EnemyCurrentLocation->yIndex + 1;
				currentBox = *battlefield->EnemyCurrentLocation;
			}

			currentBox.ocupied = true;
			target->target->currentBox = currentBox;

			battlefield->drawBattlefield(5, 5);

			return;
		}



	}
}

void Character::Attack(Character* target)
{
	if (PlayerIndex == 0)
	{
		printf("The Player is Attacking the Enemy!\n");
	}
	else
	{
		printf("The Enemy is Attacking the Player!\n");
	}
	
	target->TakeDamage(BaseDamage * DamageMultiplier);

	
}

void Character::AttackTryPushAway(Character* target , Grid* battlefield)
{
	int randomnumber = rand() % 3 + 2;

	if (randomnumber % 2 == 0) //Gives a 50% Chance of Pushing the Character
	{
		return;
	}

	//verify if target is not at the top 
	if (battlefield->grids[((target->currentBox.xIndex) * battlefield->xLenght) + target->currentBox.yIndex].xIndex != 0)
	{
		//If the zone above the target is free Push Character Up
		if (battlefield->grids[((target->currentBox.xIndex - 1) * battlefield->xLenght) + target->currentBox.yIndex].ocupied == false)
		{
			battlefield->grids[(target->currentBox.xIndex * battlefield->xLenght) + target->currentBox.yIndex].ocupied = false;
			battlefield->grids[((target->currentBox.xIndex - 1) * battlefield->xLenght) + target->currentBox.yIndex].ocupied = true;

			if (PlayerIndex == 1)
			{

				battlefield->PlayerCurrentLocation->xIndex = battlefield->PlayerCurrentLocation->xIndex - 1;
				target->currentBox = *battlefield->PlayerCurrentLocation;

				target->currentBox.xIndex = battlefield->PlayerCurrentLocation->xIndex;
				target->currentBox.yIndex = battlefield->PlayerCurrentLocation->yIndex;
			}
			else
			{
				battlefield->EnemyCurrentLocation->xIndex = battlefield->EnemyCurrentLocation->xIndex - 1;
				target->currentBox = *battlefield->EnemyCurrentLocation;

				target->currentBox.xIndex = battlefield->EnemyCurrentLocation->xIndex;
				target->currentBox.yIndex = battlefield->EnemyCurrentLocation->yIndex;

			}
			printf("\nCharacter Was Pushed Up! \n");
		}
		else //The Zone Above the Target is not Free and the target is not at the top, so don't push it 
		{
			printf("Cant Push \n");
			return;
		}
	}
	//Target is at the top, so Verify if not at right most
	else if (battlefield->grids[((target->currentBox.xIndex) * battlefield->xLenght) + target->currentBox.yIndex].yIndex != (battlefield->yLength - 1))
	{
		//If the zone to the right of the character is free, push the character to the right
		if (battlefield->grids[((target->currentBox.xIndex) * battlefield->xLenght) + (target->currentBox.yIndex + 1)].ocupied == false)
		{
			battlefield->grids[(target->currentBox.xIndex * battlefield->xLenght) + target->currentBox.yIndex].ocupied = false;
			battlefield->grids[((target->currentBox.xIndex) * battlefield->xLenght) + (target->currentBox.yIndex + 1)].ocupied = true;
			if (PlayerIndex == 1)
			{

				battlefield->PlayerCurrentLocation->yIndex = battlefield->PlayerCurrentLocation->yIndex + 1;
				target->currentBox = *battlefield->PlayerCurrentLocation;

				target->currentBox.xIndex = battlefield->PlayerCurrentLocation->xIndex;
				target->currentBox.yIndex = battlefield->PlayerCurrentLocation->yIndex;
			}
			else
			{
				battlefield->EnemyCurrentLocation->yIndex = battlefield->EnemyCurrentLocation->yIndex + 1;
				target->currentBox = *battlefield->EnemyCurrentLocation;

				target->currentBox.xIndex = battlefield->EnemyCurrentLocation->xIndex;
				target->currentBox.yIndex = battlefield->EnemyCurrentLocation->yIndex;

			}

			printf("\nCharacter Was Pushed Right! \n");
		}
		else //The Zone to the right of the Target is not Free and the target is not at the right most, so don't push it 
		{
			printf("Cant Push \n");
			return;
		}
	}
	else //Character is Corned, so don't push
	{
		printf("Cant Push \n");
		return;
	}

	battlefield->drawBattlefield(5, 5);

}

void Character::TakeDamage(float amount) 
{
	Health = Health - amount;

	if (Health <= 0) 
	{
		Die();		
	}
}

void Character::Die() 
{
	IsDead = true;

	if (PlayerIndex == 0)
	{
		printf("\nPlayer Died!\n");
	}
	else
	{
		printf("\nEnemy Died!\n");
	}
}










