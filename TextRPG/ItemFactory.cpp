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
	// Default Item
	string desc = "갓 모험을 떠나는 모험가에게 지급되는 기본 장검. 기본적인 공격력을 제공합니다.";
	items.insert(make_pair("모험가의장검", new EquipableItem("모험가의장검", 300, Rarity::C, "Weapon", { {"Damage", 50} }, 0, BuffStat(10, 0, 0), desc)));

	// Heal Potion
	desc = "하급 체력 회복 포션이다. 딸기맛이 난다";
	items.insert(make_pair("하급체력회복포션", new ConsumableItem("하급체력회복포션", 50, Rarity::C, EffectType::HealCurrentHP, 30, desc)));
	desc = "중급 체력 회복 포션이다. 더 큰 상처를 회복할 수 있다.";
	items.insert(make_pair("중급체력회복포션", new ConsumableItem("중급체력회복포션", 100, Rarity::R, EffectType::HealCurrentHP, 60, desc)));
	desc = "상급 체력 회복 포션이다. 심각한 상처도 회복이 가능하다.";
	items.insert(make_pair("상급체력회복포션", new ConsumableItem("상급체력회복포션", 200, Rarity::SR, EffectType::HealCurrentHP, 120, desc)));

	//Attack Power Up Potion
	desc = "하급 공격 부스터다. TMI : 공격부스터 계열은 코로 흡입한다.";
	items.insert(make_pair("하급공격부스터", new ConsumableItem("하급공격부스터", 20, Rarity::C, EffectType::DamageUp, 30, 3, desc)));
	desc = "중급 공격 부스터다. 적을 더 강하게 공격할 수 있다.";
	items.insert(make_pair("중급공격부스터", new ConsumableItem("중급공격부스터", 50, Rarity::R, EffectType::DamageUp, 50, 5, desc)));
	desc = "상급 공격 부스터다. 모든 힘을 끌어올려 적을 제압할 수 있다.";
	items.insert(make_pair("상급공격부스터", new ConsumableItem("상급공격부스터", 100, Rarity::SR, EffectType::DamageUp, 100, 7, desc)));

	// Elixir
	desc = "최대 체력을 올려주는 하급 엘릭서다. 던전을 탐험하다 운이 좋으면 구할수 있을것이다.";
	items.insert(make_pair("하급체력엘릭서", new ConsumableItem("하급체력엘릭서", 50, Rarity::C, EffectType::IncreaseMaxHP, 20, desc)));
	desc = "중급 체력 엘릭서다. 모험가의 체력을 크게 강화시켜준다.";
	items.insert(make_pair("중급체력엘릭서", new ConsumableItem("중급체력엘릭서", 200, Rarity::R, EffectType::IncreaseMaxHP, 50, desc)));
	desc = "상급 체력 엘릭서다. 오크에 버금가는 체력을 제공한다.";
	items.insert(make_pair("상급체력엘릭서", new ConsumableItem("상급체력엘릭서", 500, Rarity::SR, EffectType::IncreaseMaxHP, 100, desc)));
	desc = "근신경계를 깨워주는 하급 엘릭서다. 한약맛이난다.";
	items.insert(make_pair("하급근력엘릭서", new ConsumableItem("하급근력엘릭서", 50, Rarity::C, EffectType::IncreaseAttackPower, 120, desc)));
	//장비 아이템베이스
	desc = "장인은 도구탓을 하지 않는다고 한다. 하지만 용사들은 항상 도구에 선택받아왔었지...";
	items.insert(make_pair("선택받은용사의검", new EquipableItem("선택받은용사의검", 3000, Rarity::SSR, "Weapon", { {"Damage", 50} }, 0, BuffStat(50, 0, 0), desc)));
	desc = "전투에 최적화된 도끼. 묵직한 공격력을 제공합니다.";
	items.insert(make_pair("전투도끼", new EquipableItem("전투도끼", 1500, Rarity::R, "Weapon", { {"Damage", 60} }, 0, BuffStat(20, 0, 0), desc)));
	desc = "튼튼하고 가벼운 가죽으로 만들어진 갑옷. 이동하기 편리하다.";
	items.insert(make_pair("가죽갑옷", new EquipableItem("가죽갑옷", 500, Rarity::C, "Armor", { {"Defense", 10} }, 0, BuffStat(0, 20, 0), desc)));
	desc = "철로 만든 갑옷. 강력한 방어력을 제공합니다.";
	items.insert(make_pair("체인메일", new EquipableItem("체인메일", 1000, Rarity::R, "Armor", { {"Defense", 20} }, 0, BuffStat(0, 50, 0), desc)));
	desc = "적의 공격을 튕겨내는 가시가 달린 갑옷.";
	items.insert(make_pair("가시갑옷", new EquipableItem("가시갑옷", 2000, Rarity::SR, "Armor", { {"Defense", 30}, {"Reflect", 5} }, 0, BuffStat(10, 70, 0), desc)));
	desc = "낡은 검. 오래되어 공격력이 낮다.";
	items.insert(make_pair("낡은검", new EquipableItem("낡은검", 150, Rarity::C, "Weapon", { {"Damage", 20} }, 0, BuffStat(5, 0, 0), desc)));

	//보스몹 드랍 도감아이템
	desc = "고블린족장의유물이다. 밤일을 조금더 잘할수 있게 된다.";
	items.insert(make_pair("고블린족장의유물", new ArchiveItem("고블린족장의유물", 500, Rarity::C, BuffStat(5, 0, 0), desc)));
	desc = "트롤의 심장. 생명력을 상징하는 유물이다."; 
	items.insert(make_pair("트롤의심장", new ArchiveItem("트롤의심장", 1200, Rarity::R, BuffStat(0, 0, 50), desc)));
	desc = "트렌트의 열매. 자연의 정수를 담고 있다.";
	items.insert(make_pair("트렌트의열매", new ArchiveItem("트렌트의열매", 1500, Rarity::SR, BuffStat(20, 0, 30), desc)));
	desc = "드래곤의 머리입니다. 강력한 존재의 증거로 매우 희귀합니다.";
	items.insert(make_pair("드래곤의머리", new ArchiveItem("드래곤의머리", 5000, Rarity::SSR, BuffStat(0, 0, 100), desc)));

	//몬스터 별 특수 드랍템
	desc = "고블린의 귀다. 고블린 토벌 의뢰를 완수하기위해 잘 챙기자.";
	items.insert(make_pair("고블린귀", new Item("고블린귀", 50, Rarity::C, desc)));
	desc = "오크의 머리털. 강한 냄새가 난다.";
	items.insert(make_pair("오크의머리털", new Item("오크의머리털", 80, Rarity::C, desc)));
	desc = "트롤의 송곳니. 강력한 생명력을 상징한다.";
	items.insert(make_pair("트롤의송곳니", new Item("트롤의송곳니", 100, Rarity::R, desc)));
	desc = "늑대의 발톱. 사냥꾼들에게 인기 있는 수집품이다.";
	items.insert(make_pair("늑대발톱", new Item("늑대발톱", 50, Rarity::C)));
	desc = "슬라임의 점액질. 독특한 향과 점도가 있다.";
	items.insert(make_pair("슬라임의점액질", new Item("슬라임의점액질", 40, Rarity::C, desc)));
	desc = "고블린 라이더의 안장. 희귀한 수집품이다.";
	items.insert(make_pair("고블린라이더의안장", new Item("고블린라이더의안장", 150, Rarity::R, desc)));
	desc = "트윈헤드 트롤의 두개골. 무시무시한 유물이다.";
	items.insert(make_pair("트윈헤드트롤의두개골", new Item("트윈헤드트롤의두개골", 200, Rarity::R, desc)));
	desc = "엔트의 씨앗. 생명의 기운이 느껴진다.";
	items.insert(make_pair("엔트의씨앗", new Item("엔트의씨앗", 250, Rarity::SR, desc)));
	//노말몹 드랍템
	desc = "짐승의 가죽. 기본적인 방어구 제작에 사용된다.";
	items.insert(make_pair("짐승의가죽", new Item("짐승의가죽", 50, Rarity::C, desc)));
	desc = "부서진 뼈. 몬스터의 잔해로 활용 가치는 적다.";
	items.insert(make_pair("부서진뼈", new Item("부서진뼈", 30, Rarity::C, desc)));
	desc = "마물의 피. 강력한 주술 재료로 사용된다.";
	items.insert(make_pair("마물의피", new Item("마물의피", 100, Rarity::R, desc)));
	//보스몹 드랍템
	desc = "두꺼운 가죽. 방어구 제작에 적합하다.";
	items.insert(make_pair("두꺼운가죽", new Item("두꺼운가죽", 200, Rarity::R, desc)));
	desc = "단단한 뼈. 내구성이 높아 다양한 용도로 사용된다.";
	items.insert(make_pair("단단한뼈", new Item("단단한뼈", 250, Rarity::R, desc)));
	desc = "마물의 뜨거운 피. 강력한 주술 재료로 희귀하다.";
	items.insert(make_pair("마물의뜨거운피", new Item("마물의뜨거운피", 300, Rarity::SR, desc)));
	//드래곤 드랍템
	desc = "드래곤의 가죽. 전설적인 내구성을 자랑한다.";
	items.insert(make_pair("드래곤의가죽", new Item("드래곤의가죽", 3000, Rarity::SSR, desc)));
	desc = "드래곤의 뼈. 강력한 힘이 깃들어 있다.";
	items.insert(make_pair("드래곤의뼈", new Item("드래곤의뼈", 4000, Rarity::SSR, desc)));
	desc = "드래곤의 피. 생명의 정수가 응축되어 있다.";
	items.insert(make_pair("드래곤의피", new Item("드래곤의피", 5000, Rarity::SSR, desc)));


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


