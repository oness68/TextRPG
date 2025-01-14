#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H
#include"Character.h"
#include"Battle.h"
#include"Monster.h"
#include <string>
#include <map>
#include <vector>





class BattleManager
{
	
	
private:

	BaseMonster* monster;

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
	
};



#endif