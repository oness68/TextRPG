#pragma once
#include <string>
using namespace std;

class ItemInterface
{
public:
	virtual string GetName() = 0;
	virtual int GetPrice() = 0;
	virtual int GetRarity() = 0;
	virtual string GetItemType() = 0;//소비아이템, 장비아이템
	virtual int GetSellPrice() = 0;
};