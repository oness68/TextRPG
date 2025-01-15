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
		player.SetAttackPower(player.GetAttackPower() + effectValue);
		cout << "You used a " << name << "!" << endl;
		cout << "Damage Up " << effectValue << "! AttackPower : " << player.GetAttackPower() << endl;
		break;
	case EffectType::Unknown:
		break;
	default:
		break;
	}
}

AttackBoost::AttackBoost(string name, int price, Rarity rarity, int effectValue)
{
	this->name = name;
	this->price = price;
	this->rarity = rarity;
	this->itemType = ItemType::Consumable;
	this->effectValue = effectValue;
	this->effectType = EffectType::DamageUp;

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

//HealPotion::HealPotion(string name, int price, Rarity rarity, int effectValue)
//{
//	this->name = name;
//	this->price = price;
//	this->rarity = rarity;
//	this->itemType = ItemType::Consumable;
//	this->effectValue = effectValue;
//}
//
//HealPotion::~HealPotion()
//{
//}
//
//void HealPotion::Use(Character* character)
//{
//	character->SetCurrentHP(character->GetCurrentHP() + this->effectValue);
//	if (character->GetCurrentHP() > character->GetMaxHP())
//	{
//		character->SetCurrentHP(character->GetMaxHP());
//	}
//}
//
//Elixir::Elixir(string name, int price, Rarity rarity, int effectValue)
//{
//	this->name = name;
//	this->price = price;
//	this->rarity = rarity;
//	this->itemType = ItemType::Consumable;
//	this->effectValue = effectValue;
//}
//
//Elixir::~Elixir()
//{
//}
//
//void Elixir::Use(Character* character)
//{
//	// 최대 체력 증가
//	character->SetMaxHP(character->GetMaxHP() + this->effectValue);
//	// 현재 체력 증가
//	// character->SetCurrentHP(character->GetCurrentHP() + this->effectValue);
//}
