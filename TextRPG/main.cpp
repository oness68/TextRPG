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

	// ¹èÆ² ¸Å´ÏÀú, ÄÉ¸¯ÅÍ »ı¼º
	gameManager.GenerateBattleManager();
<<<<<<< HEAD
	Log* logger = Log::GetInstance();
	Character player1 = *new Character("ÇÑÁ¤Çõ");
	player1.DisplayStatus();
=======
	//Character player1 = *new Character("í•œì •í˜");
	//player1.DisplayStatus();
>>>>>>> GameManager

	int menuOption;
	bool isGameRun = false;		//°ÔÀÓÀÇ ½ÇÇà¿©ºÎ
	bool isGameStart = false;	//°ÔÀÓ¸Ş´º Å»ÃâÁ¶°Ç À§ÇÔ

	// 1. °ÔÀÓ½ÃÀÛ, 2. Á¾·á
	while (!isGameStart)
	{
		logger->PrintStartMenu(Menu);
		cin >> menuOption;

		switch (menuOption) {
		case 1:
<<<<<<< HEAD
			isGameStart = true;	//½ÃÀÛÈ­¸é ·çÇÁ ¹ş¾î³ª±â À§ÇÔ
			isGameRun = true;	//°ÔÀÓ ½ÃÀÛ
			logger->PrintStartMenu(Start);
			break;
		case 2:
			logger->PrintGameOver(LogEnum::GameEnd);	//ÇÃ·¹ÀÌ¾îÀÇ »ç¸Á°ú °ÔÀÓ Àç½ÃÀÛ ¿©ºÎ ¹°¾îº¸´Â Ãâ·Â¹®
			return;
=======
			gameManager.BeginPlay();
			break;
		case 2:
			cout << "ê²Œì„ì„ ì¢…ë£Œí•©ë‹ˆë‹¤..." << endl;
			return 0;
>>>>>>> GameManager
			break;
		default:
			logger->PrintInputError();	//Àß¸øµÈ ÀÔ·Â ¾È³» Ãâ·Â
		}
	}

<<<<<<< HEAD
	//°ÔÀÓ ½ÇÇà ÄÚµå
	while (isGameStart)
	{
		break;
	}

	//°ÔÀÓ ½ÇÇàÀÌ ³¡³µÀ» ¶§
	logger->PrintGameOver(LogEnum::GameEnd);
	return;
=======
	return 0;
>>>>>>> GameManager
}