#pragma once

class ShopInterface
{
public:
	virtual void BuyItem(Character& player) = 0;
	virtual void SellItem(Character& player) = 0;
	virtual void UseEnchancer(Character& player) = 0;
};