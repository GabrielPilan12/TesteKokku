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

bool Character::TakeDamage(float amount) 
{
	if ((Health -= BaseDamage) <= 0) 
	{
		Die();
		return true;
	}
	return false;
}

void Character::Die() 
{
	// TODO >> kill
	//TODO >> end the game?
}

void Character::WalkTo(bool CanWalk) 
{

}




void Character::StartTurn(Grid* battlefield , bool IsPlayerTurn) { 

        if (CheckCloseTargets(battlefield))
        {
            //Attack(Character::target);
			printf("\nATTACK!\n");
            return;
        }
        else
        {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
			
			/*
			printf("\n\nCharacter Current Box before moving: Line: %d Column: %d \n",currentBox.xIndex, currentBox.yIndex);
			printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
			*/

            if (currentBox.xIndex > target->currentBox.xIndex)
            {
				//CHARACTER GO UP
				printf("\nCharacter MUST GO UP\n");

				//TODO Verify if this IF really is necessary
                //if(find(battlefield->grids.begin(), battlefield->grids.end(), currentBox.Index - 1) != battlefield->grids.end())
                //{
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

				target->target->currentBox = currentBox;

				battlefield->drawBattlefield(5, 5);
				/*
				printf("Character Moved Up\n");
				printf("Character Current Box After moving: Line: %d Column: %d \n", currentBox.xIndex, currentBox.yIndex);
				printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
				*/
                return;
                //}
            }
            else if(currentBox.xIndex < target->currentBox.xIndex)
            {
				//CHARACTER GO DOWN
				printf("\nCharacter MUST GO DOWN\n");

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

				target->target->currentBox = currentBox;

				battlefield->drawBattlefield(5, 5);

				/*
				printf("Character Moved Down\n");
				printf("Character Current Box After moving: Line: %d Column: %d \n", currentBox.xIndex, currentBox.yIndex);
				printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
				*/
				return;
            }
            
			if (currentBox.yIndex > target->currentBox.yIndex)
            {
				//CHARACTER GO LEFT
				printf("\nCharacter MUST GO LEFT\n");
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

				target->target->currentBox = currentBox;

				battlefield->drawBattlefield(5, 5);

				/*
				printf("Character Moved to the Left\n");
				printf("Character Current Box After moving: Line: %d Column: %d \n", currentBox.xIndex, currentBox.yIndex);
				printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
				*/
				return;

            }
            else if(currentBox.yIndex < target->currentBox.yIndex)
            {
				//CHARACTER GO RIGHT
				printf("\nCharacter MUST GO RIGHT\n");

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
				
				target->target->currentBox = currentBox;

				battlefield->drawBattlefield(5, 5);
				/*
				printf("Character Moved to the Right\n");
				printf("Character Current Box After moving: Line: %d Column: %d \n", currentBox.xIndex, currentBox.yIndex);
				printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
				*/
                return;
            }



        }
}



bool Character::CheckCloseTargets(Grid* battlefield)
{
	int xLenght = battlefield->xLenght;
	int yLenght = battlefield->yLength;

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

	Indice = (linha * xLenght) + coluna
	0 1 2 3 4
	5 6 7 8 9
	10
	
	*/
	

	/*
	Types::GridBox CurrentGridBox;
	Types::GridBox OtherGridBox;

	currentBox.ocupied = true;

	CurrentGridBox = battlefield->grids[(currentBox.xIndex * xLenght) + currentBox.yIndex];

	if(CurrentGridBox.ocupied)
	{
		printf("\n\nOccupied\n\n");
	}

	OtherGridBox = battlefield->grids[((currentBox.xIndex + 1) * xLenght) + currentBox.yIndex];

	if (OtherGridBox.ocupied)
	{
		printf("\n\nOther Grid Box Also Occupied\n\n");
	}
	*/

	/*
	Types::GridBox CurrentGridBox;

	CurrentGridBox = battlefield->grids[(currentBox.xIndex * xLenght) + currentBox.yIndex];
	printf("Character Current Grid Box, xValue %d and yValue %d", CurrentGridBox.xIndex, CurrentGridBox.yIndex);
	*/

	//TODO Continuar aqui -> Enteder Qual o caso que faz um nao atacar o outro mesmo estando do lado

	if (battlefield->grids[((currentBox.xIndex - 1) * xLenght) + currentBox.yIndex].ocupied == true) //Verify up
	{
		return true;
	}

	if (battlefield->grids[((currentBox.xIndex + 1) * xLenght) + currentBox.yIndex].ocupied == true) //Verify Down
	{
		return true;
	}

	if (battlefield->grids[(currentBox.xIndex * xLenght) + (currentBox.yIndex + 1)].ocupied == true) //Verify to the Right
	{
		return true;
	}
	if (battlefield->grids[(currentBox.xIndex * xLenght) + (currentBox.yIndex - 1)].ocupied == true) //Verify to the Left
	{
		return true;
	}

	return false;
}

void Character::Attack(Character* target) 
{

}

