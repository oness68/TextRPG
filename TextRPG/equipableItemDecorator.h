#pragma once
#include "equipableItem.h"
#include "Character.h"

class EquipableItemDecorator : public EquipableItem
{
private:
	EquipableItem* decoratedItem;
public:
	EquipableItemDecorator(EquipableItem* item) : decoratedItem(item) {}


	string GetName() override
	{
		return decoratedItem->GetName();
	}
	int GetPrice() override
	{
		return decoratedItem->GetPrice();
	}
	int GetRarity() override
	{
		return decoratedItem->GetRarity();
	}
	string GetItemType() override
	{
		return decoratedItem->GetItemType();
	}
	string GetEquipType() {
		return decoratedItem->GetEquipType();
	}

	map<string, int> GetBaseStat() {
		return decoratedItem->GetBaseStat();
	}

	int GetEnchantLevel() {
		return decoratedItem->GetEnchantLevel();
	}

	void EquipEffect(Character& player) {
		decoratedItem->EquipEffect(player);
	}
};