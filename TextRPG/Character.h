#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <vector>
#include <map>
#include "Log.h"

using namespace std;

enum EquipmentType
{
	Weapone = 0,
	Armor,
};

class Character
{
public:
	//Character();
	Character(const string& name);
	~Character();

	void DisplayStatus();
	string GetCharacterStatusString();

	const int& GetAcctackPower();
	const int& GetGold();
	map<EquipmentType, int> GetEquipmentItems();
	map<string, int> GetInventory();

	void UseItem(const string& itemKey);

	void TakeExp(const int& exp);
	void TakeGold(const int& gold);

	void TakeItem(const string& itemKey);
	void TakeItem(const int& equipmentKey);

	void TakeDamage(const int& damage);

private:
	string name;
	int level = 1;
	int currentHP = 100;
	int maxHP = 100;
	int attackPower = 10;
	int gold = 0;
	int currentExp = 0;
	int requiredLevelUpExp = 100;

	map<EquipmentType, int> equipmentItems;
	map<string, int> inventory;

	void LevelUp();
	void IncreaseMaxHP(const int& level);
	void IncreaseAttackPower(const int& level);
	void IncreaseRequireLevelUpExp(const int& level);
};

#endif // !CHARACTER_H_