#ifndef CONSUMABLE_ITEM_H_
#define CONSUMABLE_ITEM_H_

#include "Item.h"
#include "Character.h"

using namespace std;

enum class EffectType
{
	Unknown,
	HealCurrentHP,
	IncreaseMaxHP,
	IncreaseAttackPower,
	DamageUp
};

class ConsumableItem : public Item
{
public:
	ConsumableItem();
	ConsumableItem(string name, int price, Rarity rarity, EffectType effectType, int effectValue, string desc = "소비아이템");
	ConsumableItem(string name, int price, Rarity rarity, EffectType effectType, int effectValue, int duration, string desc = "소비아이템");
	virtual ~ConsumableItem();

	EffectType GetEffectType();
	int GetEffectValue();
	int GetDuration();

	void ConsumeEffect(Character& player);

protected:
	EffectType effectType = EffectType::Unknown;
	int effectValue = 0;
	int duration = 0;
};

#endif // !CONSUMABLE_ITEM_H_
