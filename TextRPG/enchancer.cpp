#pragma once
#include "Enchancer.h"
#include "EquipableItem.h"
#include "EquipableItemDecorator.h"
#include "vector"
using namespace std;


Enchancer::Enchancer() : gen(rd()) {}

EquipableItem* Enchancer::EnchanceItem(EquipableItem* item)
{
	int currentEnchantLevel = item->GetEnchantLevel();
	int successChance = max(100 - (currentEnchantLevel * 10), 10);
	uniform_int_distribution<> dis(0, 99);

	if (dis(gen) < successChance)
	{
		cout << "Enchancement Succeeded! Enchant Level increased to " << (currentEnchantLevel + 1) << endl;

		EquipableItem* enchancedItem = new EquipableItemDecorator(item);
		enchancedItem->SetEnchantLevel(currentEnchantLevel + 1);
		return enchancedItem;
	}
	else
	{
		cout << "Enchancement failed! No changes made to the item." << endl;
		return item;
	}
}
vector<Item*> Enchancer::GetEnchanceableItems(map<Item*, int>& inventory)
{
	vector<Item*> equipableItems;
	for (auto& item : inventory)
	{
		if (item.first->GetType() == ItemType::Equipable)
		{
			equipableItems.push_back(item.first);
		}
	}
	return equipableItems;
}