// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "BattleField.h"
#include <iostream>
#include <time.h>

int main()
{
    BattleField* battleField = new(BattleField);
	delete battleField;
	battleField = nullptr;
}


