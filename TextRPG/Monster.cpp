#include "Monster.h"

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
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, totalProbabiility);

	int randomValue = dis(gen);
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
	dropTable.push_back({ 50,"Portion" });
	dropTable.push_back({ 50,"Rare Sword" });
}

int NormalMonster::TakeAction() const
{

	return 0;
}

void BossMonster::InitializeDropTable()
{
	dropTable.push_back({ 50,"Epic Sword" });
	dropTable.push_back({ 50,"Elixir" });
}

int BossMonster::TakeAction() const 
{
	return 0;
}

void Dragon::InitializeDropTable()
{
	dropTable.push_back({ 10,"Dragon Sword" });
	dropTable.push_back({ 10,"Dragon Heart" });
	dropTable.push_back({ 40,"Dragon Bone" });
	dropTable.push_back({ 40,"Dragon Skin" });
}
