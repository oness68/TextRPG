#pragma once
#include <vector>
#include "Item.h"
#include "Character.h"

using namespace std;

class Shop
{
public:
	Shop();
	~Shop();
	void BuyItem(Character& player);
	void SellItem(Character& player);
	void UseEnchancer(Character& player);
private:
	vector<Item*> shopInven;
};