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

string Log::GetLog()
{
	return this->log;
}

void Log::SetLog(string log)
{
	this->log = log;
}

//객체에서 전달된 문자열을 멤버 변수 log에 저장하고 출력(Set 자체가 필요 없을 수도 있음)
void Log::PrintLog(string orderLog)
{
	this->SetLog(orderLog);				//각 객체에서 SetLog를 직접 호출하기보단, PrintLog를 호출에서 Set과 출력이 동시에 이루어지도록 함
	cout << this->log << endl;
}

//게임 시작 메뉴 출력
void Log::PrintStartMenu()
{
	cout << "게임 메뉴" << endl;
	cout << "1. 게임시작" << endl;
	cout << "2. 게임종료" << endl;
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