#include "Grid.h"
#include "Types.h"


Grid::Grid(int Lines, int Columns)
{
    xLenght = Lines;
    yLength = Columns;
    //Console.WriteLine("The battle field has been created\n");
    for (int i = 0; i < Lines; i++)
    {

        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* newBox = new Types::GridBox(i, j, false, (Columns * i + j));
            grids.insert(grids.end(), *newBox);
            //Console.Write($"{newBox.Index}\n");
        }
    }
	//drawBattlefield(Lines, Columns);
}

Grid::~Grid() 
{

}

void Grid::drawBattlefield(int Lines, int Columns)
{
	/*Debug
	printf("Player Character Current Box: Line: %d Column: %d \n", PlayerCurrentLocation->xIndex, PlayerCurrentLocation->yIndex);
	printf("Enemy Character Current Box: Line: %d Column: %d \n", EnemyCurrentLocation->xIndex, EnemyCurrentLocation->yIndex);
	*/

    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* currentgrid = new Types::GridBox();
			currentgrid->xIndex = i;
			currentgrid->yIndex = j;

			bool bOccupiedByPlayer = false;

			if (currentgrid->xIndex == PlayerCurrentLocation->xIndex && currentgrid->yIndex == PlayerCurrentLocation->yIndex)
			{
				/*Debug
				printf("Grids Match\n");
				printf("Player Character Current Box: Line: %d Column: %d \n", currentgrid->xIndex, currentgrid->yIndex);
				*/
				currentgrid->ocupied = true;
				bOccupiedByPlayer = true;

			}
			else if (currentgrid->xIndex == EnemyCurrentLocation->xIndex && currentgrid->yIndex == EnemyCurrentLocation->yIndex)
			{
				/*Debug
				printf("Grids Match\n");
				printf("Enemy Character Current Box: Line: %d Column: %d \n", currentgrid->xIndex, currentgrid->yIndex);
				*/
				currentgrid->ocupied = true;
			}


            if (currentgrid->ocupied)
            {
				if (bOccupiedByPlayer)
				{
					printf("[P]\t");
				}
				else
				{
					printf("[X]\t");
				}
                
            }
            else
            {
                printf("[ ]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}