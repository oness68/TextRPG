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
	std::random_device rd;
	std::mt19937 gen(rd());
	int range;
	if (stage < 20)
	{
		if (isNamde)
		{
			range = 3;
			
			std::uniform_int_distribution<int> dist(0, range-1);

			switch (dist(gen))
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

			std::uniform_int_distribution<int> dist(0, range-1);

			switch (dist(gen))
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





