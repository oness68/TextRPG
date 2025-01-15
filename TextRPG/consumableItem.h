#ifndef CONSUMABLE_ITEM_H_
#define CONSUMABLE_ITEM_H_

#include "Item.h"
#include "Character.h"

using namespace std;

class ConsumableItem : public Item
{
public:
	ConsumableItem();
	ConsumableItem(string name, int price, int rarity, string effectType, int effectValue);
	virtual ~ConsumableItem();

	string GetEffectType();
	int GetEffectValue();
	void ConsumeEffect(Character& player);
	//virtual void Use(Character* player);

protected:
	string effectType;
	int effectValue;
};

class HealPotion : public ConsumableItem
{
public:
	HealPotion(string name, int price, Rarity rarity, int effectValue);
	virtual ~HealPotion();

	void Use(Character* character);
private:
};

class AttackBoost : public ConsumableItem
{
public:
	AttackBoost(string name, int price, Rarity rarity, int effectValue);
	virtual ~AttackBoost();

	virtual void Use(Character* character);
private:
	int duration;
};

class Elixir : public ConsumableItem
{
public:
	Elixir(string name, int price, enum Rarity rarity, int effectValue);
	virtual ~Elixir();

	void Use(Character* character);
private:
};


#endif // !CONSUMABLE_ITEM_H_
