#include "Character.h"
#include "ItemInterface.h"//추가 이인화--------------------
#include "ConsumableItem.h"//추가 이인화
#include "EquipableItem.h"//추가 이인화
#include <format>
#include <iostream>


using namespace std;

Character::Character(const string& name)
{
	this->name = name;
	cout << "캐릭터 " << name << " 생성 완료!";
	cout << " 레벨 : " << level << ", 체력 : " << currentHP << " / " << maxHP << ", 공격력 : " << attackPower << endl;
}

Character::~Character()
{
}

const int& Character::GetAttackPower()
{
	return this->attackPower; // + 아이템 + 버프
}

void Character::SetAttackPower(int attackPower)
{
	this->attackPower = attackPower;
}

const int& Character::GetGold()
{
	return this->gold;
}

void Character::DisplayStatus()
{
	cout << GetCharacterStatusString();
}

string Character::GetCharacterStatusString()
{
	string returnValue;
	returnValue += format("이름 : {}\n", name);
	returnValue += format("레벨 : {}\n", level);
	returnValue += format("HP : {}/{}\n", currentHP, maxHP);
	returnValue += format("공격력 : {}\n", attackPower);
	//returnValue += format("방어력 : {}\n", armor);
	returnValue += format("Gold : {}\n", gold);
	returnValue += format("경험치 : {}/{}\n", currentExp, requiredLevelUpExp);

	return returnValue;

}

/*map<EquipmentType, int> Character::GetEquipmentItems()
{
	return this->EquipableItems;//수정 이인화--------------------------
}*/

map<ItemInterface*, int> Character::GetInventory()//수정 이인화-----------------------------
{
	return this->inventory;
}

void Character::UseItem(ItemInterface* item)//수정 이인화-------------------
{
	if (ConsumableItem* consumable = dynamic_cast<ConsumableItem*>(item))
	{
		consumable->ConsumeEffect(*this);
		RemoveItem(item);
		return;
	}
	else if (EquipableItem* equipable = dynamic_cast<EquipableItem*>(item))
	{
		//equipable->EquipEffect(*this);
		return;
	}
}

void Character::RemoveItem(ItemInterface* item)//추가 이인화---------
{
	if (inventory.find(item) != inventory.end())
	{
		inventory[item]--;
		if (inventory[item] == 0) {
			inventory.erase(item);
		}
	}
}

void Character::TakeExp(const int& exp)
{
	currentExp += exp;
	if (currentExp >= requiredLevelUpExp)
	{
		LevelUp();
	}
}

void Character::TakeGold(const int& gold)
{
	this->gold += gold;
}

void Character::TakeItem(ItemInterface* item)//수정 이인화-------------------------
{
	// TO DO : if Can't Find Add Key
	if (inventory.find(item) != inventory.end())
	{
		inventory[item]++;
	}
	else
	{
		inventory[item] = 1;
	}
	//수정 이인화 ---------------------------인벤토리에 있으면 +1 없으면 새로 1
}

void Character::TakeDamage(const int& damage)
{
	currentHP -= damage;
}

int Character::GetCurrentHP()
{
	return 0;
}

int Character::GetMaxHP()
{
	return 0;
}

void Character::SetCurrentHP(int HP)
{
	this->currentHP = HP;
}

void Character::SetMaxHP(int HP)
{
	this->maxHP = HP;
}

void Character::LevelUp()
{
	//TO DO : Level Up
	currentExp -= requiredLevelUpExp;
	level++;

	IncreaseMaxHP(level);
	IncreaseAttackPower(level);
	IncreaseRequireLevelUpExp(level);
}

void Character::IncreaseMaxHP(const int& level)
{
}

void Character::IncreaseAttackPower(const int& level)
{
}

void Character::IncreaseRequireLevelUpExp(const int& level)
{

}


