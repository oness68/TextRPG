#pragma once
#include <string>
using namespace std;

class ItemInterface
{
public:
	virtual ~ItemInterface() {}

	string GetName()
	{
		return this->name;
	}

	int GetPrice()
	{
		return this->price;
	}

	int GetRarity()
	{
		return this->rarity;
	}

	string GetItemType() //소비아이템, 장비아이템
	{
		return this->name;
	}

	int GetSellPrice()
	{
		return this->sellPrice;
	}

protected:
	string name = "";
	int price = 0;
	int rarity = 0;
	string itemType = "";
	int sellPrice = 0;
};