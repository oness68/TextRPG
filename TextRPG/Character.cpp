#include "Character.h"
#include "Item.h"
#include "ItemFactory.h"
#include "ConsumableItem.h"
#include "EquipableItem.h"
#include <format>
#include <iostream>


using namespace std;

Character::Character(const string& name)
{
	this->name = name;
	TakeItem(ItemFactory::GetInstance().GenerateItem("모험가의장검"));

	//cout << "캐릭터 " << name << " 생성 완료!";
	//cout << " 레벨 : " << level << ", 체력 : " << currentHP << " / " << maxHP << ", 공격력 : " << attackPower << endl;
}

Character::~Character() {}

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
map<string, class Inventory> Character::GetInventory()
{
	return this->inventory;
}

vector<Inventory> Character::GetInventoryItems(enum class ItemType type = ItemType::Unknown)
{
	vector<Inventory> inventoryItems;

	switch (type)
	{
	case ItemType::Unknown:
		for (auto inventory : inventory)
		{
			inventoryItems.push_back(inventory.second);
		}
		break;
	case ItemType::Equipable:
	case ItemType::Consumable:
	case ItemType::Archive:
	case ItemType::Default:
		for (auto inventory : inventory)
		{
			if (inventory.second.itemType == type)
			{
				inventoryItems.push_back(inventory.second);
			}
		}
		break;
	default:
		break;
	}
	return inventoryItems;
}

const int& Character::GetGold() { return this->gold; }

void Character::TakeItem(Item* item)
{
	string itemName = item->GetName();
	if (inventory.find(itemName) == inventory.end())
	{
		inventory[itemName] = Inventory(item, item->GetType(), 1);
		//cout << format("신규 아이템이 추가됐습니다!! 아이템 이름 : {}, 개수 : {}", itemName, inventory[itemName].Count) << endl;
	}
	else
	{
		inventory[itemName].Count++;
		//cout << format("기존 아이템 개수가 추가됐습니다!! 아이템 이름 : {}, 개수 : {}", itemName, inventory[itemName].Count) << endl;
	}
}

void Character::UseItem(const string& itemKey)
{
	if (inventory.find(itemKey) == inventory.end())
	{
		throw ExceptionHandler(ErrorCode::Unknown, "아이템이 없습니다.");
	}
	else
	{
		Inventory selectedItem = inventory[itemKey];
		if (selectedItem.itemType == ItemType::Consumable)
		{
			ConsumableItem* cosumableItem = dynamic_cast<ConsumableItem*>(selectedItem.item);
			cosumableItem->ConsumeEffect(*this);

			ReduceInventory(itemKey);
		}
		else
		{
			throw ExceptionHandler(ErrorCode::Unknown, "소비 아이템이 아닙니다.");
		}
	}
}

void Character::BuyItem(Item* item)
{
	if (gold < item->GetPrice())
	{
		// cout << "소지 골드가 부족합니다"
	}
	else
	{
		gold -= item->GetPrice();
		TakeItem(item);
	}
}

void Character::SellItem(string itemKey)
{
	if (inventory.find(itemKey) == inventory.end())
	{
		throw ExceptionHandler(ErrorCode::Unknown, "아이템이 없습니다.");
	}
	else
	{
		Inventory selectedItem = inventory[itemKey];
		gold += selectedItem.item->GetPrice();

		ReduceInventory(itemKey);
	}
}

void Character::ReduceInventory(const string& itemKey)
{
	Inventory& selectedItem = inventory[itemKey];
	selectedItem.Count--;

	//cout << "인벤토리의 아이템이 감소됐습니다!\n"
	//	<< format("이름 : {}, 수량 : {}", selectedItem.item->GetName(), selectedItem.Count) << endl;

	if (selectedItem.Count == 0)
	{
		inventory.erase(itemKey);
		//cout << "인벤토리에서 아이템 항목을 제거합니다!" << endl;
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

