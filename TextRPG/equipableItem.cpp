#include "EquipableItem.h"
#include "Character.h"
#include <iostream>
#include<map>
void EquipableItem::EquipEffect(Character& player)
{
	if (equipType == "Weapon")
	{
		if (player.GetWeaponSlot() != nullptr)
		{
			player.GetWeaponSlot()->SetEquipping(false);
			player.SetAttackPower(player.GetAttackPower() - player.GetWeaponSlot()->GetBaseStat()["Damage"]);
		}
		player.SetWeaponSlot(this);
		player.SetAttackPower(player.GetAttackPower() + this->GetBaseStat()["Damage"]);
		this->SetEquipping(true);
		cout << "You equipped " << player.GetWeaponSlot()->GetName() << "! AttackPower is now : " << player.GetAttackPower() << endl;

	}
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