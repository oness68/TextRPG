#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <vector>
#include <map>

#include "BuffBase.h"
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
	void DisplayStatus(string reason, int hp, int power, int level = 0, int exp = 0);
	const string GetCharacterStatusString();

	const int& GetCurrentHP();
	const int& GetMaxHP();
	const int& GetAttackPower();
	const int& GetRequiredLevelUpExp();

	void SetCurrentHP(int hp);
	void SetMaxHP(int hp);
	void AddMaxHP(int amount);

	void SetAttackPower(int attackPower);
	void AddAttackPower(int amount);

	void TakeDamage(const int& damage);
	void TakeExp(const int& exp);
	void TakeGold(const int& gold);
	int GetCurrnetExp() { return currentExp; }
	// ========== 인벤토리 및 아이템 상점관련 ==========
	vector<Inventory> GetInventoryItems(enum class ItemType type = ItemType::Unknown);
	map<string, class Inventory> GetInventory();

	// TODO : UI 로 이동 필요 (Game Manager)
	void DisplayInventory();
	void DisplayEquipMentItem();
	void DisplayConsumableItem();
	void DisplayArchiveItem();
	void DisplayEtcItem();

	const int& GetGold();

	void TakeItem(Item* item);
	void UseItem(const string& itemKey);

	void BuyItem(class Item* item);
	void SellItem(string itemKey);
	void ReduceInventory(const string& itemKey);

	void TurnEnd();
	void TryAddBuff(BuffBase& buffBase);
	void TryRemoveBuff();

	string GetName() { return name; }

	void TryAddArchiveItem(Item* item);
	void TryRemoveArchiveItem(Inventory inventory);

private:
	string name;
	int level = 1;
	int currentHP = 100;
	int maxHP = 100;
	int attackPower = 30;
	int armor = 0;
	int gold = 5000;
	int currentExp = 0;
	int requiredLevelUpExp = 100;
	int maxLevel = 10;

	map<string, class Inventory> inventory;

	map<enum class EquipmentType, class EquipableItem*> equipItemContainer;
	BuffStat equipmentBuffStat;				// 장비 아이템 추가 Stats
	BuffStat archiveBuffStat;				// 도감 아이템 추가 Stat
	vector<class BuffBase> buffContainer;	// 턴이 있는 Buff 아이템 추가 Stat
	BuffStat buffStat;

	void InitEquipMentItem();
	void EquipItem(EquipableItem* equipableItem);
	void Equip(EquipableItem* equipableItem);

	void LevelUp();

	void IncreaseMaxHP();
	void IncreaseAttackPower();
	void IncreaseRequireLevelUpExp();
	int increaseMaxHPAmount = level * 20;
	int increaseAPAmount = level * 5;
	int increaseExpAmount = level * 10;
};

#endif // !CHARACTER_H_