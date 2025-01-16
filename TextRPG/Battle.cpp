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

void Battle::StageOfDifficulty(int stage)
{
	float multiple = 0.05*stage;
	multiple = multiple + 1.0f;
	battleMonster->SetHealth(battleMonster->GetHealth() * multiple);
	battleMonster->SetExperience(battleMonster->GetExperience() * multiple);
	battleMonster->SetDamage(battleMonster->GetDamage() * multiple);
	battleMonster->SetGold(battleMonster->GetGold() * multiple);
	
}

void Battle::NextTurn(Character* Player)
{
	if (nextTurn)
	{
		if (myTurn)
		{
			Player->TurnEnd();
		}
		myTurn = !myTurn;
	}
}


void Battle::Fight(Character* Player, BaseMonster* monster, int stage) // 전투
{
	Log* logger = Log::GetInstance();
	BattleManager* BM = BattleManager::GetInstance();
	this->battleMonster = monster;
	Image = BM->getMonsterImage();
	StageOfDifficulty(stage);
	saveCharacterState(Player);
	logger->PrintLog(battleMonster->GetName() + "가(이) 등장했다!\n", BM->getMonsterImage(), false);
	Sleep(1000);
	ItemFactory& IFactory = ItemFactory::GetInstance();
	Item* item = IFactory.GenerateItem("하급체력회복포션");
	Item* item2 = IFactory.GenerateItem("중급체력회복포션");
	Player->TakeItem(item);
	Player->TakeItem(item2);
	UpdateInfo(Player);
	while (!endBattle)
	{
		//logger->PrintLog();
		logger->PrintLog("", BM->getMonsterImage(), true);
		logger->PrintLog("플레이어 체력 :" + to_string(Player->GetCurrentHP()) + " : " + to_string(Player->GetMaxHP()) + " 플레이어 공격력 : " + to_string(Player->GetAttackPower())+"\n",false);
		logger->PrintLog(battleMonster->GetName() + " 체력 : " + to_string(battleMonster->GetHealth()) + " 공격력 : " + to_string(battleMonster->GetDamage())+"\n",false);
		if (myTurn)
		{
			PlayerAction(Player);
			
			UpdateInfo(Player);
			Sleep(2000);
			//플레이어턴
		}
		else
		{
			Sleep(1500);

			MonsterAction(Player);
			UpdateInfo(Player);

			//몬스터 턴
			Sleep(2500);
		}

		NextTurn(Player);
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
	
	vector<Inventory> cosumableItems = Player->GetInventoryItems(ItemType::Consumable);

	bool flag = false;
	
	vector<string> menuItems = {
		"공격",
		"아이템 사용",
	};

	vector<function<void()>> actions = 
	{
		[&]() {
			cout << "공격을 선택했습니다." << endl;
			AttackSystem(Player);
			nextTurn = true;
			flag = true;
		},
		[&]() {
			cout << "아이템을 사용합니다." << endl;
			if (cosumableItems.size() > 0)
			{
				UseItem(Player);
				flag = true;
			}
			else
			{
				logger->PrintLog("사용 아이템이 없습니다.\n", false);
			}
			nextTurn = false;
		}

	};

	Menu menuSystem(menuItems, actions);

	// 메뉴 실행
	while (true) {
		menuSystem.DisplayMenu(Image, true, info+"무엇을 해야할까?\n");
		menuSystem.RunMenu(Image, true, info + "무엇을 해야할까?\n");

		if (menuSystem.GetSelectedIndex() < menuItems.size()) {
			break;
		}

		cout << endl; // 메뉴 간격 조정
	}


	
}

void Battle::MonsterAction(Character* Player)
{
	Log* logger = Log::GetInstance();
	
	
	//logger->PrintLog(battleMonster->GetName() + "가(이) 공격했다!\n",false);
	int Damage = 0;
	state = (MonsterState)battleMonster->TakeAction();
	switch (state)
	{
	case Enums::EAttack:
		Damage = battleMonster->GetDamage();

		Player->TakeDamage(Damage);
		logger->PrintLog("플레이어가 " + to_string(Damage) + "의 피해를 입었다.\n", false);
		state = EAttack;
		break;
	case Enums::EDefence:
		state = EDefence;
		break;

	case Enums::EMonsterSkill:
		MonsterSkill(Player);
		break;

	default:
		break;
	}
	//logger->PrintLog();

	nextTurn = true;

}

void Battle::MonsterSkill(Character* Player) // 특수패턴
{
	Log* logger = Log::GetInstance();

	
	int choice;
	vector<string> ActionList = battleMonster->GetcharacterResponseList();
	vector<string> menuItems;
	for (int i = 1; i < ActionList.size(); i++)
	{
		menuItems.push_back(ActionList[i]);
	}

	vector<function<void()>> actions =
	{
		[&]() {
			choice = 1;
		},
		[&]() {
			choice = 2;
		},
		[&]() {
			choice = 3;
		}

	};

	Menu menuSystem(menuItems, actions);

	// 메뉴 실행
	while (true) {
		menuSystem.DisplayMenu(Image, true, info+ ActionList[0]);
		menuSystem.RunMenu(Image, true, info + ActionList[0]);

		if (menuSystem.GetSelectedIndex() < menuItems.size()) {
			break;
		}

		cout << endl; // 메뉴 간격 조정
	}


	int result = battleMonster->GetResponseScore(choice);
	if (result==1)
	{
		battleMonster->TakeDamage(Player->GetAttackPower() * 3);
		logger->PrintLog("좋은 선택이었다!\n", false);
		logger->PrintLog(battleMonster->GetName() + "가(이)" + to_string(Player->GetAttackPower() * 3) + "의 치명적인 피해를 입었다!\n", false);

	}
	else if (result == 2)
	{
		logger->PrintLog("나쁘지 않은 선택이었다!\n", false);
		logger->PrintLog(battleMonster->GetName() + " 에게 피해를 입지 않았다.\n", false);

	}
	else
	{
		Player->TakeDamage(battleMonster->GetDamage()*2);
		logger->PrintLog("나쁜 선택이었다.\n", false);
		logger->PrintLog("플레이어가 " +battleMonster->GetName()+" "+ to_string(battleMonster->GetDamage()*2) + "의 치명적인 피해를 입었다.\n", false);

	}

	
}



void Battle::UseItem(Character* Player)
{
	Log* logger = Log::GetInstance();

	vector<Inventory> cosumableItems = Player->GetInventoryItems(ItemType::Consumable);
	logger->PrintLog("====== Item List =====\n", false);
	vector<string> menuItems;
	
	int i = 0;
	
	for (auto inventory : cosumableItems)
	{
		menuItems.push_back(format("{}. 아이템명 :{}, 수량 :{}", i+1, inventory.item->GetName(), inventory.Count));
		//logger->PrintLog(, false);
		i++;
		
		
	};
	vector<function<void()>> actions;
	
	
	Menu* tempmenuSystem;

	for (int index = 0; index < cosumableItems.size(); index++)
	{
		actions.push_back
		(
			[&]()
			{
				auto selectedItem = cosumableItems[tempmenuSystem->GetSelectedIndex()];
				Player->UseItem(selectedItem.item->GetName());
				Sleep(1000);
			}
		);
	}
	Menu menuSystem(menuItems, actions);
	tempmenuSystem = &menuSystem;
	// 메뉴 실행
	while (true) {
		menuSystem.DisplayMenu(Image, true, info + "무엇을 해야할까?\n");
		menuSystem.RunMenu(Image, true, info + "무엇을 해야할까?\n");

		if (menuSystem.GetSelectedIndex() < menuItems.size()) {
			break;
		}

		cout << endl; // 메뉴 간격 조정
	}

	

}

void Battle::UpdateInfo(Character* Player)
{
	info = Player->GetName() + " => HP : " + to_string(Player->GetCurrentHP()) + " / " + to_string(Player->GetMaxHP()) + " 공격력 : " + to_string(Player->GetAttackPower())+"\n";
	info += battleMonster->GetName() + " => HP : " + to_string(battleMonster->GetHealth()) + " 공격력 : " + to_string(battleMonster->GetDamage()) + "\n";
}

void Battle::LootAction(Character* Player)
{
	Log* logger = Log::GetInstance();
	ItemFactory &IFactory = ItemFactory::GetInstance();
	Player->TakeExp(battleMonster->GetExperience());
	Player->TakeGold(battleMonster->GetGold());
	string itemName = battleMonster->GetRandomItem();
	
	Item* item = IFactory.GenerateItem(itemName);
	Player->TakeItem(item);

	logger->PrintLog(format("{} 에게 {}경험치를 얻었다!\n", battleMonster->GetName(), battleMonster->GetExperience()), false);
	logger->PrintLog(format("{} 에게 {}골드를 얻었다!\n", battleMonster->GetName(), battleMonster->GetGold()), false);
	logger->PrintLog(format("{} 에게 {}을(를) 얻었다\n", battleMonster->GetName(), itemName), false);
	Sleep(2000);
	logger->PrintLog("");
	//Player->TakeItem()
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
	bool flag = false;
	bool isHit;
	int Damage = 0;
	int headProb = 30;
	int bodyProb = 80;
	vector<string> menuItems = {
		format("머리 {}%",headProb),
		format("몸통 {}%",bodyProb),
	};

	vector<function<void()>> actions =
	{
		[&]() {
			isHit = RandomSuccess(headProb);
			if (isHit)
			{
				logger->PrintLog("머리 공격이 성공했다!\n", false);
				Damage = Player->GetAttackPower() * 2;
				if (state == EDefence)
				{
					logger->PrintLog("몬스터가 방어태세를 취했습니다. 감소된 피해를 입힙니다.\n", false);

					Damage *= 0.6;
				}
				battleMonster->TakeDamage(Damage);

				logger->PrintLog(battleMonster->GetName() + "가(이)" + to_string(Damage) + "의 피해를 입었다!\n",false);
			}
			else
			{
				logger->PrintLog("공격이 빗나갔다.\n",false);
				logger->PrintLog(battleMonster->GetName() + "가(이) 피해를 입지 않았다.\n",false);
			}

			flag = true;
			//log
		},
		[&]() {
			isHit = RandomSuccess(bodyProb);
			if (isHit)
			{
				logger->PrintLog("공격이 성공했다!\n", false);
				Damage = Player->GetAttackPower();
				if (state == EDefence)
				{
					logger->PrintLog("몬스터가 방어태세를 취했습니다. 감소된 피해를 입힙니다.\n", false);
					Damage *= 0.6;
				}
				battleMonster->TakeDamage(Damage);

				logger->PrintLog(battleMonster->GetName() + "가(이)" + to_string(Damage) + "의 피해를 입었다!\n", false);

			}
			else
			{
				logger->PrintLog("공격이 빗나갔다.\n",false);
				logger->PrintLog(battleMonster->GetName() + "가(이) 피해를 입지 않았다.\n",false);
			}
			flag = true;
			//log
		}

	};

	Menu menuSystem(menuItems, actions);

	// 메뉴 실행
	while (true) 
	{
		menuSystem.DisplayMenu(Image, true, info + "어느곳을 공격할까?\n");
		menuSystem.RunMenu(Image, true, info + "어느곳을 공격할까?\n");

		if (menuSystem.GetSelectedIndex() < menuItems.size()) {
			break;
		}

		cout << endl; // 메뉴 간격 조정
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
			logger->PrintLog("전투에서 승리했다!\n", false);
			isWin = true;
			Sleep(2000);

		}
		else //패배
		{
			logger->PrintLog("플레이어 사망.\n",false);
			isWin = false;
			Player = nullptr;
			Sleep(2000);

		}
	}
}
