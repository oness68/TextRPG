#include "GameManager.h"
#include "Log.h"

#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

namespace GameManger {

	// 싱글톤 인스턴스 반환
	GameManger& GameManger::GetInstance()
	{
		static GameManger instance;

		return instance;
	}

	// 상점 방문 함수
	void GameManger::VisitShop(Character* player)
	{
		Log::GetInstance()->PrintLog("상점에 방문했습니다!\n", (int)EShop, true);

		Shop shop;

		vector<string> menuItems = {
			"구매",
			"판매",
			"강화",
			"인벤토리",
			"나가기"
		};

		vector<function<void()>> actions = {
			[&]() {
				cout << "구매를 선택했습니다." << endl;
				shop.BuyItem(*player);
			},
			[&]() {
				cout << "판매를 선택했습니다." << endl;
				shop.SellItem(*player);
			},
			[&]() {
				cout << "강화를 선택했습니다." << endl;
				shop.UseEnchancer(*player);
			},
			[&]() {
				cout << "인벤토리를 확인합니다." << endl;
				player->DisplayInventory();
			},
			[&]() {
				cout << "상점을 떠납니다." << endl;
			}
		};

		Menu menuSystem(menuItems, actions);

		// 메뉴 실행
		while (true) {
			menuSystem.DisplayMenu((int)EShop, true);
			menuSystem.RunMenu((int)EShop, true);

			if (menuSystem.GetSelectedIndex() == 4) {
				break;
			}

			cout << endl; // 메뉴 간격 조정
		}
	}

	// 전투 시작 함수
	void GameManger::BeginBattle(Character* player, int stage)
	{
		BattleManager* BM = BattleManager::GetInstance();

		BM->BeginBattle(player, stage);
		// TODO: 리턴 처리
	}

	// 휴식 장소 방문 함수
	void GameManger::VisitRest(Character* player)
	{
		int currentHP = player->GetCurrentHP()-70;
		int maxHP = player->GetMaxHP();
		Log* logger = Log::GetInstance();
		if (maxHP / 2 > currentHP)
		{
			player->SetCurrentHP(currentHP + (maxHP / 2));
			string restLog = "플레이어의 체력이 " + to_string(maxHP / 2) + "회복되었습니다.(현재 체력 : " + to_string(player->GetCurrentHP()) + ")\n";
			logger->PrintLog(restLog, ERest);
		}
		else
		{
			player->SetCurrentHP(maxHP);
			string restLog = "플레이어의 체력이 최대(" + to_string(maxHP) + ")로 회복되었습니다.\n";
			logger->PrintLog(restLog, ERest);
		}
	}

	// 버프룸 방문 함수
	void GameManger::VisitBuffRoom(Character* player)
	{
		auto buffRoom = GenerateRandomRoom(buffRoomProbabilities);  //랜덤으로 방 생성

		BuffCoinToss(player);
		/*switch (buffRoom)
		{
		case Dice:
			BuffDice(player);
			break;
		case Number:
			BuffNumber(player);
			break;
		case Rand:
			BuffRand(player);
			break;
		case Game:
			BuffCoinToss(player);
			break;
		default:
			break;
		}*/
		/*for (size_t i = 0; i < buffRooms.size(); ++i) {
			std::cout << i + 1 << ". Buff Room: " << BuffRoomToString(buffRooms[i]) << std::endl;
		}*/
	}

	void GameManger::BuffDice(Character* player)
	{
		//1 : 깎인 체력의 절반 회복
		//2 : 공격력 5 증가
		//3 : 골드 1000 획득
		//4 : 현재 체력의 5분의 1만큼 체력 감소
		//5 : 공격력 5 감소
		//6 : 골드 1000 획득
		Log* logger = Log::GetInstance();
		std::random_device random;
		std::mt19937 generator(random());
		int diceResult;
		int currentHP = player->GetCurrentHP();
		int maxHP = player->GetMaxHP();
		int healAmount = (maxHP - currentHP) / 2;
		int damage = (currentHP) / 5;
		int goldTake = 1000;
		string diceLog = "랜덤 주사위 방에 도착했습니다.(1~3 : 이로운 효과, 4~6 : 해로운 효과)";
		diceLog += "\n당신의 운을 시험해보세요.";
		logger->PrintLog(diceLog, EBuff);
		std::uniform_int_distribution<int> distribution(1, 6);  //랜덤 주사위 값
		diceResult = distribution(generator);
		diceLog += "\n주사위 값 : " + to_string(diceResult) + "\n";
		switch (diceResult)
		{
		case 1:
			diceLog += "플레이어의 체력을 깎인 체력의 반 만큼 회복합니다.\n";
			if (currentHP == maxHP)
			{
				diceLog += "이미 플레이어의 체력이 최대입니다.\n";
				Sleep(3000);
				logger->PrintLog(diceLog, EBuff);
				break;
			}
			else
			{
				diceLog += "깎인 체력을 반(" + to_string(healAmount) + ") 회복했습니다.\n";
				Sleep(3000);
				logger->PrintLog(diceLog, EBuff);
			}
			break;
		case 2:
			player->SetAttackPower(player->GetAttackPower() + 5);
			diceLog += "플레이어의 공격력이 5만큼 상승합니다.";
			diceLog += "현재 공격력 : " + to_string(player->GetAttackPower()) + '\n';
			Sleep(3000);
			logger->PrintLog(diceLog, EBuff);
			break;
		case 3:
			player->TakeGold(goldTake);
			diceLog += to_string(goldTake) + "gold를 획득했습니다!\n";
			Sleep(3000);
			logger->PrintLog(diceLog, EBuff);
			break;
		case 4:
			player->SetCurrentHP(currentHP - damage);   //현재 체력의 5분의 1만큼 체력 감소
			diceLog += "현재 체력의 5분의 1만큼 체력이 감소합니다.\n";
			diceLog += "\n현재 체력 : " + to_string(player->GetCurrentHP()) + "\n";
			Sleep(3000);
			logger->PrintLog(diceLog, EDeBuff);
			break;
		case 5:
			player->SetAttackPower(player->GetAttackPower() - 5);
			diceLog += "플레이어의 공격력이 5만큼 감소합니다.\n";
			diceLog += "현재 공격력 : " + to_string(player->GetAttackPower()) + '\n';
			Sleep(3000);
			logger->PrintLog(diceLog, EDeBuff);
			break;
		case 6:
			player->TakeGold(goldTake * -1);
			diceLog += to_string(goldTake) + "gold를 잃었습니다!\n";
			Sleep(3000);
			logger->PrintLog(diceLog, EDeBuff);
			break;
		default:
			cout << "주사위 값 범위 이탈 에러 발생\n";  //예외처리 프로그램 종료
			exit(1);
			break;
		}
	}

	void GameManger::BuffNumber(Character* player)
	{
		Log* logger = Log::GetInstance();

		std::random_device random;
		std::mt19937 generator(random());
		std::uniform_int_distribution<int> distribution(1, 100);
		int secretNumber = distribution(generator);
		int guess;
		int attempts = 3;
		int score = 0;
		string numberLog = "";

		numberLog += "숫자 맞추기 게임에 오신 것을 정말 진심으로 환영합니다!\n";
		numberLog += "1부터 100 사이의 숫자를 맞춰보세요. 기회는 3번입니다!\n";
			/*logger->PrintLog("숫자 맞추기 게임에 오신 것을 정말 진심으로 환영합니다!\n", EBuff);
			logger->PrintLog("1부터 100 사이의 숫자를 맞춰보세요. 기회는 3번입니다!\n", EBuff);*/

		logger->PrintLog(numberLog, EBuff);
		Sleep(3000);
		numberLog = "";
		for (int i = 1; i <= attempts; ++i) {
			logger->PrintLog(to_string(i) + "번째 시도: ", EBuff);
			cin >> guess;

			if (guess == secretNumber) {
				/*logger->PrintLog("축하합니다! 숫자를 맞췄습니다!\n", EBuff);
				score = (attempts - i + 1) * 50;
				logger->PrintLog("획득 점수: " + score, EBuff);
				logger->PrintLog("\n", EBuff);*/
				numberLog += "축하합니다! 숫자를 맞췄습니다!\n";
				score = (attempts - i + 1) * 50;
				numberLog += "획득 점수: " + to_string(score) + "\n";
				logger->PrintLog(numberLog, EBuff);
				return;
			}
			else if (guess < secretNumber) {
				logger->PrintLog("힌트: 더 큰 숫자입니다!\n", EBuff);
				Sleep(3000);
			}
			else {
				logger->PrintLog("힌트: 더 작은 숫자입니다!\n", EBuff);
				Sleep(3000);
			}
		}
		/*logger->PrintLog("아쉽습니다. 기회를 모두 소진했습니다.\n", EBuff);
		logger->PrintLog("정답은 " + secretNumber, EBuff);
		logger->PrintLog("\n", EBuff);
		logger->PrintLog("획득 점수: " + score, EBuff);
		logger->PrintLog("\n", EBuff);*/
		numberLog = "";
		numberLog += "아쉽습니다. 기회를 모두 소진했습니다.\n";
		numberLog += "정답은 " + to_string(secretNumber);
		numberLog += "획득 점수: " + to_string(score) + "\n";
		logger->PrintLog(numberLog, EBuff);
	}

	void GameManger::BuffRand(Character* player)
	{
		//TODO: 아이템 랜덤 변경 (등급상향)
	}

	void GameManger::BuffCoinToss(Character* player)
	{
		Log* logger = Log::GetInstance();
		int solution = 1;
		int count = 0;
		int choice = 0;
		string str = "";
		std::random_device random;
		std::mt19937 generator(random());
		std::uniform_int_distribution<int> distribution(1, 2);  //동전 앞(1), 뒷면(2)

		logger->PrintLog("동전 던지기 방에 도착했습니다.\n", EBuff);
		Sleep(3000);
		while (true)
		{
			
			int randomNumber = distribution(generator);
			string result = (randomNumber == 1 ? "앞면" : "뒷면");
			while (true)
			{
				logger->PrintLog("동전을 던져 나올 면을 맞춰보세요.(1 : 앞면, 2 : 뒷면)\n", EBuff);
				cin >> choice;
				switch (choice)
				{
				case 1:
					str += to_string(count + 1) + "번 째 선택 : 앞면";
					break;
				case 2:
					str += to_string(count + 1) + "번 째 선택 : 뒷면";
					break;
				default:
					logger->PrintLog("", EBuff);
					logger->PrintInputError();
					break;
				}
				if (choice == 1 || choice == 2) break;
			}
			str += "    결과 : " + result;
			if (choice == randomNumber)
			{
				str += "\n맞췄습니다!";
				count++;
			}
			else
			{
				str += "\n틀렸습니다!";
			}
			logger->PrintLog(str, EBuff);
			Sleep(3000);
			str = "";
		}
		//while (solution) {
		//	int choice = 0;
		//	int RandomNumber = distribution(generator);
		//	string result;
		//	str += "동전을 던져 나올 면을 선택해주세요.(1 : 앞면, 2 : 뒷면)(현재 맞춘 개수 : ";
		//	str += to_string(count) + ")\n";
		//	logger->PrintLog(str, EBuff);
		//	//logger->PrintLog(str + to_string(count) + ")\n");
		//	//string result = (RandomNumber == 1 ? "앞면" : "뒷면");
		//	
		//	str = "";
		//	str += "동전 결과 : " + result + "\n";
		//	//logger->PrintLog("동전 결과 : " + result + "\n");
		//	if (choice != 1 && choice != 2)
		//	{
		//		logger->PrintLog("잘못된 입력입니다. 1 또는 2를 입력해주세요\n");
		//		continue;
		//	}
		//	else if (RandomNumber != choice)
		//	{
		//		logger->PrintLog("게임 종료! 당신의 선택이 틀렸습니다. (현재 맞춘 개수 : "+to_string(count) +")\n");
		//		//맞춘 개수 기반 버프 부여 및 게임 종료
		//		solution = 0;
		//	}
		//	else
		//	{
		//		logger->PrintLog("당신의 선택이 옳았습니다.\n");
		//		count++;
		//	}
		//}

	}

	// 현재 스테이지 반환 함수
	int GameManger::GetCurrentStage()
	{
		return stage;
	}

	// 스테이지 단계 설정
	void GameManger::SetStage(int num)
	{
		stage = num;
	}

	// 게임시작
	void GameManger::BeginPlay(Character* player)
	{
		int stage = 1;

		Log* logger = Log::GetInstance();

		// player->DisplayStatus();
		 VisitBuffRoom(player);
		// VisitShop(player);
		// VisitRest(player);
		/*
		SetStage(stage);
		BeginBattle(player, stage);
		SetStage(++stage);
		*/
		//while (stage <= 20)
		//{
		//	auto stageRooms = GenerateTwoRandomRooms(roomProbabilities, std::optional<StageRooms>(StageRooms::Battle));
		//	
		//	for (size_t i = 0; i < stageRooms.size(); ++i) {
		//		cout << i + 1 << ". Stage Room: " << StageRoomToString(stageRooms[i]) << endl;
		//	}

		//	vector<string> menu = {
		//		StageRoomToString(stageRooms[0]),
		//		StageRoomToString(stageRooms[1])
		//	};

		//	vector<function<void()>> actions;

		//	for (const auto stage : stageRooms)
		//	{
		//		switch (stage)
		//		{
		//		case Market:
		//			// player는 게임 도중에 바뀔 수 있는 값이라면, 그 시점에서 player가 변경된 상태를 반영하게 됩니다.
		//			actions.push_back([&]() {
		//				logger->PrintLog("이상한 건물에 들어섰다.\n");
		//				VisitShop(player);
		//			});
		//			break;
		//		case Rest:
		//			actions.push_back([&]() {
		//				logger->PrintLog("잠시 쉴수 있을꺼 같다.\n");
		//				VisitRest(player);
		//			});
		//			break;
		//		case Battle:
		//			actions.push_back([&]() {
		//				logger->PrintLog("어맛!\n");
		//				BeginBattle(player, stage);
		//			});
		//			break;
		//		default:
		//			actions.push_back([&]() {
		//				logger->PrintLog("여긴 어디지...?\n");
		//				VisitBuffRoom(player);
		//			});
		//			break;
		//		}
		//	}

		//	Menu menuSystem(menu, actions);

		//	// 메뉴 실행
		//	while (true) {
		//		menuSystem.DisplayMenu((int)ECharacter, true);
		//		menuSystem.RunMenu((int)ECharacter, true);

		//		if (menuSystem.GetSelectedIndex() == 4) {
		//			break;
		//		}

		//		cout << endl; // 메뉴 간격 조정
		//	}

		//	SetStage(++stage);
		//	/*
		//	int choice;
		//	cout << "들어갈 방 번호 (1 또는 2 입력): " << endl;
		//	std::cin >> choice;

		//	if (choice == 1 || choice == 2) {
		//		StageRooms selectedRoom = stageRooms[choice - 1];

		//		switch (selectedRoom) {
		//		case Market:
		//			logger->PrintLog("이상한 건물에 들어섰다.\n");
		//			VisitShop(player);
		//			break;
		//		case Rest:
		//			logger->PrintLog("잠시 쉴수 있을꺼 같다.\n");
		//			VisitRest(player);
		//			break;
		//		case Battle:
		//			logger->PrintLog("어맛!\n");
		//			BeginBattle(player, stage);
		//			break;
		//		default:
		//			logger->PrintLog("여긴 어디지...?\n");
		//			VisitBuffRoom(player);
		//			break;
		//		}
		//	}
		//	else {
		//		logger->PrintLog("잘못된 입력입니다. 다시 시도하세요.\n");
		//		continue;
		//	}

		//	SetStage(++stage);
		//	*/
		//}
	}
	
} // namespace GameManger