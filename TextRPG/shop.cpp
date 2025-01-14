#include"Shop.h"
#include"ItemInterface.h"
#include"AllItem.cpp"
#include "Enchancer.h"

Shop::Shop()
{
	AllItem allItems;
	shopInven = allItems.GetRandomItems(3);
}

Shop::~Shop()
{
	for (auto item : shopInven)
	{
		delete item;
	}
}

void Shop::BuyItem(Character& player)
{
	cout << "You have " << player.GetGold() << "gold\n" << endl;
	cout << "Select the items you want to buy!" << endl;
	for (int i = 0;i < shopInven.size();i++)
	{
		cout << i + 1 << ". " << shopInven[i]->GetName() << " - " << shopInven[i]->GetPrice() << " gold" << "[" << shopInven[i]->GetItemType() << "]" << endl;
	}
	int choice;
	cin >> choice;
	if (choice < 1 || choice>shopInven.size())
	{
		cout << "Invalid choice" << endl;
		return;
	}
	else
	{
		Item* selectedItem = shopInven[choice - 1];
		if (player.GetGold() >= selectedItem->GetPrice())
		{
			player.TakeGold(-selectedItem->GetPrice());
			player.TakeItem(selectedItem);
			cout << "You bought" << selectedItem->GetName() << "!\n" << endl;
			cout << "Left gold : " << player.GetGold() << endl;
			shopInven.erase(shopInven.begin() + (choice - 1));
		}
		else
		{
			cout << "Not enough gold" << endl;
		}
	}
	for (auto item : shopInven)delete item;
}

void Shop::SellItem(Character& player)
{
	map<Item*, int> inventory = player.GetInventory();
	if (inventory.empty()) {
		cout << "You have no items to sell!" << endl;
		return;
	}
	cout << "Your inventory" << endl;
	int index = 1;
	vector <Item*> invenItems;
	for (const auto& item : inventory)
	{
		cout << index << ". " << item.first << " (x" << item.second << ")" << " [Price at Sale : " << item.first->GetDepreciationRate() << "gold]" << endl;
		invenItems.push_back(item.first);
		index++;
	}
	cout << "Select the item you want to sell!" << endl;
	int choice;
	cin >> choice;
	if (choice<1 || choice>invenItems.size()) {
		cout << "Invaild choice" << endl;
		return;
	}
	Item* selectedItem = invenItems[choice - 1];
	int sellPrice = selectedItem->GetDepreciationRate();

	player.TakeGold(sellPrice);
	player.RemoveItem(selectedItem);
	cout << "You sold " << selectedItem->GetName() << " for " << sellPrice << "gold!" << endl;
	cout << "Left gold : " << player.GetGold() << endl;
}

void Shop::UseEnchancer(Character& player)
{
	Enchancer enchancer;
	map<Item*, int> inventory = player.GetInventory();
	vector<Item*> enchantableItems = enchancer.GetEnchanceableItems(inventory);

	if (enchantableItems.empty())
	{
		cout << "No Items for enchancement" << endl;
		return;
	}
	cout << "Select an item to Enchance!" << endl;
	for (int i = 0;i < enchantableItems.size();i++)
	{
		cout << i + 1 << ". " << enchantableItems[i]->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantableItems[i])->GetEnchantLevel() << ")" << endl;
	}
	int choice;
	cin >> choice;
	if (choice<1 || choice>enchantableItems.size())
	{
		cout << "Invalid choice!" << endl;
		return;
	}
	EquipableItem* itemToEnchant = dynamic_cast<EquipableItem*>(enchantableItems[choice - 1]);
	EquipableItem* enchantedItem = enchancer.EnchanceItem(itemToEnchant);

	if (enchantedItem != itemToEnchant)
	{
		player.RemoveItem(itemToEnchant);
		player.TakeItem(enchantedItem);
		cout << "Item enchanted successfully!" << endl;
	}
	else
	{
		cout << "Item enchantment failed! No changes made to the item!" << endl;
	}


}