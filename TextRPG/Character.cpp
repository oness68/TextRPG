#include "Character.h"

#include "ItemFactory.h"
#include "ConsumableItem.h"
#include "EquipableItem.h"
#include "Log.h"
#include "Menu.h"

#include <format>
#include <iostream>

using namespace std;

Character::Character(const string& name)
{
	this->name = name;
	DisplayStatus();
	InitEquipMentItem();
}

void Character::InitEquipMentItem()
{
	Item* startItem = ItemFactory::GetInstance().GenerateItem("모험가의장검");
	TakeItem(startItem);
	EquipItem(dynamic_cast<EquipableItem*>(startItem));
}

Character::~Character() {}

void Character::DisplayStatus()
{
	Log::GetInstance()->PrintLog(GetCharacterStatusString(), false);
}

void Character::DisplayStatus(string reason, int hp, int power, int level, int exp)
{
	string temp = reason += "\n";
	temp += format("이름 : {}\n", name);

	if (level != 0)
	{
		temp += format("레벨 : {} + (1)\n", level + 1);
	}
	else
	{
		temp += format("레벨 : {}\n", level);
	}

	if (hp != 0)
	{
		temp += format("HP : {}/{} + ({})\n", currentHP, GetMaxHP(), hp);
	}
	else
	{
		temp += format("HP : {}/{}\n", currentHP, GetMaxHP());
	}

	if (power != 0)
	{
		temp += format("공격력 : {} + ({})\n", GetAttackPower(), power);
	}
	else
	{
		temp += format("공격력 : {}\n", GetAttackPower());
	}

	temp += format("Gold : {}\n", gold);

	if (exp != 0)
	{
		temp += format("경험치 : {}/{} + ({})\n", currentExp, requiredLevelUpExp, exp);
	}
	else
	{
		temp += format("경험치 : {}/{}\n", currentExp, requiredLevelUpExp);
	}

	Log::GetInstance()->PrintLog(temp, false);
}

const string Character::GetCharacterStatusString()
{
	string returnValue;
	returnValue += format("이름 : {}\n", name);
	returnValue += format("레벨 : {}\n", level);
	returnValue += format("HP : {}/{}\n", currentHP, GetMaxHP());
	returnValue += format("공격력 : {}\n", GetAttackPower());
	//returnValue += format("방어력 : {}\n", armor);
	returnValue += format("Gold : {}\n", gold);
	returnValue += format("경험치 : {}/{}\n", currentExp, requiredLevelUpExp);

	return returnValue;
}


const int& Character::GetCurrentHP() { return this->currentHP; }
const int& Character::GetMaxHP()
{
	int calculateMaxHP = this->maxHP + equipmentBuffStat.maxHP + archiveBuffStat.maxHP + buffStat.maxHP;
	return calculateMaxHP;
}
const int& Character::GetAttackPower()
{
	int calculateAP = this->attackPower + equipmentBuffStat.attackPower + archiveBuffStat.attackPower + buffStat.attackPower;
	return calculateAP;
}
const int& Character::GetRequiredLevelUpExp() { return this->requiredLevelUpExp; }


void Character::SetCurrentHP(int hp)
{
	if (hp > maxHP)
	{
		this->currentHP = maxHP;
	}
	else
	{
		this->currentHP = hp;
	}
}
void Character::SetMaxHP(int hp)
{
	this->maxHP = hp;
}
void Character::AddMaxHP(int amount)
{
	this->maxHP += amount;
}


void Character::SetAttackPower(int attackPower)
{
	this->attackPower = attackPower;
}
void Character::AddAttackPower(int amount)
{
	this->attackPower += amount;
}


void Character::TakeDamage(const int& damage)
{
	// TODO : 방어력에 대한 데미지 계산식 적용
	currentHP -= (damage - armor);
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

vector<Inventory> Character::GetInventoryItems(enum class ItemType type)
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

#pragma region Inventory 관련 Method들 TO DO : GameManager로 이전
void Character::DisplayInventory()
{
	vector<string> menuItems = {
	"장비",
	"소모품",
	"도감",
	"기타",
	"나가기"
	};

	vector<function<void()>> actions = {
	[&]() {
			//cout << "******* 장비아이템 ********" << endl;
			DisplayEquipMentItem();
		},
		[&]() {
			//cout << "******* 소모품 ********" << endl;
			DisplayConsumableItem();
		},
		[&]() {
			//cout << "******* 도감 ********" << endl;
			DisplayArchiveItem();
		},
		[&]() {
			//cout << "******* 기타 ********" << endl;
			DisplayEtcItem();
		},
		[&]() {
			cout << "인벤토리를 종료합니다." << endl;
		}
	};

	Menu menuSystem(menuItems, actions);

	while (true) {
		menuSystem.DisplayMenu((int)EBag, true, "");
		menuSystem.RunMenu((int)EBag, true, "");

		if (menuSystem.GetSelectedIndex() == 4) {
			break;
		}

		cout << endl; // 메뉴 간격 조정
	}
}

void Character::DisplayEquipMentItem()
{
	vector<Inventory> displayInventory = GetInventoryItems(ItemType::Equipable);
	vector<string> menuItems;
	vector<function<void()>> actions;

	if (displayInventory.size() > 0)
	{
		for (Inventory inventory : displayInventory)
		{
			EquipableItem* item = dynamic_cast<EquipableItem*>(inventory.item);
			EquipableItem& selectedItem = *item;
			BuffStat itemStat = selectedItem.GetBuffStat();

			string temp = format("- {} [+{}] ", item->GetName(), item->GetEnchantLevel());
			if (selectedItem.IsEquipping())
			{
				temp += "(장착중)";
			}

			menuItems.push_back(temp);

			actions.push_back([&]()
				{
					string itemDetail = format("[{}] 상세 정보\n\n", selectedItem.GetName());
					itemDetail += format("아이템 설명 : {}\n", selectedItem.GetDescription());
					itemDetail += format("장비 장착효과 : 공격력+{}, 방어력+{}, 체력+{}\n", selectedItem.GetBuffStat().attackPower, selectedItem.GetBuffStat().armor, selectedItem.GetBuffStat().maxHP);
					itemDetail += format("아이템 구매가격 : {}, 판매 가격 : {}\n", selectedItem.GetPrice(), selectedItem.GetSellPrice());

					// TODO : Replace : Menu System(장착, 나가기)
					vector<string> itemDetailMenu = {
						"\n[장착]",
						"[장비 아이템 인벤토리로 돌아가기]"
					};

					vector<function<void()>> itemDetailAction = {
						[&]()
						{
							if (selectedItem.IsEquipping())
							{
								Log::GetInstance()->PrintLog("WARNING : 이미 장착중인 아이템 입니다.", (int)EBag, true);
							}
							else
							{
								EquipItem(&selectedItem);
							}

							Sleep(2000);
						},
						[&]()
						{
						}
					};

					Menu itemDetailSystem(itemDetailMenu, itemDetailAction);
					while (true) {
						itemDetailSystem.DisplayMenu((int)EBag, true, itemDetail);
						itemDetailSystem.RunMenu((int)EBag, true, itemDetail);

						if (itemDetailSystem.GetSelectedIndex() == itemDetailMenu.size() - 1)
						{
							break;
						}

						cout << endl; // 메뉴 간격 조정
					}
					return;
				});

		}
	}
	else
	{
		menuItems.push_back("***** 장비 아이템이 텅 비어있습니다 *****");
		actions.push_back([&]() {});
	}

	menuItems.push_back("\n[인벤토리로 돌아가기]");
	actions.push_back([&]() {});

	Menu menuSystem(menuItems, actions);
	while (true) {
		menuSystem.DisplayMenu((int)EBag, true, "");
		menuSystem.RunMenu((int)EBag, true, "");

		if (menuSystem.GetSelectedIndex() == menuItems.size() - 1)
		{
			break;
		}

		cout << endl; // 메뉴 간격 조정
	}
}

void Character::DisplayConsumableItem()
{
	vector<Inventory> displayInventory = GetInventoryItems(ItemType::Consumable);
	vector<string> menuItems;
	vector<function<void()>> actions;

	if (displayInventory.size() > 0)
	{
		for (Inventory inventory : displayInventory)
		{
			ConsumableItem* item = dynamic_cast<ConsumableItem*>(inventory.item);
			ConsumableItem& selectedItem = *item;

			string temp = format("- {}  개수 : {}ea", selectedItem.GetName(), inventory.Count);
			menuItems.push_back(temp);

			actions.push_back([&]()
				{
					string itemDetail = format("[{}] 상세 정보\n\n", selectedItem.GetName());
					itemDetail += format("아이템 설명 : {}\n", selectedItem.GetDescription());
					itemDetail += "아이템 사용효과 : ";
					switch (selectedItem.GetEffectType())
					{
					case EffectType::Unknown:
						break;
					case EffectType::HealCurrentHP:
						itemDetail += format("체력을 {}만큼 회복합니다.\n", selectedItem.GetEffectValue());
						break;
					case EffectType::IncreaseMaxHP:
						itemDetail += format("최대 체력을 {}만큼 증가시킵니다.\n", selectedItem.GetEffectValue());
						break;
					case EffectType::IncreaseAttackPower:
						itemDetail += format("공격력을 {}만큼 증가시킵니다.\n", selectedItem.GetEffectValue());
						break;
					case EffectType::DamageUp:
						itemDetail += format("공격력을 {}턴동안 {}만큼 증가시킵니다.\n", selectedItem.GetDuration(), selectedItem.GetEffectValue());
						break;
					default:
						break;
					}

					itemDetail += format("아이템 구매가격 : {}, 판매 가격 : {}\n", selectedItem.GetPrice(), selectedItem.GetSellPrice());


					vector<string> itemDetailMenu = { "\n[소비 아이템 인벤토리로 돌아가기]" };
					vector<function<void()>> itemDetailAction = { [&]() {} };

					Menu itemDetailSystem(itemDetailMenu, itemDetailAction);
					while (true) {
						itemDetailSystem.DisplayMenu((int)EBag, true, itemDetail);
						itemDetailSystem.RunMenu((int)EBag, true, itemDetail);

						if (itemDetailSystem.GetSelectedIndex() == itemDetailMenu.size() - 1)
						{
							break;
						}

						cout << endl; // 메뉴 간격 조정
					}

					return;
				});
		}
	}
	else
	{
		menuItems.push_back("***** 소모품이 텅 비어있습니다 *****");
		actions.push_back([&]() {});
	}

	menuItems.push_back("\n[인벤토리로 돌아가기]");
	actions.push_back([&]() {});

	Menu menuSystem(menuItems, actions);
	while (true) {
		menuSystem.DisplayMenu((int)EBag, true, "");
		menuSystem.RunMenu((int)EBag, true, "");

		if (menuSystem.GetSelectedIndex() == menuItems.size() - 1)
		{
			break;
		}

		cout << endl; // 메뉴 간격 조정
	}
}

void Character::DisplayArchiveItem()
{
	vector<Inventory> displayInventory = GetInventoryItems(ItemType::Archive);
	vector<string> menuItems;
	vector<function<void()>> actions;

	if (displayInventory.size() > 0)
	{
		for (Inventory inventory : displayInventory)
		{
			ArchiveItem* item = dynamic_cast<ArchiveItem*>(inventory.item);
			ArchiveItem& selectedItem = *item;
			BuffStat itemStat = selectedItem.GetBuffStat();

			string temp = format("- {}  개수 : {}ea", item->GetName(), inventory.Count);
			menuItems.push_back(temp);

			actions.push_back([&]()
				{
					string itemDetail = format("[{}] 상세 정보\n\n", selectedItem.GetName());
					itemDetail += format("아이템 설명 : {}\n", selectedItem.GetDescription());
					itemDetail += format("도감 수집 효과 : 공격력+{}, 방어력+{}, 체력+{}\n", selectedItem.GetBuffStat().attackPower, selectedItem.GetBuffStat().armor, selectedItem.GetBuffStat().maxHP);
					itemDetail += format("아이템 구매가격 : {}, 판매 가격 : {}\n", selectedItem.GetPrice(), selectedItem.GetSellPrice());


					vector<string> itemDetailMenu = { "\n[도감 아이템 인벤토리로 돌아가기]" };
					vector<function<void()>> itemDetailAction = { [&]() {} };

					Menu itemDetailSystem(itemDetailMenu, itemDetailAction);
					while (true) {
						itemDetailSystem.DisplayMenu((int)EBag, true, itemDetail);
						itemDetailSystem.RunMenu((int)EBag, true, itemDetail);

						if (itemDetailSystem.GetSelectedIndex() == itemDetailMenu.size() - 1)
						{
							break;
						}

						cout << endl; // 메뉴 간격 조정
					}
					return;
				});

		}
	}
	else
	{
		menuItems.push_back("***** 도감 아이템이 텅 비어있습니다 *****");
		actions.push_back([&]() {});
	}

	menuItems.push_back("\n[인벤토리로 돌아가기]");
	actions.push_back([&]() {});

	Menu menuSystem(menuItems, actions);
	while (true) {
		menuSystem.DisplayMenu((int)EBag, true, "");
		menuSystem.RunMenu((int)EBag, true, "");

		if (menuSystem.GetSelectedIndex() == menuItems.size() - 1)
		{
			break;
		}

		cout << endl; // 메뉴 간격 조정
	}
}

void Character::DisplayEtcItem()
{
	vector<Inventory> displayInventory = GetInventoryItems(ItemType::Default);
	vector<string> menuItems;
	vector<function<void()>> actions;

	if (displayInventory.size() > 0)
	{
		for (Inventory inventory : displayInventory)
		{
			Item& selectedItem = *inventory.item;
			string temp = format("- {}  개수 : {}ea", selectedItem.GetName(), inventory.Count);
			menuItems.push_back(temp);

			actions.push_back([&]()
				{
					string itemDetail = format("[{}] 상세 정보\n\n", selectedItem.GetName());
					itemDetail += format("아이템 설명 : {}\n", selectedItem.GetDescription());
					itemDetail += format("아이템 구매가격 : {}, 판매 가격 : {}\n", selectedItem.GetPrice(), selectedItem.GetSellPrice());


					vector<string> itemDetailMenu = { "\n[기타 아이템 인벤토리로 돌아가기]" };
					vector<function<void()>> itemDetailAction = { [&]() {} };

					Menu itemDetailSystem(itemDetailMenu, itemDetailAction);
					while (true) {
						itemDetailSystem.DisplayMenu((int)EBag, true, itemDetail);
						itemDetailSystem.RunMenu((int)EBag, true, itemDetail);

						if (itemDetailSystem.GetSelectedIndex() == itemDetailMenu.size() - 1)
						{
							break;
						}

						cout << endl; // 메뉴 간격 조정
					}
					return;
				});

		}
	}
	else
	{
		menuItems.push_back("***** 기타 아이템이 텅 비어있습니다 *****");
		actions.push_back([&]() {});
	}

	menuItems.push_back("\n[인벤토리로 돌아가기]");
	actions.push_back([&]() {});

	Menu menuSystem(menuItems, actions);
	while (true) {
		menuSystem.DisplayMenu((int)EBag, true, "");
		menuSystem.RunMenu((int)EBag, true, "");

		if (menuSystem.GetSelectedIndex() == menuItems.size() - 1)
		{
			break;
		}

		cout << endl; // 메뉴 간격 조정
	}
}

#pragma endregion

const int& Character::GetGold() { return this->gold; }

void Character::TakeItem(Item* item)
{
	string itemName = item->GetName();
	if (inventory.find(itemName) == inventory.end())
	{
		inventory[itemName] = Inventory(item, item->GetType(), 1);

		TryAddArchiveItem(item);
	}
	else
	{
		inventory[itemName].Count++;
		TryAddArchiveItem(item);
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
		//Log::GetInstance()->PrintLog("소지 골드가 부족합니다.\n", false);
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

	if (selectedItem.Count == 0)
	{
		inventory.erase(itemKey);
		// Log::GetInstance()->PrintLog("인벤토리에서 아이템 항목을 제거합니다!", false);
	}

	TryRemoveArchiveItem(selectedItem);
}

void Character::TurnEnd()
{
	TryRemoveBuff();
}

void Character::TryAddBuff(BuffBase& buffBase)
{
	Log::GetInstance()->PrintLog(format("\n[ 디/버프가 추가됐습니다!! 지속턴수 : {} ]\n\n", buffBase.duration), false);
	if (buffBase.duration == 0)
	{
		Log::GetInstance()->PrintLog(format("[ Buff가 아무런 영향을 주지 않습니다. ]\n"), false);
	}
	else
	{
		buffContainer.push_back(buffBase);
		buffStat += buffBase.buffStat;

		string temp = format("************* 디/버프 효과 발동 ****************");
		DisplayStatus(temp, buffBase.buffStat.maxHP, buffBase.buffStat.attackPower);
	}
}

void Character::TryRemoveBuff()
{
	for (auto it = buffContainer.begin(); it != buffContainer.end(); )
	{
		it->duration--;
		if (it->duration <= 0)
		{
			auto removedBuff = *it;
			buffStat -= removedBuff.buffStat;

			string temp = format("************* 버프 종료 ****************");
			DisplayStatus(temp, -removedBuff.buffStat.maxHP, -removedBuff.buffStat.attackPower);

			it = buffContainer.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Character::TryAddArchiveItem(Item* item)
{
	string itemName = item->GetName();
	if (inventory[itemName].itemType == ItemType::Archive)
	{
		BuffStat archiveItemBuffStat = dynamic_cast<ArchiveItem*>(item)->GetBuffStat();
		archiveBuffStat += archiveItemBuffStat;

		string temp = format("************* 도감 아이템 획득 ****************");
		DisplayStatus(temp, archiveItemBuffStat.maxHP, archiveItemBuffStat.attackPower);
	}
}

void Character::TryRemoveArchiveItem(Inventory inventory)
{
	if (inventory.itemType == ItemType::Archive)
	{
		BuffStat archiveItemBuffStat = dynamic_cast<ArchiveItem*>(inventory.item)->GetBuffStat();
		archiveBuffStat -= archiveItemBuffStat;

		string temp = format("************* 도감 아이템 소실 ****************");
		DisplayStatus(temp, archiveItemBuffStat.maxHP, archiveItemBuffStat.attackPower);
	}
}

void Character::EquipItem(EquipableItem* equipableItem)
{
	if (equipItemContainer.find(equipableItem->GetType()) != equipItemContainer.end())
	{
		auto currentItem = equipItemContainer[equipableItem->GetType()];

		// 현재 장비 해제 처리
		currentItem->SetEquipping(false);
		equipmentBuffStat -= currentItem->GetBuffStat();
		equipItemContainer.erase(equipableItem->GetType());
	}

	Equip(equipableItem);
}

void Character::Equip(EquipableItem* equipableItem)
{
	BuffStat buffStat = equipableItem->GetBuffStat();
	equipItemContainer[equipableItem->GetType()] = equipableItem;
	equipmentBuffStat += equipableItem->GetBuffStat();
	equipableItem->SetEquipping(true);

	string temp = "************* 장비 장착 ****************";
	DisplayStatus(temp, buffStat.maxHP, buffStat.attackPower);
}

void Character::LevelUp()
{
	if (level < maxLevel)
	{
		currentExp -= requiredLevelUpExp;

		IncreaseMaxHP();
		IncreaseAttackPower();
		IncreaseRequireLevelUpExp();

		string temp = "************* 레벨업 ****************";
		DisplayStatus(temp, increaseMaxHPAmount, increaseAPAmount, level, increaseExpAmount);

		this->level++;
		if (level == maxLevel)
		{
			currentExp = requiredLevelUpExp;
			// Log::GetInstance()->PrintLog("최대 레벨에 도달했습니다.", false);
		}
	}
}

void Character::IncreaseMaxHP()
{
	this->maxHP += increaseMaxHPAmount;
}

void Character::IncreaseAttackPower()
{
	this->attackPower += increaseAPAmount;
}

void Character::IncreaseRequireLevelUpExp()
{
	this->requiredLevelUpExp += increaseExpAmount;
}

