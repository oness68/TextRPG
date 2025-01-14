#pragma once
#include "ItemInterface.h"


class BaseEquipableItem : public Item
{
public:
	BaseEquipableItem() {}
	BaseEquipableItem(string name, int price, int rarity, string itemType)
	{
		this->name = name;
		this->price = price;
		this->rarity = rarity;
		this->itemType = itemType;
	}

	virtual ~BaseEquipableItem() {}

//private:
	//string name;
	//int price;
	//int rarity;
	//string itemType;
};