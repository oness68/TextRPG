#ifndef EQUIPABLE_DECORATOR_H_
#define EQUIPABLE_DECORATOR_H_

#include "EquipableItem.h"
#include "Character.h"

class EquipableItemDecorator : public EquipableItem
{
public:
	EquipableItemDecorator(EquipableItem* item) : EquipableItem(item->GetName(), item->GetPrice(), item->GetRarity(), item->GetEquipType(), item->GetBaseStat(), item->GetEnchantLevel()), decoratedItem(item) {}

	string GetEquipType()
	{
		return decoratedItem->GetEquipType();
	}

	map<string, int> GetBaseStat()
	{
		map<string, int> enhancedStat = decoratedItem->GetBaseStat();
		for (auto& stat : enhancedStat)
		{
			stat.second += (decoratedItem->GetEnchantLevel() * 5);
		}
		return enhancedStat;
	}

	int GetEnchantLevel()
	{
		return decoratedItem->GetEnchantLevel();
	}

	void SetEnchantLevel(int level)
	{
		decoratedItem->SetEnchantLevel(level);
	}

	void EquipEffect(Character& player)
	{
		decoratedItem->EquipEffect(player);
	}

private:
	EquipableItem* decoratedItem;
};

#endif // !EQUIPABLE_DECORATOR_H_