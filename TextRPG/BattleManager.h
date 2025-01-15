#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H
#include"Character.h"
#include"Battle.h"
#include"Monster.h"
#include <string>
#include <map>
#include <vector>
#include"EnumCollection.h"

class BattleManager
{
	
private:

	BaseMonster* monster;
	
	EnumPrintLog MonsterImage;
	static BattleManager* Battleinstance;

	BattleManager() = default;
	~BattleManager() = delete;
	BattleManager(const BattleManager&) = delete;
	BattleManager& operator=(const BattleManager&) = delete;
public:

	static BattleManager* GetInstance();
	BaseMonster* getMonster() { return monster; }
	void setMonster(BaseMonster* monster);
	void BeginBattle(Character* player, int stage);
	void CreateMonster(bool isNamde, int stage);
	EnumPrintLog getMonsterImage() { return MonsterImage; }
	void setMonsterImage(EnumPrintLog imageData) { this->MonsterImage = imageData; }

};



#endif