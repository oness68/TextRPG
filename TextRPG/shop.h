#pragma once
#include <vector>
#include "shopInterface.h"
#include "itemInterface.h"

using namespace std;

class shop : public ShopInterface
{
private:
	vector<ItemInterface*> generateItem;
public:
	shop() {};
	~shop() {};
	void DisplayItem()override;
	void BuyItem(ItemInterface* item, int price);
	void SellItem(ItemInterface* item, int price);
	void UseEnchancer();

};