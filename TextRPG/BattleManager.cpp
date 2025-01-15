#include "BattleManager.h"


BattleManager* BattleManager::Battleinstance = nullptr;

BattleManager* BattleManager::GetInstance()
{

	if (Battleinstance == nullptr)
		Battleinstance = new BattleManager();

	return Battleinstance;

}


void BattleManager::setMonster(BaseMonster* monster)
{
	this->monster = monster;
}

void BattleManager::BeginBattle(Character* player, int stage)
{
	
	if (stage % 5 == 0)
	{
		CreateMonster(true, stage);


	}
	else
	{
		CreateMonster(false, stage);
		Battle battle;
		battle.Fight(player, monster, stage);

		/*NormalMonster monster = CreateNormalMonster();
		NormalBattle B;*/
		//B.setTarget(monster);

	}


}

void BattleManager::CreateMonster(bool isNamde,int stage)
{
	monster = nullptr;
	int range;
	if (stage < 20)
	{
		if (isNamde)
		{
			range = 3;


			int random = rand() % range;
			switch (random)
			{
			case 0:
				setMonster(new GoblinRider());
				break;
			case 1:
				setMonster(new TwinHeadTroll());

				break;
			case 2:
				setMonster(new Treant());
				break;
			default:
				break;
			}
		}
		else
		{
			range = 5;

			int random = rand() % range;
			switch (random)
			{
			case 0:
				setMonster(new Goblin());
				break;
			case 1:
				setMonster(new Orc());
				break;
			case 2:
				setMonster(new Troll());
				break;
			case 3:
				setMonster(new Wolf());
				break;
			case 4:
				setMonster(new Slime());
				break;
			default:
				break;
			}
		}
	}
	else
	{
		setMonster(new Dragon());

	}
	

	

}





