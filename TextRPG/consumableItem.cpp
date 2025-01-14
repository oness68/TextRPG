#include "ConsumableItem.h"
#include "Character.h"
#include <iostream>
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