// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "BattleField.h"
#include <iostream>
#include <time.h>

int main()
{
	/*Makes the Player and Enemy appear at a different random spot each playtrough */
	srand((unsigned int)time(NULL));
	

    BattleField* battleField = new(BattleField);
	battleField->Setup();

	delete battleField;
	battleField = nullptr;
}


