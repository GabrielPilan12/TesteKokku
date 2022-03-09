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

	/*
	battlefield->xLenght = 5
	battlefield->yLength = 5

	Indice 0 -> Linha = 0 e Coluna = 0
	Indice 1 -> Linha = 0 e Coluna = 1
	Indice 2 -> Linha = 0 e Coluna = 2
	Indice 3 -> Linha = 0 e Coluna = 3
	Indice 4 -> Linha = 0 e Coluna = 4
	Indice 5 -> Linha = 1 e Coluna = 0
	Indice 6 -> Linha = 1 e Coluna = 1
	Indice 7 -> Linha = 1 e Coluna = 2
	Indice 8 -> Linha = 1 e Coluna = 3
	Indice 9 -> Linha = 1 e Coluna = 4
	Indice 10 -> Linha = 2 e Coluna = 0

	Indice = (linha * battlefield->xLenght) + coluna
	0 1 2 3 4
	5 6 7 8 9
	10
	*/

	//TODO -> Diagonals Can Also be Considered Here

	//verify if not at the top, then if it not, verify up
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].xIndex != 0)
	{
		if (battlefield->grids[((currentBox.xIndex - 1) * battlefield->xLenght) + currentBox.yIndex].ocupied == true)
		{
			return true;
		}
	}


	//Verify if not at the bottom, then if not, Verify Down
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].xIndex != (battlefield->xLenght - 1))
	{
		if (battlefield->grids[((currentBox.xIndex + 1) * battlefield->xLenght) + currentBox.yIndex].ocupied == true)
		{
			return true;
		}
	}

	//Verify if not at the Leftmost, then if not, Verify to the Left
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].yIndex != 0)
	{
		if (battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex - 1)].ocupied == true)
		{
			return true;
		}
	}
	//Verify if not at the rightmost, then if not, Verify to the Right
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].xIndex != (battlefield->yLength - 1))
	{
		if (battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex + 1)].ocupied == true)
		{
			return true;
		}
	}

	return false;
}

//TODO Remove is Player Turn for PlayerIndex == 0
void Character::StartTurn(Grid* battlefield, bool IsPlayerTurn) 
{
	
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


	if (CheckCloseTargets(battlefield))
	{
		Attack(&*target);
		return;
	}
	else
	{   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target

		/*
		printf("\n\nCharacter Current Box before moving: Line: %d Column: %d \n", currentBox.xIndex, currentBox.yIndex);
		printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
		*/

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

	//TODO Implement a Chance to Push the Character Away
	
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










