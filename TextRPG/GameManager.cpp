#include "GameManager.h"
#include "Log.h"
#include "ProcessInput.h"

#include <iostream>
#include <string>

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
			menuSystem.DisplayMenu((int)EShop, true, "여기는 정보가 들어갈꺼에요\n");
			menuSystem.RunMenu((int)EShop, true, "여기는 정보가 들어갈꺼에요\n");

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

	// 휴식 장소 방문 함수 구현 완료 - 채규혁
	void GameManger::VisitRest(Character* player)
	{
		int currentHP = player->GetCurrentHP();
		int maxHP = player->GetMaxHP();
		Log* logger = Log::GetInstance();
		if (maxHP / 2 > currentHP)	//현재 체력이 전체 체력의 절반보다 낮으면 전체 체력의 반만큼 회복
		{
			player->SetCurrentHP(currentHP + (maxHP / 2));
			string restLog = "플레이어의 체력이 " + to_string(maxHP / 2) + "회복되었습니다.(현재 체력 : " + to_string(player->GetCurrentHP()) + ")\n";
			logger->PrintLog(restLog, ERest);
		}
		else	//최대로 회복
		{
			player->SetCurrentHP(maxHP);
			string restLog = "플레이어의 체력이 최대(" + to_string(maxHP) + ")로 회복되었습니다.\n";
			logger->PrintLog(restLog, ERest);
		}
		PI::isInputEnabled = false;
		Sleep(3000);
		PI::ClearInputBuffer();
		PI::isInputEnabled = true;
	}

	// 버프룸 방문 함수
	void GameManger::VisitBuffRoom(Character* player)
	{
		BuffRooms buffRoom = GenerateRandomRoom(buffRoomProbabilities);  //랜덤으로 방 생성

		switch (buffRoom)
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
		}
	}

	//구현 완료 - 채규혁
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
		std::uniform_int_distribution<int> distribution(1, 6);  //랜덤 주사위 값
		int diceResult = distribution(generator);
		int currentHP = player->GetCurrentHP();
		int maxHP = player->GetMaxHP();
		int healAmount = (maxHP - currentHP) / 2;
		int damage = (currentHP) / 5;
		int goldTake = 1000;

		string diceLog = "랜덤 주사위 방에 도착했습니다.(1~3 : 이로운 효과, 4~6 : 해로운 효과)";
		diceLog += "\n당신의 운을 시험해보세요.";
		logger->PrintLog(diceLog, EBuff);
		Sleep(3000);

		diceLog += "\n주사위 값 : " + to_string(diceResult) + "\n";
		switch (diceResult)
		{
		case 1:
			diceLog += "플레이어의 체력을 깎인 체력의 반 만큼 회복합니다.\n";
			if (currentHP == maxHP)
			{
				diceLog += "이미 플레이어의 체력이 최대입니다.\n";
				logger->PrintLog(diceLog, EBuff);
				break;
			}
			else if (currentHP < maxHP)
			{
				player->SetCurrentHP(healAmount);
				diceLog += "깎인 체력을 반(" + to_string(healAmount) + ") 회복했습니다.\n";
				logger->PrintLog(diceLog, EBuff);
			}
			break;
		case 2:
			player->AddAttackPower(5);
			diceLog += "플레이어의 공격력이 5만큼 상승합니다.";
			diceLog += "현재 공격력 : " + to_string(player->GetAttackPower()) + '\n';
			logger->PrintLog(diceLog, EBuff);
			break;
		case 3:
			player->TakeGold(goldTake);
			diceLog += to_string(goldTake) + "gold를 획득했습니다!\n";
			logger->PrintLog(diceLog, EBuff);
			break;
		case 4:
			player->SetCurrentHP(currentHP - damage);   //현재 체력의 5분의 1만큼 체력 감소
			diceLog += "현재 체력의 5분의 1만큼 체력이 감소합니다.\n";
			diceLog += "현재 체력 : " + to_string(player->GetCurrentHP()) + "\n";
			logger->PrintLog(diceLog, EDeBuff);
			break;
		case 5:
			player->AddAttackPower(-5);
			diceLog += "플레이어의 공격력이 5만큼 감소합니다.\n";
			diceLog += "현재 공격력 : " + to_string(player->GetAttackPower()) + '\n';
			logger->PrintLog(diceLog, EDeBuff);
			break;
		case 6:
			player->TakeGold(goldTake * -1);
			diceLog += to_string(goldTake) + "gold를 잃었습니다!\n";
			logger->PrintLog(diceLog, EDeBuff);
			break;
		default:
			cout << "주사위 값 범위 이탈 에러 발생\n";  //예외처리 프로그램 종료
			exit(1);
			break;
		}
		Sleep(4000);
	}

	//구현 완료 - 채규혁
	void GameManger::BuffNumber(Character* player)
	{
		Log* logger = Log::GetInstance();
		std::random_device random;
		std::mt19937 generator(random());
		std::uniform_int_distribution<int> distribution(1, 10);
		int secretNumber = distribution(generator);
		int guess;
		int attempts = 3;
		int score = 0;
		int buffAttackPower = 5;
		int buffDuration = 5;
		string numberLog = "";
		bool isCorrect = false;

		numberLog += "숫자 맞추기 게임에 오신 것을 정말 진심으로 환영합니다!\n";
		numberLog += "1부터 10 사이의 숫자를 맞춰보세요. 기회는 3번입니다!\n";
		numberLog += "정답을 맞추실 경우 공격력을 획득합니다! 못 맞추실 경우에는...\n";
		logger->PrintLog(numberLog, EBuff);
		Sleep(3000);
		numberLog = "";

		for (int i = 1; i <= attempts; ++i) {
			while (true)
			{
				logger->PrintLog(to_string(i) + "번째 시도: ", EBuff);
				cin >> guess;
				if (guess < 1 || guess >10)
				{
					logger->PrintInputError();
					Sleep(3000);
				}
				else break;
			}
			if (guess == secretNumber) {
				numberLog += "축하합니다! 숫자를 맞췄습니다!\n";
				score = (attempts - i + 1);
				numberLog += "획득 점수: " + to_string(score) + "\n";
				numberLog += "다음 전투에서 공격력이 " + to_string(buffAttackPower) + " X " + to_string(score) + "(획득 점수) 만큼 " + to_string(buffDuration) + "턴 동안 증가합니다.";
				logger->PrintLog(numberLog, EBuff);
				BuffBase buff = BuffBase(BuffStat(buffAttackPower, 0, 0), buffDuration);
				player->TryAddBuff(buff);
				Sleep(7000);
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
		if (isCorrect == false)
		{
			numberLog = "";
			numberLog += "아쉽습니다. 기회를 모두 소진했습니다.\n";
			numberLog += "정답은 " + to_string(secretNumber) + "\n";
			numberLog += "정답을 맞추지 못해 디버프를 받습니다!\n";

			numberLog += "다음 전투에서 공격력이 " + to_string(buffAttackPower * -1) + "만큼 " + to_string(buffDuration) + "턴 동안 감소합니다.";
			logger->PrintLog(numberLog, EDeBuff);
			BuffBase buff = BuffBase(BuffStat(buffAttackPower * -1, 0, 0), buffDuration);
			player->TryAddBuff(buff);
			Sleep(7000);
		}
	}

	//미구현
	void GameManger::BuffRand(Character* player)
	{
		//TODO: 아이템 랜덤 변경
		Log* logger = Log::GetInstance();
		logger->PrintLog("아무것도 없었다.", EBuff);
		Sleep(2000);
	}

	//구현 완료 - 채규혁
	void GameManger::BuffCoinToss(Character* player)
	{
		Log* logger = Log::GetInstance();
		int solution = 1;
		int count = 0;
		int choice = 0;
		int buffArmor = 5;
		int buffDuration = 5;
		string str = "";
		string result;
		std::random_device random;
		std::mt19937 generator(random());
		std::uniform_int_distribution<int> distribution(1, 2);  //동전 앞(1), 뒷면(2)

		str += "동전 던지기 방에 도착했습니다.\n";
		str += "맞춘 횟수 X " + to_string(buffArmor) + "만큼 " + to_string(buffDuration) + "턴 동안 방어력이 증가합니다.";
		logger->PrintLog(str, EBuff);
		Sleep(3000);
		str = "";
		while (solution)
		{
			int randomNumber = distribution(generator);
			while (true)	//입력 예외 처리
			{
				logger->PrintLog("동전을 던져 나올 면을 맞춰보세요.(1 : 앞면, 2 : 뒷면)\n기회는 총 5번 입니다. 행운을 빕니다.!\n입력 : ", EBuff);
				cin >> choice;
				switch (choice)
				{
				case 1:
					str += to_string(solution) + "번 째 선택 : 앞면";
					break;
				case 2:
					str += to_string(solution) + "번 째 선택 : 뒷면";
					break;
				default:
					logger->PrintLog("", EBuff);
					logger->PrintInputError();
					Sleep(2000);
					break;
				}
				if (choice == 1 || choice == 2)
				{
					result = (randomNumber == 1 ? "앞면" : "뒷면");	//choice가 1 or 2일 경우에만 result에 해당 면 대입
					break;
				}
			}
			str += "    결과 : " + result;
			if (choice == randomNumber)
			{
				count++;
				str += "\n맞췄습니다! 맞춘 횟수 : " + to_string(count);
			}
			else
			{
				str += "\n틀렸습니다! 맞춘 횟수 : " + to_string(count);
			}
			logger->PrintLog(str, EBuff);
			Sleep(3000);
			str = "";
			if (++solution == 6)	//동전 덜질 기회는 5번, solution이 6이면 결과에 따라 버프 부여
			{
				str += to_string(count) + "(맞춘 횟수) X " + to_string(buffArmor) + "만큼 " + to_string(buffDuration) + "동안 방어력이 증가합니다.";
				logger->PrintLog(str, EBuff);
				BuffBase buff = BuffBase(BuffStat(0, buffArmor, 0), buffDuration);
				player->TryAddBuff(buff);
				break;
			}
		}
		Sleep(7000);
	}

	// 현재 스테이지 반환 함수
	int GameManger::GetCurrentStage()
	{
		return stage;
	}

	// 스테이지 단계 설정
	void GameManger::SetStage(int num)
	{
		this->stage = num;
	}

	//테스트용 BeginPlay
	void GameManger::BeginPlayDebug(Character* player)
	{
		int stage = 1;
		int battleCnt = 1; // 배틀방 연속 입장 횟수

		Log* logger = Log::GetInstance();

		player->DisplayStatus();

		/*SetStage(stage);
		BeginBattle(player, stage);
		SetStage(++stage);*/

		while (stage <= 20)
		{
			cout << "------------------------------------------------------------------" << endl;
			cout << "currentStage" << stage << endl;

			if (stage % 5 == 0) // 보스 입장
			{
				// Debug
				cout << "BOSS" << endl;
				battleCnt = 2;

				//BeginBattle(player, stage);
				//battleCnt = 0;
				SetStage(++stage);
				continue;
			}


			if (battleCnt > 1)
			{
				// 배틀방 2연속일 경우 확률 조정
				roomProbabilities[Battle] = 20.0;
				roomProbabilities[Rest] = 20.0;
				roomProbabilities[Buff] = 20.0;
				roomProbabilities[Market] = 40.0;
				battleCnt = 0;
			}
			else
			{
				// Default
				roomProbabilities[Battle] = 50.0;
				roomProbabilities[Rest] = 10.0;
				roomProbabilities[Buff] = 10.0;
				roomProbabilities[Market] = 30.0;
			}

			// roomProbabilities 출력
			for (const auto& entry : roomProbabilities) {
				std::cout << StageRoomToString(entry.first) << ": " << entry.second << std::endl;
			}

			auto stageRooms = GenerateTwoRandomRooms(roomProbabilities, std::optional<StageRooms>(StageRooms::Battle));

			// 디버그
			for (size_t i = 0; i < stageRooms.size(); ++i) {
				cout << i + 1 << ". Stage Room: " << StageRoomToString(stageRooms[i]) << endl;
			}

			SetStage(++stage);

			//vector<string> menu = {
			//	StageRoomToString(stageRooms[0]),
			//	StageRoomToString(stageRooms[1])
			//};

			//vector<function<void()>> actions;

			//for (const auto stage : stageRooms)
			//{
			//	switch (stage)
			//	{
			//	case Market:
			//		// player는 게임 도중에 바뀔 수 있는 값이라면, 그 시점에서 player가 변경된 상태를 반영하게 됩니다.
			//		actions.push_back([&]() {
			//			logger->PrintLog("이상한 건물에 들어섰다.\n");
			//			Sleep(2000);
			//			battleCnt = 0;
			//			//VisitShop(player);
			//			});
			//		break;
			//	case Rest:
			//		actions.push_back([&]() {
			//			logger->PrintLog("잠시 쉴수 있을꺼 같다.\n");
			//			Sleep(2000);
			//			battleCnt = 0;
			//			//VisitRest(player);
			//			});
			//		break;
			//	case Battle:
			//		actions.push_back([&]() {
			//			logger->PrintLog("어맛!\n");
			//			Sleep(2000);
			//			++battleCnt;
			//			//BeginBattle(player, stage);
			//			});
			//		break;
			//	case Buff:
			//		actions.push_back([&]() {
			//			logger->PrintLog("여긴 어디지...?\n");
			//			Sleep(2000);
			//			battleCnt = 0;
			//			//VisitBuffRoom(player);
			//		});
			//		break;
			//	default:
			//		break;
			//	}
			//}

			//Menu menuSystem(menu, actions);

			//// 메뉴 실행
			//while (true) {
			//	menuSystem.DisplayMenu((int)ECharacter, true, "Stage: " + to_string(stage) + "\n");
			//	menuSystem.RunMenu((int)ECharacter, true, "Stage: " + to_string(stage) + "\n");

			//	if (menuSystem.GetSelectedIndex() == 0 || menuSystem.GetSelectedIndex() == 1) {
			//		SetStage(++stage);
			//	}

			//	cout << endl; // 메뉴 간격 조정
			//}
		}
	}

	// 게임시작
	void GameManger::BeginPlay(Character* player)
	{
		int stage = 1;
		int battleCnt = 1; // 배틀방 연속 입장 횟수

		Log* logger = Log::GetInstance();

		player->DisplayStatus();

		SetStage(stage);
		BeginBattle(player, stage);
		SetStage(++stage);

		while (stage <= 20)
		{
			if (stage % 5 == 0) // 보스 입장
			{
				BeginBattle(player, stage);
				battleCnt = 0;
				SetStage(++stage);
				continue;
			}

			if (battleCnt > 1)
			{
				// 배틀방 2연속일 경우 확률 조정
				roomProbabilities[Battle] = 20.0;
				roomProbabilities[Rest] = 20.0;
				roomProbabilities[Buff] = 20.0;
				roomProbabilities[Market] = 40.0;
				battleCnt = 0;
			}
			else
			{
				// Default
				roomProbabilities[Battle] = 50.0;
				roomProbabilities[Rest] = 10.0;
				roomProbabilities[Buff] = 10.0;
				roomProbabilities[Market] = 30.0;
			}

			auto stageRooms = GenerateTwoRandomRooms(roomProbabilities, std::optional<StageRooms>(StageRooms::Battle));

			vector<string> menu = {
				StageRoomToString(stageRooms[0]),
				StageRoomToString(stageRooms[1])
			};

			vector<function<void()>> actions;

			for (const auto stage : stageRooms)
			{
				switch (stage)
				{
				case Market:
					// player는 게임 도중에 바뀔 수 있는 값이라면, 그 시점에서 player가 변경된 상태를 반영하게 됩니다.
					actions.push_back([&]() {
						logger->PrintLog("이상한 건물에 들어섰다.\n");
						Sleep(2000);
						battleCnt = 0;
						//VisitShop(player);
					});
					break;
				case Rest:
					actions.push_back([&]() {
						logger->PrintLog("잠시 쉴수 있을꺼 같다.\n");
						Sleep(2000);
						battleCnt = 0;
						//VisitRest(player);
					});
					break;
				case Battle:
					actions.push_back([&]() {
						logger->PrintLog("어맛!\n");
						Sleep(2000);
						++battleCnt;
						BeginBattle(player, stage);
					});
					break;
				case Buff:
					actions.push_back([&]() {
						logger->PrintLog("여긴 어디지...?\n");
						Sleep(2000);
						battleCnt = 0;
						//VisitBuffRoom(player);
					});
					break;
				default:
					break;
				}
			}

			Menu menuSystem(menu, actions);

			// 메뉴 실행
			while (true) {
				menuSystem.DisplayMenu((int)ECharacter, true, "Stage: " + to_string(stage) + "\n");
				menuSystem.RunMenu((int)ECharacter, true, "Stage: " + to_string(stage) + "\n");

				if (menuSystem.GetSelectedIndex() == 0 || menuSystem.GetSelectedIndex() == 1) {
					SetStage(++stage);
				}

				cout << endl; // 메뉴 간격 조정
			}
		}
	}

} // namespace GameManger