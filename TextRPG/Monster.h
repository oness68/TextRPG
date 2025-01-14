#pragma once
#include <string>
#include <map>
#include <vector>
#include <random>
using namespace std;

class Monster
{
public:
	virtual string GetName() = 0;
	virtual int GetHealth() const = 0;
	virtual void SetHealth(int health) = 0;
	virtual int GetDamage() const = 0;
	virtual void SetDamage(int damage) = 0;
	virtual int GetExperience() const = 0;
	virtual void SetExperience(int experience) = 0;
	virtual int GetGold() const = 0;
	virtual void SetGold(int gold) = 0;
	virtual void TakeDamage(int damage) = 0;
	virtual int TakeAction() const = 0;
};

class BaseMonster : public Monster
{
protected:
	string name;
	int HP;
	int attackPower;
	int experience;
	int gold;
	vector<pair<int, string>> dropTable;

	virtual void InitializeDropTable() = 0;
	string GetRandomItem() const;

public:
	BaseMonster(string n, int hp, int atk, int exp, int g) :
		name(n), HP(hp), attackPower(atk), experience(exp), gold(g) {
	}
	string GetName() override;
	int GetHealth() const override;
	void SetHealth(int health) override;
	int GetDamage() const override;
	void SetDamage(int damage) override;
	int GetExperience() const override;
	void SetExperience(int experience) override;
	int GetGold() const override;
	void SetGold(int gold) override;
	void TakeDamage(int damage) override;
};

class NormalMonster : public BaseMonster
{
protected:
	void InitializeDropTable() override;

public:
	NormalMonster(string n, int hp, int atk, int exp, int g)
		: BaseMonster(n, hp, atk, exp, g) {
	}
	int TakeAction() const override;
};

class Goblin : public NormalMonster
{
public:
	Goblin() : NormalMonster("Goblin", 100, 15, 20, 25) {};
};

class Orc : public NormalMonster
{
public:
	Orc() : NormalMonster("Orc", 100, 15, 20, 25) {};
};

class Troll : public NormalMonster
{
public:
	Troll() : NormalMonster("Troll", 100, 15, 20, 25) {};
};

class Wolf : public NormalMonster
{
public:
	Wolf() : NormalMonster("Wolf", 100, 15, 20, 25) {};
};

class Slime : public NormalMonster
{
public:
	Slime() : NormalMonster("Slime", 100, 15, 20, 25) {};
};

class BossMonster : public BaseMonster
{
protected:
	vector<string> characterResponseList;
	map<string, int> responseResultJudgment;

	void InitializeDropTable() override;

public:
	BossMonster(string n, int hp, int atk, int exp, int g) :
		BaseMonster(n, hp, atk, exp, g) {
	}
	int TakeAction() const override;
};

class GoblinRider : public BossMonster
{
public:
	GoblinRider() : BossMonster("GoblinRider", 500, 30, 50, 100) {}
};

class TwinHeadTroll : public BossMonster
{
public:
	TwinHeadTroll() : BossMonster("TwinHeadTroll", 500, 30, 50, 100) {}
};

class Treant : public BossMonster
{
public:
	Treant() : BossMonster("Treant", 500, 30, 50, 100) {}
};

class Dragon : public BossMonster
{
protected:
	void InitializeDropTable() override;

public:
	Dragon() : BossMonster("Dragon", 1000, 50, 777, 777) {}

};