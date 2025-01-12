#include <iostream>
#include "GameManager.h"
#include "EnumCollection.h"
#include "Log.h"

using namespace std;

void main()
{
	using GM = GameManger::GameManger;

	GM& gameManager = GM::GetInstance();

	// ��Ʋ �Ŵ���, �ɸ��� ����, �α� �̱��� �ν��Ͻ� ����
	gameManager.GenerateBattleManager();
	Character player1 = gameManager.GenerateCharacter();
	Log* logger = Log::GetInstance();

	bool isGameRun = false;		//������ ���࿩��
	bool isGameStart = false;	//���Ӹ޴� Ż������ ����
	int menuOption;

	// 1. ���ӽ���, 2. ����
	while (!isGameStart)
	{
		logger->PrintStartMenu();
		cin >> menuOption;

		switch (menuOption) {
		case 1:
			isGameStart = true;	//����ȭ�� ���� ����� ����
			isGameRun = true;	//���� ����
			break;
		case 2:
			logger->PrintGameOver(LogEnum::GameEnd);	//�÷��̾��� ����� ���� ����� ���� ����� ��¹�
			return;
			break;
		default:
			logger->PrintInputError();	//�߸��� �Է� �ȳ� ���
		}
	}

	//���� ���� �ڵ�
	while (isGameStart)
	{
		break;
	}

	//���� ������ ������ ��
	logger->PrintGameOver(LogEnum::GameEnd);
	return;
}