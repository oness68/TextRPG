#ifndef ITEM_H_
#define ITEM_H_

enum class ItemType
{
	Unknown = 0,
	Equipable,
	Consumable,
	Archive,
	Default
};

enum class Rarity
{
	C,		// Common
	UC,		// Uncommon
	R,		// Rare
	SR,		// Super Rare
	SSR,	// Super Special Rare
	UR,		// Ultra Rare
};

enum class EquipmentType
{
	Weapone = 0,	// 무기
	// Armor,		// 방어구
	Ring,			// 반지 => 공격력만증가
	// Head,		// 머리 보호대
	// Glove,		// 장갑
	// Shoes,		// 신발
	// EarRing,		// 귀걸이
};

#include <string>
using namespace std;

class Item
{
	friend class Character;
public:
	Item() {};
	virtual ~Item() {}

	string GetName() { return this->name; }
	int GetPrice() { return this->price; }
	int GetRarity() { return this->rarity; }
	string GetItemType() { return this->name; }
	double GetDepreciationRate() { return this->depreciationRate; }

	int GetSellPrice() { return depreciationRate == 0 ? 0 : (int)(price / depreciationRate); }

protected:
	string name = "";
	int price = 0;
	int rarity = 0;
	string itemType = "";
	enum class ItemType typeItem = ItemType::Unknown;
	double depreciationRate = 0;
};

#endif // !ITEM_H_