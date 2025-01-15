#include "Character.h"
#include "Item.h"
#include "ConsumableItem.h"
#include "EquipableItem.h"
#include <format>
#include <iostream>


using namespace std;

Character::Character(const string& name)
{
	this->name = name;
	// cout << "캐릭터 " << name << " 생성 완료!";
	// cout << " 레벨 : " << level << ", 체력 : " << currentHP << " / " << maxHP << ", 공격력 : " << attackPower << endl;
}

Character::~Character(){}

void Character::DisplayStatus()
{
	cout << GetCharacterStatusString();
}

const string& Character::GetCharacterStatusString()
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


int Character::GetCurrentHP() { return this->currentHP; }
int Character::GetMaxHP() { return 0; }
const int& Character::GetAttackPower()
{
	return this->attackPower; // + 아이템 + 버프
}

void Character::SetCurrentHP(int hp) { this->currentHP = hp; }
void Character::SetMaxHP(int hp) { this->maxHP = hp; }
void Character::SetAttackPower(int attackPower) { this->attackPower = attackPower; }

void Character::TakeDamage(const int& damage)
{
	// TODO : 방어력에 대한 데미지 계산식 적용
	currentHP -= damage;
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


// ========== 인벤토리 및 아이템 상점관련 ==========
map<Item*, int> Character::GetInventory()
{
	return this->inventory;
}

const int& Character::GetGold()
{
	return this->gold;
}

void Character::TakeItem(Item* item)//수정 이인화-------------------------
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

void Character::UseItem(Item* item)//수정 이인화-------------------
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

void Character::BuyItem(Item* item)
{
}

void Character::SellItem(string itemKey)
{
}

void Character::RemoveItem(Item* item)//추가 이인화---------
{
	if (inventory.find(item) != inventory.end())
	{
		inventory[item]--;
		if (inventory[item] == 0) {
			inventory.erase(item);
		}
	}
}

void Character::LevelUp()
{
	if (level < maxLevel)
	{
		currentExp -= requiredLevelUpExp;

		IncreaseMaxHP(level);
		IncreaseAttackPower(level);
		IncreaseRequireLevelUpExp(level);

		level++;
		if (level == maxLevel)
		{
			currentExp = requiredLevelUpExp;
			//cout << "최대 레벨에 도달했습니다." << endl;
		}
	}
	else
	{

	}
}

void Character::IncreaseMaxHP(const int& level)
{
	maxHP += level * 20;
}

void Character::IncreaseAttackPower(const int& level)
{
	attackPower += level * 5;
}

void Character::IncreaseRequireLevelUpExp(const int& level)
{
	requiredLevelUpExp += level * 10;
}


