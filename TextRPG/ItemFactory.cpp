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
	items.insert(make_pair("하급체력회복포션", new ConsumableItem("하급체력회복포션", 50, Rarity::C, EffectType::HealCurrentHP, 30)));
	items.insert(make_pair("중급체력회복포션", new ConsumableItem("중급체력회복포션", 100, Rarity::R, EffectType::HealCurrentHP, 50)));
	items.insert(make_pair("상급체력회복포션", new ConsumableItem("상급체력회복포션", 200, Rarity::SR, EffectType::HealCurrentHP, 100)));

	//Attack Power Up Potion
	items.insert(make_pair("하급공격부스터", new ConsumableItem("하급공격부스터", 20, Rarity::C, EffectType::DamageUp, 30, 3)));
	items.insert(make_pair("중급공격부스터", new ConsumableItem("중급공격부스터", 40, Rarity::R, EffectType::DamageUp, 50, 5)));
	items.insert(make_pair("상급공격부스터", new ConsumableItem("상급공격부스터", 60, Rarity::SR, EffectType::DamageUp, 100, 7)));

	// Elixir
	items.insert(make_pair("하급엘릭서", new ConsumableItem("하급엘릭서", 50, Rarity::C, EffectType::IncreaseMaxHP, 100)));
	items.insert(make_pair("중급엘릭서", new ConsumableItem("중급엘릭서", 100, Rarity::R, EffectType::IncreaseMaxHP, 200)));
	items.insert(make_pair("상급엘릭서", new ConsumableItem("상급엘릭서", 200, Rarity::SR, EffectType::IncreaseMaxHP, 400)));

	// Default Item

	items.insert(make_pair("모험가의장검", new EquipableItem("모험가의장검", 300, Rarity::C, "Weapon", { {"Damage", 50} }, 0, BuffStat(10, 0, 0))));

	//장비 아이템베이스
	items.insert(make_pair("선택받은용사의검", new EquipableItem("선택받은용사의검", 3000, Rarity::SSR, "Weapon", { {"Damage", 50} }, 0, BuffStat(50, 0, 0))));
	items.insert(make_pair("전투도끼", new EquipableItem("전투도끼", 1000, Rarity::R, "Weapon", { {"Damage", 50} }, 0, BuffStat(3, 0, 0))));
	items.insert(make_pair("가죽갑옷", new EquipableItem("가죽갑옷", 300, Rarity::C, "Armor", { {"Damage", 50} }, 0, BuffStat(0, 10, 0))));
	items.insert(make_pair("체인메일", new EquipableItem("체인메일", 500, Rarity::R, "Armor", { {"Damage", 50} }, 0, BuffStat(0, 20, 0))));
	items.insert(make_pair("가시갑옷", new EquipableItem("가시갑옷", 1000, Rarity::SR, "Armor", { {"Damage", 50} }, 0, BuffStat(10, 30, 0))));

	//보스몹 드랍 도감아이템
	items.insert(make_pair("고블린족장의유물", new ArchiveItem("고블린족장의유물", 500, Rarity::C, BuffStat(5, 0, 0))));
	items.insert(make_pair("트롤의심장", new ArchiveItem("트롤의심장", 500, Rarity::C, BuffStat(0, 0, 50))));
	items.insert(make_pair("트렌트의열매", new ArchiveItem("트렌트의열매", 500, Rarity::C, BuffStat(0, 0, 50))));
	items.insert(make_pair("드래곤의머리", new ArchiveItem("드래곤의머리", 500, Rarity::C, BuffStat(0, 0, 50))));
	//몬스터 별 특수 드랍템
	items.insert(make_pair("고블린귀", new Item("고블린귀", 50, Rarity::C)));
	items.insert(make_pair("오크의머리털", new Item("오크의머리털", 50, Rarity::C)));
	items.insert(make_pair("트롤의송곳니", new Item("트롤의송곳니", 50, Rarity::C)));
	items.insert(make_pair("늑대발톱", new Item("늑대발톱", 50, Rarity::C)));
	items.insert(make_pair("슬라임의점액질", new Item("슬라임의점액질", 50, Rarity::C)));
	items.insert(make_pair("고블린라이더의안장", new Item("고블린라이더의안장", 50, Rarity::C)));
	items.insert(make_pair("트윈헤드트롤의두개골", new Item("트윈헤드트롤의두개골", 50, Rarity::C)));
	items.insert(make_pair("엔트의씨앗", new Item("엔트의씨앗", 50, Rarity::C)));
	//노말몹 드랍템
	items.insert(make_pair("짐승의가죽", new Item("짐승의가죽", 50, Rarity::C)));
	items.insert(make_pair("부서진뼈", new Item("부서진뼈", 50, Rarity::C)));
	items.insert(make_pair("마물의피", new Item("마물의피", 50, Rarity::C)));
	items.insert(make_pair("낡은검", new EquipableItem("낡은검", 150, Rarity::C, "Weapon", { {"Damage", 30} }, 0, BuffStat(10, 0, 0))));
	//보스몹 드랍템
	items.insert(make_pair("두꺼운가죽", new Item("두꺼운가죽", 50, Rarity::C)));
	items.insert(make_pair("단단한뼈", new Item("단단한뼈", 50, Rarity::C)));
	items.insert(make_pair("마물의뜨거운피", new Item("마물의뜨거운피", 50, Rarity::C)));
	//드래곤 드랍템
	items.insert(make_pair("드래곤의가죽", new Item("드래곤의가죽", 50, Rarity::C)));
	items.insert(make_pair("드래곤의뼈", new Item("드래곤의뼈", 50, Rarity::C)));
	items.insert(make_pair("드래곤의피", new Item("드래곤의피", 50, Rarity::C)));


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
		if (item.second->GetType() == ItemType::Consumable || item.second->GetType() == ItemType::Equipable || item.second->GetType() == ItemType::Archive) {

			shuffledItems.push_back(item.second);
		}
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
		//throw ExceptionHandler(ErrorCode::NullItemKey, format("생성하려는 아이템이 아이템 목록에 없습니다. 아이템 이름 :{}\n", itemName));
	}

	return item;
}

//Item* ItemFactory::GenerateItem(enum ItemList itemList)
//{
//	return nullptr;
//}


