#include "Battle.h"
//Common

void Battle::NextTrun(bool& turn)
{
	turn = !&turn;
}



//Normal


void NormalBattle::Fight(Character* Player, NormalMonster* monster, int stage)
{
//	Data = monster;

	while (!endBattle)
	{
		if (myTurn)
		{
			PlayerAction();
			//플레이어턴
		}
		else
		{
			//몬스터 턴
		}


	}


	cout << "일반 전투" << endl;
	Player->TakeExp(10);

}

void NormalBattle::PlayerAction()
{
}

void NormalBattle::MonsterAction()
{
}




//Named

void NamedBattle::Fight(Character* Player, NormalMonster* monster, int stage)
{
	cout << "네임드 전투" << endl;
	Player->TakeExp(20);

}



//Boss
//
//void BossBattle::Fight(Character* Player, NormalMonster* monster, int stage)
//{
//
//	cout << "보스 전투" << endl;
//	Player->TakeExp(30);
//
//}
