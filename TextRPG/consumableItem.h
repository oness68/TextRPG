#pragma once
#include "itemInterface.h"
#include "Character.h"
#include <string>

using namespace std;

class ConsumableItem :public ItemInterface
{
private:
	string name;
	int price;
	int rarity;
	string itemType;
	string effectType;
	int effectValue;
public:
	ConsumableItem(string name, int price, int rarity, string effectType, int effectValue)
		:name(name), price(price), rarity(rarity), itemType("ConsumableItem"), effectType(effectType), effectValue(effectValue) {
	}


	string GetName() override
	{
		return name;
	}
	int GetPrice() override
	{
		return price;
	}
	int GetRarity() override
	{
		return rarity;
	}
	string GetItemType() override
	{
		return itemType;
	}
	string GetEffectType()
	{
		return effectType;
	}
	int GetEffectValue()
	{
		return effectValue;
	}

	void ConsumeEffect(Character& player)
	{
		//사용 효과 구현
	}


};
