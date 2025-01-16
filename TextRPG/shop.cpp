#include "Shop.h"
#include "Item.h"
#include "Enchancer.h"
#include "ItemFactory.h"
#include "Log.h"
#include <format>
#include "Menu.h"
#include "ProcessInput.h"

Log* logger = Log::GetInstance();
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
		logger->PrintLog("The shop is out of items!", (int)EShop, false);//cout << "\nThe shop is out of items!\n" << endl;
		return;
	}
	for (int i = 0; i < shopInven.size(); i++)
	{
		string logMessage = format("{}. {} - {} gold [{}]", i + 1, shopInven[i]->GetName(), shopInven[i]->GetPrice(), (int)shopInven[i]->GetType());
		logger->PrintLog(logMessage, (int)EShop, false);
		//cout << i + 1 << ". " << shopInven[i]->GetName() << " - " << shopInven[i]->GetPrice() << " gold" << " [" << (int)shopInven[i]->GetType() << "]" << endl;
	}
}
void Shop::BuyItem(Character& player)
{
	int choice;
	string logMessage;

	if (shopInven.empty())
	{
		logger->PrintLog("\n구매 가능한 아이템이 없습니다!", (int)EShop, true);
		Sleep(1500);
		return;
	}

	// =============================================================================
	logger->PrintLog("\n구매할 아이템을 선택해주세요!\n", (int)EShop, true);
	logger->PrintLog(format("보유금 {} gold\n\n", player.GetGold()), false);

	logger->PrintLog("===========구매 가능===========\n\n", false);
	for (int i = 0; i < shopInven.size(); i++)
	{
		logMessage = format("{}.{} - {} gold\n", i + 1, shopInven[i]->GetName(), shopInven[i]->GetPrice());
		logger->PrintLog(logMessage, false);
	}
	logger->PrintLog("\n==============================\n\n", false);
	logger->PrintLog(format("{}.나가기\n", shopInven.size() + 1), false);

	logger->PrintLog("\n선택 : ", false); 
	// =============================================================================
	// 입력이 정상적인지 판단 => 입력이 int가 아니면 int 값을 받아올때까지 반복
	while (!(cin >> choice))
	{
		// Clear Input Buffer
		cin.clear();
		while (std::cin.get() == '\n') continue;

		logger->PrintLog("잘못된 입력입니다.다시입력하세요.\n", (int)EShop, true);
		// =============================================================================
		logger->PrintLog("\n구매할 아이템을 선택해주세요!\n", false);
		logger->PrintLog(format("보유금 {} gold\n\n", player.GetGold()), false);

		logger->PrintLog("===========구매 가능===========\n\n", false);
		for (int i = 0; i < shopInven.size(); i++)
		{
			logMessage = format("{}.{} - {} gold\n", i + 1, shopInven[i]->GetName(), shopInven[i]->GetPrice());
			logger->PrintLog(logMessage, false);
		}
		logger->PrintLog("\n==============================\n\n", false);
		logger->PrintLog(format("{}.나가기\n", shopInven.size() + 1), false);

		logger->PrintLog("\n선택 : ", false);
		// =============================================================================
	}

	if (choice == shopInven.size() + 1)
	{
		logger->PrintLog("아이템 구매를 종료했습니다.\n", (int)EShop, true);
		Sleep(1500);
	}
	else if (choice < 1 || choice > shopInven.size() + 1)
	{
		logger->PrintLog(format("잘못된 선택입니다. 입력 : {}", choice), (int)EShop, true);
		Sleep(1500);
	}
	else
	{
		// 아이템을 정상적으로 선택했을시
		Item* selectedItem = shopInven[choice - 1];
		if (player.GetGold() >= selectedItem->GetPrice())
		{
			player.BuyItem(selectedItem);

			logMessage = format("[{}]을(를) 구매했습니다!\n\n", selectedItem->GetName());
			logMessage += format("남은 보유금 {} gold\n", player.GetGold());
			logger->PrintLog(logMessage, (int)EShop, true);
			
			shopInven.erase(shopInven.begin() + (choice - 1));
		}
		else
		{
			logger->PrintLog("\n :( 보유 골드가 부족합니다.\n", (int)EShop, false);
		}

		Sleep(1500);
	}

	return;
}

void Shop::SellItem(Character& player)
{
	map<string, class Inventory> inventory = player.GetInventory();
	int choice;
	int index = 1;

	if (inventory.empty())
	{
		logger->PrintLog("판매 가능한 아이템이 없습니다!\n", (int)EShop, true);
		Sleep(1500);
		return;
	}

	//======================================================================
	logger->PrintLog("판매할 아이템을 선택해주세요.\n", (int)EShop, true);
	logger->PrintLog("===========판매 가능===========\n\n", false);
	vector <Item*> invenItems;
	for (const auto& item : inventory)
	{
		string logMessage = format("{}. {} (x{}) [판매가 - {} gold]\n", index, item.second.item->GetName(), item.second.Count, item.second.item->GetSellPrice());
		logger->PrintLog(logMessage, false);
		invenItems.push_back(item.second.item);
		index++;
	}
	logger->PrintLog("\n==============================\n\n", false);
	logger->PrintLog(format("{}. 나가기\n", index), false);

	cout << "선택 : ";
	// =============================================================================
	// 입력이 정상적인지 판단 => 입력이 int가 아니면 int 값을 받아올때까지 반복
	while (!(cin >> choice))
	{
		// Clear Input Buffer
		cin.clear();
		while (std::cin.get() == '\n') continue;
		logger->PrintLog("잘못된 입력입니다.다시입력하세요.\n", (int)EShop, true);

		//======================================================================
		logger->PrintLog("판매할 아이템을 선택해주세요.\n", (int)EShop, true);
		logger->PrintLog("===========판매 가능===========\n\n", false);
		index = 1;
		vector <Item*> invenItems;
		for (const auto& item : inventory)
		{
			string logMessage = format("{}. {} (x{}) [판매가 - {} gold]\n", index, item.second.item->GetName(), item.second.Count, item.second.item->GetSellPrice());
			logger->PrintLog(logMessage, false);
			invenItems.push_back(item.second.item);
			index++;
		}
		logger->PrintLog("\n==============================\n\n", false);
		logger->PrintLog(format("{}. 나가기\n", index), false);
		cout << "선택 : ";
		// =============================================================================
	}

	if (choice == index)
	{
		logger->PrintLog("아이템 판매를 종료했습니다.\n", (int)EShop, true);
		Sleep(1500);
	}
	else if (choice < 1 || choice > invenItems.size()) 
	{
		logger->PrintLog("잘못된 입력입니다.\n", (int)EShop, true);
		Sleep(1500);
	}
	else
	{
		// 정상적으로 판매 했을시
		Item* selectedItem = invenItems[choice - 1];
		player.SellItem(selectedItem->GetName());

		string logMessage = format("{}을(를) {}gold 에 판매했습니다!\n\n", selectedItem->GetName(), selectedItem->GetSellPrice());
		logMessage += format("보유금 {} gold\n", player.GetGold());
		logger->PrintLog(logMessage, EShop, true);

		Sleep(1500);
	}

	return;
}

void Shop::UseEnchancer(Character& player)
{
	Enchancer enchancer;
	auto inventory = player.GetInventory();
	vector<Item*> enchantableItems = enchancer.GetEnchanceableItems(inventory);
	if (enchantableItems.empty())
	{
		logger->PrintLog("강화할 수 있는 아이템이 없습니다.\n", (int)EShop, true);
		//cout << "\nNo Items for enchancement" << endl;
		int choice;
		cout << "\n아무 키나 눌러 확인\n";
		PI::ClearInputBuffer();
		PI::isInputEnabled = true;
		cin >> choice;
		PI::isInputEnabled = false;
		return;
	}
	int enchantPrice = 100;//강화비용
	logger->PrintLog(format("보유금 {} gold\n\n", player.GetGold()), (int)EShop, true);
	//cout << "\nYou have " << player.GetGold() << " gold." << endl;
	logger->PrintLog(format("강화할 아이템을 선택해주세요! [강화 비용 {} gold]\n", enchantPrice), false);
	//cout << "\nSelect an item to Enchance! (Once " << enchantPrice << " gold)\n" << endl;
	logger->PrintLog("===========강화 가능===========\n\n", false);
	for (int i = 0; i < enchantableItems.size(); i++)
	{
		string logMessage = format("{}. {} (+{})\n", i + 1, enchantableItems[i]->GetName(), dynamic_cast<EquipableItem*>(enchantableItems[i])->GetEnchantLevel());
		logger->PrintLog(logMessage, false);
		//cout << i + 1 << ". " << enchantableItems[i]->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantableItems[i])->GetEnchantLevel() << ")" << endl;
	}
	logger->PrintLog("\n==============================\n", false);
	logger->PrintLog(format("{}. 나가기\n", enchantableItems.size() + 1), false);
	int choice;
	cout << "선택 : ";
	PI::ClearInputBuffer();
	PI::isInputEnabled = true;
	cin >> choice;
	PI::isInputEnabled = false;
	if (choice == enchantableItems.size() + 1)
	{
		logger->PrintLog("아이템 강화를 종료했습니다.\n", (int)EShop, true);
		int choice;
		cout << "\n아무 키나 눌러 확인\n";
		PI::ClearInputBuffer();
		PI::isInputEnabled = true;
		cin >> choice;
		PI::isInputEnabled = false;
		return;
	}
	if (choice<1 || choice>enchantableItems.size())
	{
		logger->PrintLog("잘못된 입력입니다.\n", (int)EShop, true);
		//cout << "Invalid choice!" << endl;
		int choice;
		cout << "\n아무 키나 눌러 확인\n";
		PI::ClearInputBuffer();
		PI::isInputEnabled = true;
		cin >> choice;
		PI::isInputEnabled = false;
		return;
	}
	if (player.GetGold() < enchantPrice)
	{
		logger->PrintLog("골드가 부족합니다.\n", (int)EShop, true);
		//cout << "Not enough gold to enchant!" << endl;
		int choice;
		cout << "\n아무 키나 눌러 확인\n";
		PI::ClearInputBuffer();
		PI::isInputEnabled = true;
		cin >> choice;
		PI::isInputEnabled = false;
		return;
	}
	EquipableItem* itemToEnchant = dynamic_cast<EquipableItem*>(enchantableItems[choice - 1]);
	EquipableItem* enchantedItem = enchancer.EnchanceItem(itemToEnchant);
	for (int i = 0; i < 2; i++)
	{
		logger->PrintLog("\n강화중.\n", (int)EShop, true);
		Sleep(500);
		logger->PrintLog("\n강화중..\n", (int)EShop, true);
		Sleep(500);
		logger->PrintLog("\n강화중...\n", (int)EShop, true);
		Sleep(500);
	}
	if (enchantedItem != itemToEnchant)
	{
		//inventory[itemToEnchant->GetName()].item = enchantedItem;
		player.ReduceInventory(itemToEnchant->GetName());
		player.TakeItem(enchantedItem);
		logger->PrintLog("아이템 강화에 성공했습니다!\n\n", (int)EShop, true);
		//cout << "Item enchanted successfully!" << endl;
		string logMessage = format("{}(+{})\n", enchantedItem->GetName(), dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel());
		logger->PrintLog(logMessage, false);
		//cout << enchantedItem->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel() << ")" << endl;
	}
	else
	{
		logger->PrintLog("아이템 강화에 실패했습니다.\n\n", (int)EShop, true);
		//cout << "Item enchantment failed! No changes made to the item!" << endl;
		string logMessage = format("{}(+{})\n", enchantedItem->GetName(), dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel());
		logger->PrintLog(logMessage, false);
		//cout << enchantedItem->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel() << ")" << endl;
	}
	player.TakeGold(-enchantPrice);
	logger->PrintLog(format("\n보유금 {} gold\n", player.GetGold()), false);
	//cout << "You used " << enchantPrice << " gold for enchant!(Left gold : " << player.GetGold() << ")" << endl;
	int choice3;
	cout << "\n아무 키나 눌러 확인\n";
	PI::ClearInputBuffer();
	PI::isInputEnabled = true;
	cin >> choice3;
	PI::isInputEnabled = false;
}