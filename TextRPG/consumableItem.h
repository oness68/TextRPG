#pragma once
#include "ItemInterface.h"
#include "Character.h"
#include <string>

using namespace std;

class ConsumableItem : public Item
{
public:
	ConsumableItem(string name, int price, int rarity, string effectType, int effectValue);
	~ConsumableItem();

	string GetEffectType();

	int GetEffectValue();

	int GetSellPrice();

	void ConsumeEffect(Character& player);

private:
//	string name;
//	int price;
//	int rarity;
//	string itemType;
	string effectType;
	int effectValue;
};
