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
		this->itemType = ItemType::Default;
		this->rarity = rarity;
		this->price = price;
		this->depreciationRate = 0.6;
	}
	virtual ~Item() {}

	string GetName() { return this->name; }
	enum class ItemType GetType() { return this->itemType; }
	enum class Rarity GetRarity() { return this->rarity; }
	
	int GetPrice() { return this->price; }
	double GetDepreciationRate() { return this->depreciationRate; }
	int GetSellPrice() { return depreciationRate == 0 ? price : (int)(price * depreciationRate); }

protected:
	string name = "";
	enum class ItemType itemType = ItemType::Unknown;
	Rarity rarity = Rarity::C;

	int price = 0;
	double depreciationRate = 0;
};

#endif // !ITEM_H_