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

	Armor,			// 방어구
	// Head,		// 머리 보호대
	Glove,			// 장갑
	Shoes,			// 신발

	Ring,			// 반지 => 공격력만증가
	EarRing,		// 귀걸이
};

enum class ElixirType
{
	HPUp = 0,
	PowerUp,
	//ArmorUp,
};

#include <string>
using namespace std;

class Item
{
	friend class Character;
public:
	Item() {};
	Item(string name, int price, Rarity rarity)
	{
		this->name = name;
		this->rarity = rarity;
		this->price = price;

		this->itemType = ItemType::Default;
		this->depreciationRate = 0.6;
	}
	Item(string name, int price, Rarity rarity, double depreciationRate)
	{
		this->name = name;
		this->rarity = rarity;
		this->price = price;
		this->depreciationRate = depreciationRate;

		this->itemType = ItemType::Default;
	}

	virtual ~Item() {}

	string GetName() { return this->name; }
	ItemType GetType() { return this->itemType; }
	Rarity GetRarity() { return this->rarity; }
	
	int GetPrice() { return this->price; }
	double GetDepreciationRate() { return this->depreciationRate; }
	int GetSellPrice() { return depreciationRate == 0 ? price : (int)(price * depreciationRate); }

protected:
	string name = "";
	ItemType itemType = ItemType::Unknown;
	Rarity rarity = Rarity::C;

	int price = 0;
	double depreciationRate = 0.6;
};

#include "BuffBase.h"
class ArchiveItem : public Item
{
public:
	ArchiveItem() {};
	ArchiveItem(string name, int price, Rarity rarity, BuffStat buffStat)
	{
		this->name = name;
		this->rarity = rarity;
		this->price = price;
		this->buffStat = buffStat;

		this->itemType = ItemType::Archive;
	}

	BuffStat GetBuffStat() { return this->buffStat; }
private:
	BuffStat buffStat;
};

#endif // !ITEM_H_