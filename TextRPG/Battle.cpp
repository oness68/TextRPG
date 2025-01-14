#include "Battle.h"
//Common




void Battle::restoreCharacterState(Character* player)
{
	player->SetAttackPower(CharacterData.Power);
	player->SetMaxHP(CharacterData.MaxHP);
}

void Battle::saveCharacterState(Character* player)
{
	CharacterData.Power = player->GetAttackPower();
	CharacterData.CurrentHP = player->GetCurrentHP();
	CharacterData.MaxHP = player->GetMaxHP();
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
	logger->PrintLog(battleMonster->GetName() + "가(이) 등장했다!\n");
	while (!endBattle)
	{
		logger->PrintLog("플레이어 체력 :" + to_string(Player->GetCurrentHP()) + " : " + to_string(Player->GetMaxHP()) + " 플레이어 공격력 : " + to_string(Player->GetAttackPower())+"\n");
		logger->PrintLog(battleMonster->GetName() + " 체력 : " + to_string(battleMonster->GetHealth()) + " 공격력 : " + to_string(battleMonster->GetDamage())+"\n");
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
	logger->PrintLog("무엇을 해야할까?\n1.공격\t2.아이템사용\n");
	int choice = Input(1, 2);
	switch (choice)
	{
	case 1:
		AttackSystem(Player);
		break;
	case 2:
		logger->PrintLog("아이템사용!\n");
		//아이템
		break;
	default:
		break;
	}
}

void Battle::MonsterAction(Character* Player)
{
	Log* logger = Log::GetInstance();
	
	Player->TakeDamage(battleMonster->GetDamage());
	logger->PrintLog(battleMonster->GetName() + "가(이) 공격했다!\n");
	logger->PrintLog("플레이어가 " + to_string(battleMonster->GetDamage()) + "의 피해를 입었다.\n");
	

}

void Battle::LootAction(Character* Player)
{
	Player->TakeExp(battleMonster->GetExperience());
	Player->TakeGold(battleMonster->GetGold());
	//battleMonster.
}

bool Battle::RandomSuccess(int probability)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 100);
	if (dist(gen) <= probability)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Battle::AttackSystem(Character* Player)
{
	Log* logger = Log::GetInstance();
	logger->PrintLog("어느곳을 공격할까?\n1.머리(40%)\t2.몸통(80%)\n");
	bool flag = false;
	bool isHit;
	while (!flag)
	{
		int choice = Input(1, 2);
		switch (choice)
		{
		case 1:
			isHit = RandomSuccess(40);
			if (isHit)
			{
				battleMonster->TakeDamage(Player->GetAttackPower() * 2);
				logger->PrintLog("머리 공격이 성공했다!\n");
				logger->PrintLog(battleMonster->GetName() + "가(이)"+ to_string(Player->GetAttackPower() * 2)+"의 치명적인 피해를 입었다!\n");
			}
			else
			{
				logger->PrintLog("공격이 빗나갔다.\n");
				logger->PrintLog(battleMonster->GetName() + "가(이) 피해를 입지 않았다.\n");
			}
			
			flag = true;
			//log
			break;
		case 2:
			isHit = RandomSuccess(80);
			if (isHit)
			{
				battleMonster->TakeDamage(Player->GetAttackPower() * 2);
				logger->PrintLog("공격이 성공했다!\n");
				logger->PrintLog(battleMonster->GetName() + "가(이)" + to_string(Player->GetAttackPower()) + "의 피해를 입었다!\n");
			}
			else
			{
				logger->PrintLog("공격이 빗나갔다.\n");
				logger->PrintLog(battleMonster->GetName() + "가(이) 피해를 입지 않았다.\n");
			}
			flag = true;
			//log
			break;
		default:
			logger->PrintLog("입력 범위 오류 다시 선택하세요.\n");
			break;
		}
	}
	

	
}

void Battle::isEndBattle(Character* Player)
{
	Log* logger = Log::GetInstance();
	if (Player->GetCurrentHP() < 1 || battleMonster->GetHealth()<1)
	{
		endBattle = true;
	}

	if (endBattle)
	{
		if (Player->GetCurrentHP() > 0)//승리
		{
			logger->PrintLog("전투에서 승리했다!\n");
			isWin = true;
		}
		else //패배
		{
			logger->PrintLog("플레이어 사망.\n");
			isWin = false;
			Player = nullptr;
		}
	}
}
