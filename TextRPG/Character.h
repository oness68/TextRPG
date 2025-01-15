#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <vector>
#include <map>
//#include "Log.h"
#include "Item.h"
#include "EquipableItem.h"
#include "ExceptionHandler.h"

using namespace std;

class Inventory
{
public:
	Inventory() : item(nullptr), Count(0) {}
	Inventory(class Item* item, enum class ItemType type, int count)
	{
		this->item = item;
		this->itemType = type;
		this->Count = count;
	}

	class Item* item = nullptr;
	enum class ItemType itemType = ItemType::Unknown;
	int Count = 0;
};

class Character
{
public:
	Character(const string& name);
	~Character();

	void DisplayStatus();
	const string& GetCharacterStatusString();

	int GetCurrentHP();
	int GetMaxHP();
	const int& GetAttackPower();

	void SetCurrentHP(int hp);
	void SetMaxHP(int hp);
	void SetAttackPower(int attackPower);

	void TakeDamage(const int& damage);
	void TakeExp(const int& exp);
	void TakeGold(const int& gold);

	// ========== 인벤토리 및 아이템 상점관련 ==========
	vector<Inventory> GetInventoryItems(enum class ItemType type = ItemType::Unknown);
	map<string, class Inventory> GetInventory();

	void DisplayInventory();
	const int& GetGold();

	void TakeItem(Item* item);
	void UseItem(const string& itemKey);

	void BuyItem(class Item* item);
	void SellItem(string itemKey);

	void ReduceInventory(const string& itemKey);

	//추가 이인화--------------
	//void RemoveItem(Item* item);//추가 이인화
	//EquipableItem* GetWeaponSlot();
	//void SetWeaponSlot(EquipableItem* item);
	//EquipableItem* GetArmorSlot();
	//void SetArmorSlot(EquipableItem* item);
	//void EquipItem(EquipableItem* item);//추가 이인화

private:
	string name;
	int level = 1;
	int currentHP = 100;
	int maxHP = 100;
	int attackPower = 10;
	int gold = 5000;
	int currentExp = 0;
	int requiredLevelUpExp = 100;
	int maxLevel = 10;

	map<string, class Inventory> inventory;
	
	//map<EquipmentType, int> equipmentItems;
	//EquipableItem* weaponSlot = nullptr;
	//EquipableItem* armorSlot = nullptr;

	void LevelUp();
	void IncreaseMaxHP(const int& level);
	void IncreaseAttackPower(const int& level);
	void IncreaseRequireLevelUpExp(const int& level);
};

#endif // !CHARACTER_H_