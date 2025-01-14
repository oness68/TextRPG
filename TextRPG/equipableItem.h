#pragma once
#include "BaseEquipableItem.h"
#include "Character.h"
#include <string>
#include<map>

using namespace std;

class EquipableItem :public BaseEquipableItem
{
public:
	EquipableItem();
	EquipableItem(string name, int price, int rarity, string equipType, map<string, int>baseStat, int enchantLevel);/*
		:BaseEquipableItem(name, price, rarity, "EquipableItem"), equipType(equipType), baseStat(baseStat), enchantLevel(enchantLevel) {
	}*/

	~EquipableItem();

	string GetEquipType();

	map<string, int> GetBaseStat();

	int GetEnchantLevel();

	void SetEnchantLevel(const int& level);

	bool IsEquipping();

	void SetEquipping(const bool& equipping);

	//string GetName() override
	//{
	//	return isEquipping ? BaseEquipableItem::GetName() + " (Equipping)" : BaseEquipableItem::GetName();
	//}

	//void EquipEffect(Character& player);
	//{
		//사용 효과 구현 BaseStat을 캐릭터에게 적용
	//}

private:
	string equipType;//무기,방어구
	map<string, int> baseStat;
	int enchantLevel;
	bool isEquipping;
};