#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H
#include"Character.h"
#include"Battle.h"
#include"Monster.h"
#include <string>
#include <map>


class BattleManager
{
private:

	static BattleManager* Battleinstance;
	
	BattleManager() = default;
	~BattleManager() = delete;
	BattleManager(const BattleManager&) = delete;
	BattleManager& operator=(const BattleManager&) = delete;
public:
	static BattleManager* GetInstance();



	void BeginBattle(Character* player, int stage);
	NormalMonster CreateNormalMonster();
	

};

#endif