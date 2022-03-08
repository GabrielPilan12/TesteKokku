#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>
#include <vector>

using namespace std;

BattleField::BattleField() {
    
    grid = new Grid(5, 5);
    AllPlayers = new list<Character>();
    int currentTurn = 0;
	int numberOfPossibleTiles =  grid->grids.size(); //Can fix the warning with Auto
    Setup();
}

void BattleField::Setup()
{
    GetPlayerChoice();
}

void BattleField::GetPlayerChoice()
{
    //asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");

    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer \n");
    //store the player choice in a variable
    std::string PlayerChoiceInput;

    std::getline(std::cin, PlayerChoiceInput);
	
	int ChoiceNumber = stoi(PlayerChoiceInput);

    switch ((ChoiceNumber))
    {
    case 1:
        CreatePlayerCharacter(ChoiceNumber);
        break;
    case 2:
        CreatePlayerCharacter(ChoiceNumber);
        break;
    case 3:
        CreatePlayerCharacter(ChoiceNumber);
        break;
    case 4:
        CreatePlayerCharacter(ChoiceNumber);
        break;
    default:
        GetPlayerChoice();
        break;
    }
}

void BattleField::CreatePlayerCharacter(int classIndex)
{

    Types::CharacterClass* characterClass = (Types::CharacterClass*)classIndex;
    printf("Player Class Choice: {characterClass}\n");
    
	//TODO - 1 Fix This
    PlayerCharacter = std::make_shared<Character>(*characterClass);
    
    PlayerCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 0;

    CreateEnemyCharacter();

}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables
    int randomInteger = GetRandomInt(1, 4);
    Types::CharacterClass enemyClass = (Types::CharacterClass)randomInteger;
    printf("Enemy Class Choice: {enemyClass}");
	EnemyCharacter = shared_ptr<Character>(new Character(enemyClass));
    //EnemyCharacter =  new Character(enemyClass);
    EnemyCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 1;
    StartGame();

}

void BattleField::StartGame()
{
    //populates the character variables and targets
	//std::make_shared<Character>(EnemyCharacter->target) = PlayerCharacter;
	//TODO - 2 Fix This
	//EnemyCharacter->target = &PlayerCharacter;
	//TODO - 3 Fix This
	//PlayerCharacter->target = *EnemyCharacter;
    AllPlayers->push_back(*PlayerCharacter);
    AllPlayers->push_back(*EnemyCharacter);
    AlocatePlayers();
    StartTurn();

}

void BattleField::StartTurn() {

    if (currentTurn == 0)
    {
        //AllPlayers.Sort();  
    }
    std::list<Character>::iterator it;

    for (it = AllPlayers->begin(); it != AllPlayers->end(); ++it) {
        it->StartTurn(grid);
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    if (PlayerCharacter->Health == 0)
    {
        return;
    }
    else if (EnemyCharacter->Health == 0)
    {
        printf("\n");

        // endgame?

        printf("\n");

        return;
    }
    else
    {
        printf("\n");
        printf("Click on any key to start the next turn...\n");
        printf("\n");

        //TODO
        //ConsoleKeyInfo key = Console.ReadKey();
        StartTurn();
    }
}

int BattleField::GetRandomInt(int min, int max)
{
	return rand() % max + min;
}

void BattleField::AlocatePlayers()
{
    AlocatePlayerCharacter();

}

void BattleField::AlocatePlayerCharacter()
{
    int random = 0;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;

    if (!RandomLocation->ocupied)
    {
        //Types::GridBox* PlayerCurrentLocation = RandomLocation;
        PlayerCurrentLocation = &*l_front;
        l_front->ocupied = true;
        PlayerCharacter->currentBox = *l_front;
        AlocateEnemyCharacter();
    }
    else
    {
        AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    
    int random = 24;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;
    
    if (!RandomLocation->ocupied)
    {
        EnemyCurrentLocation = &*l_front;
        l_front->ocupied = true;
        EnemyCharacter->currentBox = *l_front;
        grid->drawBattlefield(5, 5);
    }
    else
    {
        AlocateEnemyCharacter();
    }


}