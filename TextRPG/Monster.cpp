#include "Monster.h"

static int GetRandomNumber(int n)
{
	//0 ~ n 범위의 난수 반환
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, n);
	int randomNumber = dist(gen);
	return randomNumber;
}

string BaseMonster::GetRandomItem() const
{
	if (dropTable.empty())
	{
		return "";
	}

	int totalProbabiility = 0;

	for (const auto& item : dropTable)
	{
		totalProbabiility += item.first;
	}

	int randomValue = GetRandomNumber(totalProbabiility);
	int cumulativeProbability = 0;

	for (const auto& item : dropTable)
	{
		cumulativeProbability += item.first;
		if (randomValue <= cumulativeProbability)
		{
			return item.second;
		}
	}
	return "";
}

string BaseMonster::GetName()
{
	return this->name;
}

int BaseMonster::GetHealth() const
{
	return this->HP;
}

void BaseMonster::SetHealth(int health)
{
	this->HP = health;
}

int BaseMonster::GetDamage() const
{
	return this->attackPower;
}

void BaseMonster::SetDamage(int damage)
{
	this->attackPower = damage;
}

int BaseMonster::GetExperience() const
{
	return this->experience;
}

void BaseMonster::SetExperience(int experience)
{
	this->experience = experience;
}

int BaseMonster::GetGold() const
{
	return this->gold;
}

void BaseMonster::SetGold(int gold)
{
	this->gold = gold;
}

void BaseMonster::TakeDamage(int damage)
{
	this->HP -= damage;
	if (this->HP <= 0) {
		this->HP = 0;
	}
}

void NormalMonster::InitializeDropTable()
{
	dropTable.push_back({ 70,"LowHPPotion" });
	dropTable.push_back({ 20,"MiddleHPPotion" });
	dropTable.push_back({ 10,"모험가의장검" });
}

void BossMonster::InitializeDropTable()
{

	dropTable.push_back({ 50,"LowHPPotion Sword" });
	dropTable.push_back({ 50,"MiddleHPPotion" });
}

void Dragon::InitializeDropTable()
{
	dropTable.push_back({ 10,"LowHPPotion" });
	dropTable.push_back({ 10,"MiddleHPPotion" });
	dropTable.push_back({ 40,"HightHPPotion" });
	dropTable.push_back({ 40,"HightHPPotion" });
}

int NormalMonster::TakeAction() const
{
	// 1 -> 공격
	// 2 -> 방어
	Log* log = Log::GetInstance();
	int option = GetRandomNumber(2);
	string temp;

	if (option == 1)
	{
		//공격 문구 출력
		temp = this->name;
		temp += "이(가) 공격해 옵니다.\n";
		log->PrintLog(temp, false);

		return 1;
	}
	else if (option == 2)
	{
		//방어 문구 출력
		temp = this->name;
		temp += "이(가) 공격을 막아내려 합니다.\n";
		log->PrintLog(temp, false);

		return 2;
	}
	return 0;
}

int NormalMonster::GetResponseScore(int option) const
{
	return 0;
}

int BossMonster::TakeAction() const
{
	// 1 -> 공격
	// 2 -> 방어
	// 3 -> 특수 패턴
	Log* log = Log::GetInstance();
	int option = GetRandomNumber(3);
	string temp;

	if (option == 1)
	{
		//공격 문구 출력
		temp = this->name;
		temp += "이(가) 공격해 옵니다.\n";
		log->PrintLog(temp,false);
		return 1;
	}
	else if (option == 2)
	{
		//방어 문구 출력
		temp = this->name;
		temp += "이(가) 공격을 막아내려 합니다.\n";
		log->PrintLog(temp, false);

		return 2;
	}
	else if (option == 3)
	{
		//특수 패턴 선택지 출력
		for (string s : characterResponseList) {
			temp += s;
		}
		log->PrintLog(temp, false);

		return 3;
	}
}

int BossMonster::GetResponseScore(int option) const
{
	//플레이어의 선택지 입력 값을 받아 그에 따른 점수 반환
	return responseResultJudgment.at(option - 1);
}