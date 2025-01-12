#ifndef LOG_H
#define LOG_H

#include <iostream>
//#include <Windows.h>		���� ��밡�ɼ�
#include <string>
#include <vector>
#include "EnumCollection.h"

using namespace std;
using namespace Enums;

class Log
{
private:
	static Log* instance;
	string log;
public:

private:
	Log() {};
	~Log() = default;
	Log(const Log&) = delete;
	Log& operator = (const Log&) = delete;
public:
	static Log* GetInstance();
	string GetLog();
	void SetLog(string log);
	void PrintLog(string orderLog);
	void PrintStartMenu();	//���� ���� �޴� ���
	void PrintInputError();
	void PrintGameOver(int caseNumber);	//1 : ���� ������ ���, 2 : �÷��̾� ����� ���
};

#endif