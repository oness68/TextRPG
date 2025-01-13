#pragma once

class ShopInterface
{
public:
	virtual void DisplayItem() = 0;
	virtual void BuyItem() = 0;
	virtual void SellItem() = 0;
	virtual void UseEnchancer() = 0;
};