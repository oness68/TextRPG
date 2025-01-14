#include "BattleManager.h"


BattleManager* BattleManager::Battleinstance = nullptr;


BattleManager* BattleManager::GetInstance()
{

	if (Battleinstance == nullptr)
		Battleinstance = new BattleManager();

	return Battleinstance;

}

void BattleManager::BeginBattle(Character* player, int stage)
{
	

	if (stage % 5 == 0)
	{
		if (stage == 20)
		{
			//BossBattle playBattle;
			//playBattle.Fight(player, stage);

		}
		else
		{
			//NamedBattle playBattle;
			//playBattle.Fight(player, stage);

		}
	}
	else
	{
		
		NormalMonster monster = CreateNormalMonster();
		//NormalBattle n;
	}


}

NormalMonster BattleManager::CreateNormalMonster()
{
	Goblin goblin;
	Orc orc;
	Troll troll;
	Wolf wolf;
	Slime slime;

	int num = (rand() % 5)+1;
	
	switch (num)
	{
	case 1:
		return goblin;

	case 2:
		return orc;

	case 3:
		return troll;

	case 4:
		return wolf;

	case 5:
		return slime;

	default:
		return goblin;
	}

}
