#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <vector>
#include <map>
//#include "Log.h"
#include "ItemInterface.h"//추가 이인화
#include "EquipableItem.h"//추가 이인화

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

	const int& GetAttackPower();//변경 이인화
	void SetAttackPower(int attackPower);

	const int& GetGold();
	//map<EquipmentType, int> GetEquipmentItems();//변경 이인화
	map<ItemInterface*, int> GetInventory();//변경 이인화

	void UseItem(ItemInterface* item);//변경 이인화
	void RemoveItem(ItemInterface* item);//추가 이인화

	void TakeExp(const int& exp);
	void TakeGold(const int& gold);

	void TakeItem(ItemInterface* item);//변경 이인화
	//void TakeItem(const int& equipmentKey);

	void TakeDamage(const int& damage);

	int GetCurrentHP();
	/*{
		return currentHP;
	};*/

	int GetMaxHP();
	//{
	//	return maxHP;
	//};

	void SetCurrentHP(int HP);
	//{
	//	currentHP = max(0, HP);
	//}

	void SetMaxHP(int HP);
	//{
	//	maxHP = max(0, HP);
	//}

	//EquipableItem* GetWeaponSlot() //추가 이인화----------
	//{
	//	return weaponSlot;
	//}

	//void SetWeaponSlot(EquipableItem* item)
	//{
	//	weaponSlot = item;
	//}

	//EquipableItem* GetArmorSlot()
	//{
	//	return armorSlot;
	//}

	//void SetArmorSlot(EquipableItem* item)
	//{
	//	armorSlot = item;
	//}

	//~추가 이인화-----------------------------------
	//void EquipItem(EquipableItem* item);//추가 이인화

private:
	string name;
	int level = 1;
	int currentHP = 100;
	int maxHP = 100;
	int attackPower = 10;
	int gold = 0;
	int currentExp = 0;
	int requiredLevelUpExp = 100;

	//map<EquipmentType, int> equipmentItems;
	map<ItemInterface*, int> inventory;//변경 이인화
	//EquipableItem* weaponSlot = nullptr;
	//EquipableItem* armorSlot = nullptr;

	void LevelUp();
	void IncreaseMaxHP(const int& level);
	void IncreaseAttackPower(const int& level);
	void IncreaseRequireLevelUpExp(const int& level);
};

#endif // !CHARACTER_H_