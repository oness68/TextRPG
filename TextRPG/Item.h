#pragma once
#include <string>
using namespace std;

class Item
{
public:
	virtual ~Item() {}

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

	double GetDepreciationRate()
	{
		return this->depreciationRate;
	}

protected:
	string name = "";
	int price = 0;
	int rarity = 0;
	string itemType = "";
	double depreciationRate = 0;
};