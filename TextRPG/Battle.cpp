#include "Battle.h"
//Common




void Battle::restoreCharacterState(Character* player)
{
	player->setAttackPower(CharacterData.Power);
	player->setMaxHP(CharacterData.HP);
}

void Battle::saveCharacterState(Character* player)
{
	CharacterData.Power = player->GetAcctackPower();
	CharacterData.HP = player->getMaxHP();
}

void Battle::StageOfDifficulty()
{
}

void Battle::NextTurn()
{
	myTurn = !myTurn;
}

int Battle::Input(int min,int max)
{

	int input;
	cin >> input;
	if (min > input || max < input)
	{
		input = 0;
	}

	return input;
}

void Battle::Fight(Character* Player, BaseMonster* monster, int stage) // 전투
{
	Log* logger = Log::GetInstance();
	this->battleMonster = monster;
	saveCharacterState(Player);
	string str = battleMonster->GetName() + "이(가) 등장하였다!\n";
	logger->PrintLog(str, this);
	while (!endBattle)
	{
		if (myTurn)
		{
			PlayerAction(Player);
			//플레이어턴
		}
		else
		{
			MonsterAction(Player);
			//몬스터 턴
		}

		NextTurn();
		isEndBattle(Player);
	}

	if (isWin)
	{
		LootAction(Player);
	}


}



void Battle::PlayerAction(Character* Player)
{
	Log* logger = Log::GetInstance();
	string str ="1.공격\t2.아이템사용\n";
	logger->PrintLog(str, this);
	int choice = Input(1, 2);
	switch (choice)
	{
	case 1:
		AttackSystem(Player);
		break;
	case 2:
		//아이템
		break;
	default:
		break;
	}
}

void Battle::MonsterAction(Character* Player)
{
	Player->TakeDamage(battleMonster->GetDamage());

}

void Battle::LootAction(Character* Player)
{
	Player->TakeExp(battleMonster->GetExperience());
	Player->TakeGold(battleMonster->GetGold());
	//battleMonster.
}

void Battle::AttackSystem(Character* Player)
{
	

	cout << "1.머리\t2.몸통\n";
	bool flag = false;

	while (!flag)
	{
		int choice = Input(1, 2);
		switch (choice)
		{
		case 1:

			battleMonster->TakeDamage(Player->GetAcctackPower() * 1.2);
			flag = true;
			//log
			break;
		case 2:
			battleMonster->TakeDamage(Player->GetAcctackPower());
			flag = true;
			//log
			break;
		default:
			cout << "다시입력" << endl;
			break;
		}
	}
	

	
}

void Battle::isEndBattle(Character* Player)
{
	if (Player->getCurrnetHP() < 1 || battleMonster->GetHealth()<1)
	{
		endBattle = true;
	}

	if (endBattle)
	{
		if (Player->getCurrnetHP() > 0)
		{
			isWin = true;
		}
		else
		{
			isWin = false;
			Player = nullptr;
		}
	}
}
