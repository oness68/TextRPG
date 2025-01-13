#include "Log.h"

Log* Log::instance = nullptr;

Log* Log::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Log();
	}
	return instance;
}

void Log::SetScreen()
{
	int moniterScreenWidth = GetSystemMetrics(SM_CXSCREEN);		//모니터 해상도 가져오기
	int moniterScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int consoleWidth = moniterScreenWidth / 2;					//모니터 해상도 가로세로의 절반만큼이 콘솔창의 크기가 되도록 함(창 크기는 모니터의 1/4
	int consoleHeight = moniterScreenHeight / 2;
	int charWidth = 8;											//Windows 콘솔창의 기본 폰트(Raster Fonts)의 문자 크기 값(픽셀)  가로 8픽셀  세로 16픽셀
	int charHeight = 16;
	int bufferWidth = consoleWidth / charWidth;					//콘솔 버퍼의 크기를 문자 크기로 맞춰줌. 이러면 문자열 길이에 따라 스크롤 발생하지 않음(게임이기 때문에)
	int bufferHeight = consoleHeight / charHeight;

	//콘솔 핸들 가져옴
	HWND console = GetConsoleWindow();	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//문자 크기로 콘솔 버퍼 크기 정하고 창 크기 설정해줌
	COORD bufferSize;
	bufferSize.X = bufferWidth;
	bufferSize.Y = bufferHeight;
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);
	SMALL_RECT windowSize = { 0, 0, bufferWidth - 1, bufferHeight - 1 };	//내부의 크기 조절
	SetConsoleWindowInfo(consoleHandle, true, &windowSize);

	MoveWindow(console, moniterScreenWidth / 4, moniterScreenHeight / 4, consoleWidth, consoleHeight, true);	//화면 가운데로 띄우고, 크기 조절
}

string Log::GetLog()
{
	return this->log;
}

void Log::SetLog(string log)
{
	this->log = log;
}

//객체에서 전달된 문자열을 멤버 변수 log에 저장하고 출력(Set 자체가 필요 없을 수도 있음)
void Log::PrintLog(string orderLog, int enumCase)
{
	this->SetLog(orderLog);				//각 객체에서 SetLog를 직접 호출하기보단, PrintLog를 호출에서 Set과 출력이 동시에 이루어지도록 함

	switch (enumCase) //BattlePrint, StatusPrint, ShopRoomPrint, RestRoomPrint, BuffDebuffRoomPrint
	{
	case PrintEnum::BattlePrint:
		break;
	case PrintEnum::StatusPrint:
		this->PrintStatus();
		break;
	case PrintEnum::ShopRoomPrint:
		break;
	case PrintEnum::RestRoomPrint:
		break;
	case PrintEnum::BuffDebuffRoomPrint:
		break;
	default:
		break;
	}
	cout << this->log << endl;
}

//게임 시작 메뉴 출력
void Log::PrintStartMenu(int caseNumber)
{
	switch (caseNumber)
	{
	case LogEnum::Menu:
		cout << "게임 메뉴" << endl;
		cout << "1. 게임시작" << endl;
		cout << "2. 게임종료" << endl;
		break;
	case LogEnum::Start:
		cout << "게임이 시작됩니다." << endl;
	}
}

void Log::PrintInputError()
{
	cout << "잘못된 입력입니다. 다시 입력해 주세요." << endl;
}

void Log::PrintGameOver(int caseNumber)	//플레이어의 사망 경우와 게임의 종료에 대한 로그 출력
{
	switch (caseNumber)
	{
	case LogEnum::GameOver:
		cout << "사망하였습니다." << endl;
		cout << "새로운 게임을 시작하시겠습니까?" << endl;
		break;
	case LogEnum::GameEnd:
		cout << "게임을 종료합니다..." << endl;
		break;
	default:
		break;
	}
}

void Log::PrintBattle()
{

}

void Log::PrintStatus()
{

}