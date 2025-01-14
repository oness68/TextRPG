#pragma once
#include "baseEquipableItem.h"
#include "Character.h"
#include <string>
#include<map>

using namespace std;

class EquipableItem :public BaseEquipableItem
{
private:
	string equipType;//무기,방어구
	map<string, int> baseStat;
	int enchantLevel;
public:
	EquipableItem(string name, int price, int rarity, string equipType, map<string, int>baseStat, int enchantLevel)
		:BaseEquipableItem(name, price, rarity, "EquipableItem"), equipType(equipType), baseStat(baseStat), enchantLevel(enchantLevel) {
	}

	string GetEquipType()
	{
		return equipType;
	}
	map<string, int> GetBaseStat()
	{
		return baseStat;
	}
	int GetEnchantLevel()
	{
		return enchantLevel;
	}

	void EquipEffect(Character& player);
	


};