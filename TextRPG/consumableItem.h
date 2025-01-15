#ifndef CONSUMABLE_ITEM_H_
#define CONSUMABLE_ITEM_H_

#include "Item.h"
#include "Character.h"

using namespace std;

class ConsumableItem : public Item
{
public:
	ConsumableItem(string name, int price, int rarity, string effectType, int effectValue);
	~ConsumableItem();

	string GetEffectType();
	int GetEffectValue();
	void ConsumeEffect(Character& player);
	//virtual void Use(Character* player);

private:
	string effectType;
	int effectValue;
};

#endif // !CONSUMABLE_ITEM_H_
