#include "ConsumableItem.h"
#include "Character.h"
#include <iostream>

ConsumableItem::ConsumableItem()
{
}

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

HealPotion::HealPotion(string name, int price, Rarity rarity, int effectValue)
{
	this->name = name;
	this->price = price;
	this->rarityType = rarity;
	this->typeItem = ItemType::Consumable;
	this->effectValue = effectValue;
}

HealPotion::~HealPotion()
{
}

void HealPotion::Use(Character* character)
{
	character->SetCurrentHP(character->GetCurrentHP() + this->effectValue);
	if (character->GetCurrentHP() > character->GetMaxHP())
	{
		character->SetCurrentHP(character->GetMaxHP());
	}
}

AttackBoost::AttackBoost(string name, int price, Rarity rarity, int effectValue)
{
	this->name = name;
	this->price = price;
	this->rarityType = rarity;
	this->typeItem = ItemType::Consumable;
	this->effectValue = effectValue;

	// 몇턴에 대한 개념이 생기면 그때 작업
	this->duration = 2;
}

AttackBoost::~AttackBoost()
{
}

void AttackBoost::Use(Character* character)
{
	// TODO : Buff 개념 추가
	character->SetAttackPower(character->GetAttackPower() + this->effectValue);
}

Elixir::Elixir(string name, int price, Rarity rarity, int effectValue)
{
	this->name = name;
	this->price = price;
	this->rarityType = rarity;
	this->typeItem = ItemType::Consumable;
	this->effectValue = effectValue;
}

Elixir::~Elixir()
{
}

void Elixir::Use(Character* character)
{
	// 최대 체력 증가
	character->SetMaxHP(character->GetMaxHP() + this->effectValue);
	// 현재 체력 증가
	// character->SetCurrentHP(character->GetCurrentHP() + this->effectValue);
}
