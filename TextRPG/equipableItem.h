#ifndef EQUIPABLE_ITEM_H_
#define EQUIPABLE_ITEM_H_

#include "Character.h"
#include <string>
#include <map>

using namespace std;

class EquipableItem : public Item
{
public:
	EquipableItem();
	EquipableItem(string name, int price, Rarity rarity, string equipType, map<string, int>baseStat, int enchantLevel);
	~EquipableItem();

	string GetEquipType();
	//enum class EquipmentType GetGetEquipType();

	map<string, int> GetBaseStat();

	int GetEnchantLevel();
	void SetEnchantLevel(const int& level);

	bool IsEquipping();
	void SetEquipping(const bool& equipping);

	void EquipEffect(Character& player);

private:
	string equipType;//무기,방어구
	map<string, int> baseStat;
	int enchantLevel;
	bool isEquipping;
};

#endif // !EQUIPABLE_ITEM_H_