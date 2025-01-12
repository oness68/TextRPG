#include <iostream>

#include "GameManager.h"
#include "Character.h"

using namespace std;

int main() 
{
	using GM = GameManger::GameManger;

	GM& gameManager = GM::GetInstance();

	// 배틀 매니저, 케릭터 생성
	gameManager.GenerateBattleManager();
	//Character player1 = *new Character("한정혁");
	//player1.DisplayStatus();

	int menuOption;

	// 1. 게임시작, 2. 종료
	while (true) 
	{
		cout << "게임 메뉴" << endl;
		cout << "1. 게임시작" << endl;
		cout << "2. 게임종료" << endl;
		cin >> menuOption;

		switch (menuOption) {
		case 1:
			gameManager.BeginPlay();
			break;
		case 2:
			cout << "게임을 종료합니다..." << endl;
			return 0;
			break;
		default:
			cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
		}
	}

	return 0;
}