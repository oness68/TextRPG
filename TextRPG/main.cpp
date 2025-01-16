#include <iostream>
#include <string>

#include <windows.h>
#include <thread>
#include <format>

#include "GameManager.h"
#include "Log.h"
#include "Character.h"
#include "EnumCollection.h"
#include "shop.h"
#include "ProcessInput.h"
#include "HotKeyHandler.h"

using namespace std;

int main() 
{
	//SetConsoleOutputCP(CP_UTF8); // CMD 기본 인코딩 설정
	std::thread inputThread(PI::ProcessInput);
	PI::isInputEnabled = false;

	try {
		using GM = GameManger::GameManger;
		GM& gameManager = GM::GetInstance();

		Log* logger = Log::GetInstance();
		logger->Initialize();

		// Debug
		//Character player1 = *new Character("정의된 용사");
		//Shop shop;
		//gameManager.VisitShop(&player1);

		int menuOption;
		bool isGameRun = false;		//게임의 실행여부
		bool isGameStart = false;	//게임메뉴 탈출조건 위함
		string characterName;

		bool namingFlag = false;

		while (true) {
			if (namingFlag)
			{
				logger->PrintLog("말도 안되는 이름입니다....\n당신은 누구입니까?\n");
			}
			else
			{
				logger->PrintLog("... 당신은 누구입니까?\n");
			}

			PI::ClearInputBuffer();
			PI::isInputEnabled = true;
			getline(cin, characterName);
			PI::isInputEnabled = false;

			if (characterName.length() > 0 && characterName.length() <= 10) {
				logger->PrintLog("너의 이름은? " + characterName + "\n");
				break;
			}
			else
			{
				namingFlag = true;
			}

			// system("pause"); TODO: 좀더 이쁘게 하기위해 사용
		}

		Character player1 = *new Character(characterName);
		std::thread hotkeyThread(HotkeyHandler, std::ref(player1));

		// 1. 게임시작, 2. 종료
		while (!isGameStart)
		{
			logger->PrintStartMenu(EMenu);
			PI::ClearInputBuffer();
			PI::isInputEnabled = true;
			cin >> menuOption;
			PI::isInputEnabled = false;
			switch (menuOption) {
			case 1:
				isGameStart = true;	//시작화면 루프 벗어나기 위함
				isGameRun = true;	//게임 시작
				logger->PrintStartMenu(EStart);
				gameManager.BeginPlay(&player1);
				break;
			case 2:
				logger->PrintGameOver(EGameEnd);	//플레이어의 사망과 게임 재시작 여부 물어보는 출력문
				return 0;
				break;
			default:
				logger->PrintInputError();	//잘못된 입력 안내 출력
			}
		}

		//게임 실행이 끝났을 때
		logger->PrintGameOver(EGameEnd);

		PI::isRunning = false;
		inputThread.join();
		hotkeyThread.join();
	}
	catch (...) {
		// 비정상 종료시 쓰레드 종료
		PI::isRunning = false;
		inputThread.join();
	}

	

	return 0;
}