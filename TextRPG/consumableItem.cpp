#include "ConsumableItem.h"
#include "Character.h"
#include <iostream>

ConsumableItem::ConsumableItem()
{
}

ConsumableItem::ConsumableItem(string name, int price, Rarity rarity, EffectType effectType, int effectValue)
{
	this->name = name;
	this->price = price;
	this->rarity = rarity;
	this->effectType = effectType;
	this->effectValue = effectValue;
	this->itemType = ItemType::Consumable;
}

ConsumableItem::ConsumableItem(string name, int price, Rarity rarity, EffectType effectType, int effectValue, int duration)
{
	this->name = name;
	this->price = price;
	this->rarity = rarity;
	this->effectType = effectType;
	this->effectValue = effectValue;

	this->duration = duration;
	this->itemType = ItemType::Consumable;
}

ConsumableItem::~ConsumableItem() {}

EffectType ConsumableItem::GetEffectType() { return this->effectType; }

int ConsumableItem::GetEffectValue() { return this->effectValue; }

void ConsumableItem::ConsumeEffect(Character& player)
{
	switch (effectType)
	{
	case EffectType::HealCurrentHP:
		player.SetCurrentHP(player.GetCurrentHP() + this->effectValue);
		cout << "You used a " << name << "!" << endl;
		cout << "Healing HP" << effectValue << "! Current HP : " << player.GetCurrentHP() << "/" << player.GetMaxHP() << endl;
		break;
	case EffectType::IncreaseMaxHP:
		player.AddMaxHP(effectValue);
		cout << "You used a " << name << "!" << endl;
		cout << "Max HP Up " << effectValue << "! Max HP : " << player.GetMaxHP() << endl;
		break;
	case EffectType::DamageUp:
		{
		BuffBase buffbase = BuffBase(BuffStat(this->effectValue, 0, 0), this->duration);
		player.TryAddBuff(buffbase);
		}
		cout << "You used a " << name << "!" << endl;
		cout << "Damage Up " << effectValue << "! AttackPower : " << player.GetAttackPower() << endl;
		break;
	case EffectType::Unknown:
		break;
	default:
		break;
	}
}
