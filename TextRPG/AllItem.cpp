#include "ConsumableItem.h"
#include "EquipableItem.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<random>

using namespace std;

//ConsumableItem
class LowHPPotion : public ConsumableItem
{
public:
	LowHPPotion() : ConsumableItem("Low HP Potion", 50, 3, "Healing HP", 20) {}
};

class MiddleHPPotion : public ConsumableItem
{
public:
	MiddleHPPotion() : ConsumableItem("Middle HP Potion", 100, 2, "Healing HP", 40) {}
};

class HighHPPotion : public ConsumableItem
{
public:
	HighHPPotion() : ConsumableItem("High HP Potion", 200, 1, "Healing HP", 100) {}
};

class LowHPElixer : public ConsumableItem
{
public:
	LowHPElixer() : ConsumableItem("Low HP Elixer", 100, 3, "Max HP Up", 10) {}
};

class MiddleHPElixer : public ConsumableItem
{
public:
	MiddleHPElixer() : ConsumableItem("Middle HP Elixer", 150, 2, "Max HP Up", 20) {}
};

class HighHPElixer : public ConsumableItem
{
public:
	HighHPElixer() : ConsumableItem("High HP Elixer", 200, 1, "Max HP Up", 50) {}
};

class DamageUPpotion : public ConsumableItem
{
public:
	DamageUPpotion() : ConsumableItem("Damage UP Potion", 150, 1, "Damage Up", 5) {}
};

//EquipableItem
class ShortSword : public EquipableItem
{
public:
	ShortSword() :EquipableItem("Short Sword", 300, 3, "Weapon", { {"Damage", 10} }, 0) {}
};

class LongSword : public EquipableItem
{
public:
	LongSword() :EquipableItem("Long Sword", 500, 2, "Weapon", { {"Damage", 20} }, 0) {}
};

class TwoHandedSword : public EquipableItem
{
public:
	TwoHandedSword() :EquipableItem("Two Handed Sword", 1000, 1, "Weapon", { {"Damage", 50} }, 0) {}
};
/*class LeatherArmor : public EquipableItem
{
public:
	LeatherArmor() :EquipableItem("Leather Armor", 300, 3, "Armor", { {"Defense", 10} }, 0) {}
};
class ChainMail : public EquipableItem
{
public:
	ChainMail() :EquipableItem("Chain Mail", 500, 2, "Armor", { {"Defense", 20} }, 0) {}
};
class MetalArmor : public EquipableItem
{
public:
	MetalArmor() :EquipableItem("Metal Armor", 1000, 1, "Armor", { {"Defense", 50} }, 0) {}
};*/


class AllItem
{
private:
	vector<Item*> items;
public:
	AllItem()
	{
		items.push_back(new LowHPPotion());
		items.push_back(new MiddleHPPotion());
		items.push_back(new HighHPPotion());
		items.push_back(new LowHPElixer());
		items.push_back(new MiddleHPElixer());
		items.push_back(new HighHPElixer());
		items.push_back(new DamageUPpotion());
		items.push_back(new ShortSword());
		items.push_back(new LongSword());
		items.push_back(new TwoHandedSword());
		/*items.push_back(new LeatherArmor());
		items.push_back(new ChainMail());
		items.push_back(new MetalArmor());*/
	}
	~AllItem() {
		for (auto item : items) delete item;
	}
	vector<Item*> GetRandomItems(int count) {
		vector<Item*> shuffledItems = items;
		random_device rd;
		mt19937 gen(rd());
		shuffle(shuffledItems.begin(), shuffledItems.end(), gen);

		vector<Item*>randomItems(shuffledItems.begin(), shuffledItems.begin() + count);
		return randomItems;
	}

};