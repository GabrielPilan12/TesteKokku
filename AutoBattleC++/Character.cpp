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

            return;
        }
        else
        {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target

			printf("\n\nCharacter Current Box before moving: Line: %d Column: %d \n",currentBox.xIndex, currentBox.yIndex);
			printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);

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

				printf("Character Moved Up\n");
				printf("Character Current Box After moving: Line: %d Column: %d \n", currentBox.xIndex, currentBox.yIndex);
				printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
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

				printf("Character Moved Down\n");
				printf("Character Current Box After moving: Line: %d Column: %d \n", currentBox.xIndex, currentBox.yIndex);
				printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
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

				printf("Character Moved to the Left\n");
				printf("Character Current Box After moving: Line: %d Column: %d \n", currentBox.xIndex, currentBox.yIndex);
				printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
				return;

            }
            else if(currentBox.yIndex < target->currentBox.yIndex)
            {
				//CHARACTER GO RIGHT
				printf("\nCharacter MUST GO RIGHT\n");

				//TODO Continuar aqui -> Fazer isso Funcionar agora para o Up e Down
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

				printf("Character Moved to the Right\n");
				printf("Character Current Box After moving: Line: %d Column: %d \n", currentBox.xIndex, currentBox.yIndex);
				printf("Target Current Box  Line: %d Column: %d \n", target->currentBox.xIndex, target->currentBox.yIndex);
                return;
            }



        }
}



bool Character::CheckCloseTargets(Grid* battlefield)
{
	//TODO Implement Checking Close Targets, verify left and right, then up and down
	return false;
}

void Character::Attack(Character* target) 
{

}

