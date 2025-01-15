#include "ItemFactory.h"
#include "format"

#pragma region ItemDefine

#pragma endregion

ItemFactory* ItemFactory::instance = nullptr;
ItemFactory& ItemFactory::GetInstance()
{
	if (instance == nullptr)
		instance = new ItemFactory();

	return *instance;
}

ItemFactory::ItemFactory()
{
	// Insert Consumable Item
	// Heal Potion
	items.insert(make_pair("LowHPPotion", new ConsumableItem("LowHPPotion", 50, Rarity::C, EffectType::HealCurrentHP, 30)));
	items.insert(make_pair("MiddleHPPotion", new ConsumableItem("MiddleHPPotion", 100, Rarity::R, EffectType::HealCurrentHP, 50)));
	items.insert(make_pair("HightHPPotion", new ConsumableItem("MiddleHPPotion", 200, Rarity::SR, EffectType::HealCurrentHP, 100)));
	
	//Attack Power Up Potion
	items.insert(make_pair("LowAttackPotion", new ConsumableItem("LowAttackPotion", 20, Rarity::C, EffectType::DamageUp, 30)));
	items.insert(make_pair("MiddleAttackPotion", new ConsumableItem("MiddleAttackPotion", 40, Rarity::R, EffectType::DamageUp, 50)));
	items.insert(make_pair("HightAttackPotion", new ConsumableItem("HightAttackPotion", 60, Rarity::SR, EffectType::DamageUp, 100)));

	// Elixir
	items.insert(make_pair("LowElixir", new ConsumableItem("LowElixir", 50, Rarity::C, EffectType::IncreaseMaxHP, 100)));
	items.insert(make_pair("MiddleElixir", new ConsumableItem("MiddleElixir", 100, Rarity::R, EffectType::IncreaseMaxHP, 200)));
	items.insert(make_pair("HightElixir", new ConsumableItem("HightElixir", 200, Rarity::SR, EffectType::IncreaseMaxHP, 400)));

	// Default Item
	items.insert(make_pair("고블린가죽", new Item("고블린가죽", 50, Rarity::C)));
	items.insert(make_pair("고블린귀", new Item("고블린귀", 50, Rarity::C)));
	items.insert(make_pair("고블린라이더의안장", new Item("고블린라이더의안장", 50, Rarity::C)));

	/*items.push_back(new LeatherArmor());
	items.push_back(new ChainMail());
	items.push_back(new MetalArmor());*/
}


ItemFactory::~ItemFactory()
{
	for (auto item : items) delete item.second;
}

vector<Item*> ItemFactory::GenerateRandomItems(int count)
{
	vector<Item*> shuffledItems;
	for (auto item : items)
	{
		shuffledItems.push_back(item.second);
	}
	random_device rd;
	mt19937 gen(rd());
	shuffle(shuffledItems.begin(), shuffledItems.end(), gen);

	vector<Item*>randomItems(shuffledItems.begin(), shuffledItems.begin() + count);
	return randomItems;
}

Item* ItemFactory::GenerateItem(string itemName)
{
	Item* item = nullptr;
	if (items.find(itemName) != items.end())
	{
		item = items[itemName];
	}
	else
	{
		throw ExceptionHandler(ErrorCode::NullItemKey, format("생성하려는 아이템이 아이템 목록에 없습니다. 아이템 이름 :{}\n", itemName));
	}

	return item;
}

//Item* ItemFactory::GenerateItem(enum ItemList itemList)
//{
//	return nullptr;
//}


