﻿#include "EquipableItem.h"
#include "Character.h"
#include <iostream>
#include<map>


EquipableItem::EquipableItem()
{
}

EquipableItem::EquipableItem(string name, int price, Rarity rarity, string equipType, map<string, int> baseStat, int enchantLevel, string desc)
{
	this->name = name;
	this->price = price;
	this->rarity = rarity;
	this->equipType = equipType;
	this->baseStat = baseStat;
	this->enchantLevel = enchantLevel;

	this->itemType = ItemType::Equipable;
	this->description = desc;
}

EquipableItem::EquipableItem(string name, int price, Rarity rarity, string equipType, map<string, int> baseStat, int enchantLevel, BuffStat buffStat, string desc)
{
	this->name = name;
	this->price = price;
	this->rarity = rarity;
	this->equipType = equipType;
	this->baseStat = baseStat;
	this->enchantLevel = enchantLevel;

	this->buffStat = buffStat;
	this->itemType = ItemType::Equipable;
	this->description = desc;
}

EquipableItem::~EquipableItem()
{
}

string EquipableItem::GetEquipType()
{
	return this->equipType;
}

EquipmentType EquipableItem::GetType()
{
	return this->type;
}

BuffStat EquipableItem::GetBuffStat()
{
	return this->buffStat;
}

map<string, int> EquipableItem::GetBaseStat()
{
	return this->baseStat;
}

int EquipableItem::GetEnchantLevel()
{
	return this->enchantLevel;
}

void EquipableItem::SetEnchantLevel(const int& level)
{
	this->enchantLevel = level;
	if (this->buffStat.attackPower != 0)
	{
		this->buffStat.attackPower += enchantLevel * 5;
	}
	else if (this->buffStat.attackPower != 0)
	{
		this->buffStat.armor += enchantLevel * 5;
	}
	else if (this->buffStat.attackPower != 0)
	{
		this->buffStat.maxHP += enchantLevel * 5;
	}
}

bool EquipableItem::IsEquipping()
{
	return this->isEquipping;
}

void EquipableItem::SetEquipping(const bool& equipping)
{
	this->isEquipping = equipping;
}


void EquipableItem::EquipEffect(Character& player)
{
	//if (equipType == "Weapon")
	//{
	//	if (player.GetWeaponSlot() != nullptr)
	//	{
	//		player.GetWeaponSlot()->SetEquipping(false);
	//		player.SetAttackPower(player.GetAttackPower() - player.GetWeaponSlot()->GetBaseStat()["Damage"]);
	//	}
	//	player.SetWeaponSlot(this);
	//	player.SetAttackPower(player.GetAttackPower() + this->GetBaseStat()["Damage"]);
	//	this->SetEquipping(true);
	//	cout << "You equipped " << player.GetWeaponSlot()->GetName() << "! AttackPower is now : " << player.GetAttackPower() << endl;

	//}
	/*else if (equipType == "Armor")
	{
		if (player.GetArmorSlot() != nullptr)
		{
			player.GetArmorSlot()->SetEquipping(false);
			player.SetDefPower(player.GetDefPower() - player.GetArmorSlot()->GetBaseStat()["Defence"]);

		}
		player.SetArmorSlot(this);
		player.SetDefPower(player.GetDefPower() + this->GetBaseStat()["Defence"]);
		this->SetEquipping(true);
		cout << "You equipped " << player.GetArmorSlot()->GetName() << "! Defence is now : " << player.GetDefPower() << endl;

	}*/
}

