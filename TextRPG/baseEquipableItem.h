#pragma once
#include "ItemInterface.h"


class BaseEquipableItem : public ItemInterface
{
private:
	string name;
	int price;
	int rarity;
	string itemType;
public:
	BaseEquipableItem(string name, int price, int rarity, string itemType)
		: name(name), price(price), rarity(rarity), itemType(itemType) {
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
	int GetSellPrice()
	{
		return price * 0.6;
	}
};