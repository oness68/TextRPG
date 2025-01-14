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
			

		}
		else
		{
			//NamedBattle playBattle;
			//playBattle.Fight(player, stage);

		}
	}
	else
	{
		
		/*NormalMonster monster = CreateNormalMonster();
		NormalBattle B;*/
		//B.setTarget(monster);

	}


}

void BattleManager::CreateMonster(bool isNamde,int stage)
{
	int range;
	if (isNamde)
	{
		range = 3;


		int random = rand() % range;
		switch (random)
		{
		case 0:

			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
		}
	}
	else
	{
		range = 5;
		Goblin goblin;
		/*Wolf wolf;
		Troll troll;
		Slime slime;
		Orc orc;
		int random = rand() % range;
		switch (random)
		{
		case 0:
			readMonster(goblin.GetName(), goblin.GetHealth(), goblin.GetDamage(), goblin.GetExperience(), goblin.GetGold());
			break;
		case 1:
			readMonster(wolf.GetName(), wolf.GetHealth(), wolf.GetDamage(), wolf.GetExperience(), wolf.GetGold());

			break;
		case 2:
			readMonster(troll.GetName(), troll.GetHealth(), troll.GetDamage(), troll.GetExperience(), troll.GetGold());


			break;
		case 3:
			readMonster(slime.GetName(), slime.GetHealth(), slime.GetDamage(), slime.GetExperience(), slime.GetGold());

			break;
		case 4:
			readMonster(orc.GetName(), orc.GetHealth(), orc.GetDamage(), orc.GetExperience(), orc.GetGold());

			break;
		default:
			break;
		}*/
	}

	

}

void BattleManager::readMonster(string _name,int hp, int _attackPower,int _experience,int _gold)
{
	this->monster.name = _name;
	this->monster.HP = hp;
	this->monster.attackPower = _attackPower;
	this->monster.experience = _experience;
	this->monster.gold = _gold;
}




