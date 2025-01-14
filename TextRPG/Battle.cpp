#include "Battle.h"
//Common

//void Battle::NextTrun(bool& turn)
//{
//	turn = !&turn;
//}


void Battle::MonsterAction()
{

}

void Battle::StageOfDifficulty()
{
}

void Battle::NextTurn(bool& flag)
{
	flag = !flag;
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

void Battle::Fight(Character* Player, int stage)
{

	while (!endBattle)
	{
		if (myTurn)
		{
			PlayerAction(Player);
			//플레이어턴
		}
		else
		{
			MonsterAction();
			//몬스터 턴
		}

		NextTurn(myTurn);
	}


	cout << "일반 전투" << endl;
	Player->TakeExp(10);
}

void Battle::PlayerAction(Character* Player)
{
	cout << "1.공격\t2.아이템사용\n";
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

void Battle::AttackSystem(Character* Player)
{

	cout << "1.머리\t2.몸통\n";
	int choice = Input(1, 2);
	switch (choice)
	{
	case 1:
		//monster->TakeDamage(Player->GetAcctackPower()*1.2f);
		break;
	case 2:
		//monster->TakeDamage(Player->GetAcctackPower());

		break;
	default:
		break;
	}
}
