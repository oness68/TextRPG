#ifndef LOG_H
#define LOG_H

#include "stb_image.h"
#include "EnumCollection.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <time.h>
#include <type_traits>

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
	//문자 크기로 콘솔 버퍼 크기 정하고 창 크기 설정해줌
	COORD bufferSize;
	//콘솔 핸들 변수
	HWND console = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//이미지 관련 변수
	int presentImage = -1;
	int palette[NUMBER_OF_COLOR][3] = //SetConsoleTextAttribute의 색상 인덱스와 매칭됨
	{
	{0, 0, 0}, {0, 0, 128}, {0, 128, 0}, {0, 128, 128},
	{128, 0, 0}, {128, 0, 128}, {128, 128, 0}, {192, 192, 192},
	{128, 128, 128}, {0, 0, 255}, {0, 255, 0}, {0, 255, 255},
	{255, 0, 0}, {255, 0, 255}, {255, 255, 0}, {255, 255, 255}
	};
	//알파벳으로 변환된 문자열을 담을 vector<string> 변수, 한줄(32)을 인덱스 멤버 하나로 32개 가짐(32x32)
	//캐릭터 이미지
	vector<string> playerData;
	//몬스터 이미지
	vector<string> goblinData;
	vector<string> orcData;
	vector<string> trollData;
	vector<string> wolfData;
	vector<string> slimeData;
	vector<string> goblinRiderData;
	vector<string> twinHeadTrollData;
	vector<string> treantData;
	vector<string> dragonData;
	//버프 이미지
	vector<string> buffData;
	vector<string> deBuffData;
	//상점 이미지
	vector<string> shopData;
	//휴식 이미지
	vector<string> restData;
	//아이템 이미지
	vector<string> bagData;

private:
	Log() {};
	~Log() = default;
	Log(const Log&) = delete;
	Log& operator = (const Log&) = delete;
	int CharToIndex(char c);	//이미지 출력을 위해 알파벳을 인덱스로 전환시켜줌
	vector<string> PNGImageToData(string filePath);
	int GetClosestColorIndex(int r, int g, int b);
	void SetCursorPosition(int x, int y);
public:
	static Log* GetInstance();
	const string& GetLog();
	void Initialize();			//모니터 크기의 4분의 1 크기로 콘솔 창 크기를 설정하고 모니터 가운데로 띄워줌, 각 string타입 벡터에 이미지 텍스트 초기화(32X32 PNG파일을 0~15의 색상에 따라 알파벳으로 변환 -> 콘솔 색상 변환을 위해)
	void SetLog(string log);
	void PrintStartMenu(int caseNumber);	//게임 시작 메뉴 출력
	void PrintInputError();
	void PrintGameOver(int caseNumber);	//1 : 게임 종료의 경우, 2 : 플레이어 사망의 경우
	void PrintImage(vector<string>& data);
	//각 객체로부터 출력할 string값과 해당 Enum 값 받음, string만 받으면 출력만
	void PrintLog(string orderLog);
	void PrintLog(string orderLog, int caseNumber);						//이미지가 있을 경우
	void PrintLog(string orderLog, int caseNumber1, int caseNumber2);	//이미지가 두 개인 경우, 미구현
	void PrintLog(string orderLog, bool clear);
	void PrintLog(string orderLog, int caseNumber, bool clear);
};

#endif