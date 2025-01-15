#ifndef ITEMFACTORY_H_
#define ITEMFACTORY_H_

#include "Item.h"
#include "ConsumableItem.h"
#include "EquipableItem.h"
#include <iostream>
//#include <vector>
#include <algorithm>
#include <random>

enum ItemList
{
	모험가의장검,		// 시작아이템

	고블린가죽,
	고블린귀,
	고블린의낡은단검,

	고블린족장의반지,	//보스 몬스터 잡을시 일정확률로 드랍, ItemType=Archive, 공격력 10 증가
};

class ItemFactory
{
public:
	static ItemFactory& GetInstance();
	vector<Item*> GenerateRandomItems(int count);

	Item* GenerateItem(string itemName);
	//Item* GenerateItem(enum ItemList itemList);
private:
	static ItemFactory* instance;

	ItemFactory();
	~ItemFactory();
	ItemFactory(const ItemFactory&) = delete;
	ItemFactory& operator=(const ItemFactory&) = delete;

	map<string, Item*> items;
};

#endif // !ITEMFACTORY_H_

