#ifndef ENCHANCER_H_
#define ENCHANCER_H_

#include "EquipableItemDecorator.h"
#include <random>
#include <iostream>
using namespace std;

class Enchancer
{
private:
	random_device rd;
	mt19937 gen;
public:
	Enchancer();
	EquipableItem* EnchanceItem(EquipableItem* item);

	vector<Item*> GetEnchanceableItems(map<Item*, int>& inventory);
};

#endif // !ENCHANCER_H_