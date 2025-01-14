#include "ConsumableItem.h"
#include "Character.h"
#include <iostream>

ConsumableItem::ConsumableItem(string name, int price, int rarity, string effectType, int effectValue)
{
	this->name = name;
	this->price = price;
	this->rarity = rarity;
	this->effectType = effectType;
	this->effectValue = effectValue;
}

ConsumableItem::~ConsumableItem() {}

string ConsumableItem::GetEffectType() { return this->effectType; }

int ConsumableItem::GetEffectValue() { return this->effectValue; }

void ConsumableItem::ConsumeEffect(Character& player)
{
	if (effectType == "Healing HP")
	{
		int newHP = player.GetCurrentHP() + effectValue;
		player.SetCurrentHP(min(newHP, player.GetMaxHP()));
		cout << "You used a " << name << "!" << endl;
		cout << "Healing HP" << effectValue << "! Current HP : " << player.GetCurrentHP() << "/" << player.GetMaxHP() << endl;
	}
	else if (effectType == "Max HP Up")
	{
		player.SetMaxHP(player.GetMaxHP() + effectValue);
		cout << "You used a " << name << "!" << endl;
		cout << "Max HP Up " << effectValue << "! Max HP : " << player.GetMaxHP() << endl;
	}
	else if (effectType == "Damage Up")
	{
		player.SetAttackPower(player.GetAttackPower() + effectValue);
		cout << "You used a " << name << "!" << endl;
		cout << "Damage Up " << effectValue << "! AttackPower : " << player.GetAttackPower() << endl;
	}
}