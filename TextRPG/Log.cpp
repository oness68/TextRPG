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

//��ü���� ���޵� ���ڿ��� ��� ���� log�� �����ϰ� ���(Set ��ü�� �ʿ� ���� ���� ����)
void Log::PrintLog(string orderLog)
{
	this->SetLog(orderLog);				//�� ��ü���� SetLog�� ���� ȣ���ϱ⺸��, PrintLog�� ȣ�⿡�� Set�� ����� ���ÿ� �̷�������� ��
	cout << this->log << endl;
}

//���� ���� �޴� ���
void Log::PrintStartMenu()
{
	cout << "���� �޴�" << endl;
	cout << "1. ���ӽ���" << endl;
	cout << "2. ��������" << endl;
}

void Log::PrintInputError()
{
	cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << endl;
}

void Log::PrintGameOver(int caseNumber)	//�÷��̾��� ��� ���� ������ ���ῡ ���� �α� ���
{
	switch (caseNumber)
	{
	case LogEnum::GameOver:
		cout << "����Ͽ����ϴ�." << endl;
		cout << "���ο� ������ �����Ͻðڽ��ϱ�?" << endl;
		break;
	case LogEnum::GameEnd:
		cout << "������ �����մϴ�..." << endl;
		break;
	default:
		break;
	}
}