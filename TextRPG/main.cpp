#include <iostream>

#include "GameManager.h"
#include "Log.h"
#include "Character.h"
#include "EnumCollection.h"

using namespace std;

<<<<<<< HEAD
void main()
=======
int main() 
>>>>>>> GameManager
{
	using GM = GameManger::GameManger;

	GM& gameManager = GM::GetInstance();

	// 배틀 매니저, 케릭터 생성
	gameManager.GenerateBattleManager();
<<<<<<< HEAD
	Log* logger = Log::GetInstance();
	Character player1 = *new Character("한정혁");
	player1.DisplayStatus();
=======
	//Character player1 = *new Character("�븳�젙�쁺");
	//player1.DisplayStatus();
>>>>>>> GameManager

	int menuOption;
	bool isGameRun = false;		//게임의 실행여부
	bool isGameStart = false;	//게임메뉴 탈출조건 위함

	// 1. 게임시작, 2. 종료
	while (!isGameStart)
	{
		logger->PrintStartMenu(Menu);
		cin >> menuOption;

		switch (menuOption) {
		case 1:
<<<<<<< HEAD
			isGameStart = true;	//시작화면 루프 벗어나기 위함
			isGameRun = true;	//게임 시작
			logger->PrintStartMenu(Start);
			break;
		case 2:
			logger->PrintGameOver(LogEnum::GameEnd);	//플레이어의 사망과 게임 재시작 여부 물어보는 출력문
			return;
=======
			gameManager.BeginPlay();
			break;
		case 2:
			cout << "寃뚯엫�쓣 醫낅즺�빀�땲�떎..." << endl;
			return 0;
>>>>>>> GameManager
			break;
		default:
			logger->PrintInputError();	//잘못된 입력 안내 출력
		}
	}

<<<<<<< HEAD
	//게임 실행 코드
	while (isGameStart)
	{
		break;
	}

	//게임 실행이 끝났을 때
	logger->PrintGameOver(LogEnum::GameEnd);
	return;
=======
	return 0;
>>>>>>> GameManager
}