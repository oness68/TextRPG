#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <time.h>
#include <type_traits>
#include "EnumCollection.h"

#define IMAGE_SIDE_LENGTH 32	//사용되는 이미지파일은 무조건 32X32 픽셀 사이즈만 사용
#define NUMBER_OF_COLOR 16

using namespace std;
using namespace Enums;

class Log
{
private:
	static Log* instance;
	string log;
	//모니터 해상도 가져오기
	int moniterScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int moniterScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	//모니터 해상도 가로세로의 절반만큼이 콘솔창의 크기가 되도록 함(창 크기는 모니터의 1/4
	int consoleWidth = moniterScreenWidth / 2;
	int consoleHeight = moniterScreenHeight / 2;
	//Windows 콘솔창의 기본 폰트(Raster Fonts)의 문자 크기 값(픽셀)  가로 8픽셀  세로 16픽셀
	int charWidth = 8;
	int charHeight = 16;
	//콘솔 버퍼의 크기를 문자 크기로 맞춰줌. 이러면 문자열 길이에 따라 스크롤 발생하지 않음(게임이기 때문에 화면 스크롤 발생하지 않도록)
	int bufferWidth = consoleWidth / charWidth;
	int bufferHeight = consoleHeight / charHeight;
	//콘솔 핸들 변수
	HWND console = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<string> playerData;
	vector<string> goblinData;
	vector<string> orcData;
	vector<string> trollData;
	vector<string> wolfData;
	vector<string> slimeData;
	vector<string> goblinRiderData;
	vector<string> twinHeadTrollData;
	vector<string> treantData;
	vector<string> dragonData;

private:
	Log() {};
	~Log() = default;
	Log(const Log&) = delete;
	Log& operator = (const Log&) = delete;
	int CharToIndex(char c);	//이미지 출력을 위해 알파벳을 인덱스로 전환시켜줌
public:
	static Log* GetInstance();
	const string& GetLog();
	void Initialize();			//모니터 크기의 4분의 1 크기로 콘솔 창 크기를 설정하고 모니터 가운데로 띄워줌, 각 string타입 벡터에 이미지 텍스트 초기화(32X32 PNG파일을 0~15의 색상에 따라 알파벳으로 변환 -> 콘솔 색상 변환을 위해)
	void SetLog(string log);
	template<typename T>
	void PrintLog(string orderLog, const T& object);	//각 객체로부터 출력할 string값과 무엇을 출력할지를 판별하는 Enum을 인자로 받아 화면 출력
	void PrintStartMenu(int caseNumber);	//게임 시작 메뉴 출력
	void PrintInputError();
	void PrintGameOver(int caseNumber);	//1 : 게임 종료의 경우, 2 : 플레이어 사망의 경우
	void PrintBattle(); //BattlePrint, StatusPrint, ShopRoomPrint, RestRoomPrint, BuffDebuffRoomPrint
	void PrintStatus();
	void PrintShopRoom();
	void PrintRestRoom();
	void PrintBuffDebuffRoom();
	void TestPrint();
};

#endif