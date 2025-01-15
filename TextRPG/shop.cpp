#include"Shop.h"
#include"Item.h"
#include"AllItem.cpp"
#include "Enchancer.h"
#include "ItemFactory.h"

Shop::Shop()
{
	shopInven = ItemFactory::GetInstance().GenerateRandomItems(3);
}

Shop::~Shop()
{
	for (auto item : shopInven)
	{
		delete item;
	}
}

void Shop::DisplayItem()
{
	if (shopInven.empty())
	{
		cout << "\nThe shop is out of items!\n" << endl;
		return;
	}
	for (int i = 0; i < shopInven.size(); i++)
	{
		cout << i + 1 << ". " << shopInven[i]->GetName() << " - " << shopInven[i]->GetPrice() << " gold" << " [" << (int)shopInven[i]->GetType() << "]" << endl;
	}
}

void Shop::BuyItem(Character& player)
{
	if (shopInven.empty())
	{
		cout << "\nThe shop is out of items!" << endl;
		return;
	}

	cout << "You have " << player.GetGold() << "gold\n" << endl;
	cout << "Select the items you want to buy!" << endl;

	for (int i = 0; i < shopInven.size(); i++)
	{
		if (shopInven[i] != nullptr)
		{
			cout << i + 1 << ". " << shopInven[i]->GetName() << " - " << shopInven[i]->GetPrice() << " gold" << " [" << (int)shopInven[i]->GetType() << "]" << endl;
		}
		else
		{
			cout << i + 1 << ". Invalid Item" << endl;
		}
	}

	//for (int i = 0;i < shopInven.size();i++)
	//{
	//	cout << i + 1 << ". " << shopInven[i]->GetName() << " - " << shopInven[i]->GetPrice() << " gold" << "[" << (int)shopInven[i]->GetType() << "]" << endl;
	//}

	cout << shopInven.size() + 1 << ". Leave the shop" << endl;

	int choice;
	cin >> choice;

	if (choice == shopInven.size() + 1)
	{
		cout << "\nYou left the shop" << endl;
		return;
	}

	if (choice < 1 || choice>shopInven.size() + 1)
	{
		cout << "\nInvalid choice" << endl;
		return;
	}
	else
	{
		Item* selectedItem = shopInven[choice - 1];
		if (player.GetGold() >= selectedItem->GetPrice())
		{
			player.BuyItem(selectedItem);
			//player.TakeGold(-selectedItem->GetPrice());
			//player.TakeItem(selectedItem);

			cout << "\nYou bought [" << selectedItem->GetName() << "]!\n" << endl;
			cout << "Left gold : " << player.GetGold() << endl;

			shopInven.erase(shopInven.begin() + (choice - 1));
		}
		else
		{
			cout << "\nNot enough gold" << endl;
		}
	}
}

void Shop::SellItem(Character& player)
{
	auto inventory = player.GetInventory();
	if (inventory.empty())
	{
		cout << "You have no items to sell!" << endl;
		return;
	}
	cout << "\nSelect the item you want to sell!\n" << endl;
	cout << "[Inventory]\n" << endl;
	int index = 1;
	vector <Item*> invenItems;
	for (const auto& item : inventory)
	{
		cout << index << ". " << item.second.item->GetName() << " (x" << item.second.Count << ")" << " [Price at Sale - " << item.second.item->GetSellPrice() << " gold]" << endl;
		invenItems.push_back(item.second.item);
		index++;
	}

	cout << index << ". Leave the Inventory" << endl;

	int choice;
	cin >> choice;
	if (choice == index)
	{
		cout << "\nYou left the Inventory" << endl;
		return;
	}
	if (choice<1 || choice>invenItems.size()) {
		cout << "\nInvaild choice" << endl;
		return;
	}

	Item* selectedItem = invenItems[choice - 1];
	int sellPrice = selectedItem->GetSellPrice();

	player.SellItem(selectedItem->GetName());

	//player.TakeGold(sellPrice);
	//player.SellItem(selectedItem->GetName());

	cout << "You sold " << selectedItem->GetName() << " for " << sellPrice << "gold!" << endl;
	cout << "Left gold : " << player.GetGold() << endl;
}

void Shop::UseEnchancer(Character& player)
{
	Enchancer enchancer;
	auto inventory = player.GetInventory();
	vector<Item*> enchantableItems = enchancer.GetEnchanceableItems(inventory);

	if (enchantableItems.empty())
	{
		cout << "\nNo Items for enchancement" << endl;
		return;
	}
	int enchantPrice = 100;//강화비용

	cout << "\nYou have " << player.GetGold() << " gold." << endl;
	cout << "\nSelect an item to Enchance! (Once " << enchantPrice << " gold)\n" << endl;

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
	if (player.GetGold() < enchantPrice)
	{
		cout << "Not enough gold to enchant!" << endl;
		return;
	}

	EquipableItem* itemToEnchant = dynamic_cast<EquipableItem*>(enchantableItems[choice - 1]);
	EquipableItem* enchantedItem = enchancer.EnchanceItem(itemToEnchant);

	if (enchantedItem != itemToEnchant)
	{
		//inventory[itemToEnchant->GetName()].item = enchantedItem;
		player.ReduceInventory(itemToEnchant->GetName());
		player.TakeItem(enchantedItem);
		cout << "Item enchanted successfully!" << endl;
		cout << enchantedItem->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel() << ")" << endl;
	}
	else
	{
		cout << "Item enchantment failed! No changes made to the item!" << endl;
		cout << enchantedItem->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel() << ")" << endl;
	}

	player.TakeGold(-enchantPrice);
	cout << "You used " << enchantPrice << " gold for enchant!(Left gold : " << player.GetGold() << ")" << endl;
}
