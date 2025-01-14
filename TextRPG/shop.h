#pragma once
#include <vector>
#include "ShopInterface.h"
#include "ItemInterface.h"

using namespace std;

class Shop : public ShopInterface
{
private:
	vector<ItemInterface*> shopInven;
public:
	Shop() {};
	~Shop() {};
	void BuyItem(Character& player) {};
	void SellItem(Character& player) {};
	void UseEnchancer(Character& player) {};

};