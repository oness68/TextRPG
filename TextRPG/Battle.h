#pragma once
#include "Character.h"
#include "Monster.h"
#include"Log.h"
#include<algorithm>
#include"EnumCollection.h"
#include"BattleManager.h"
#include<format>
#include"consumableItem.h"
#include"ItemFactory.h"
#include"Item.h"
#include "Menu.h"
class Battle
{
	struct saveStatus {
		int Power;
		int CurrentHP;
		int MaxHP;
	};
	EnumPrintLog Image;
	MonsterState state;
	saveStatus CharacterData;
	bool endBattle = false;
	bool myTurn = true;
	bool isWin = false;
	BaseMonster* battleMonster;
	bool nextTurn;
	string info;
	int stage;

private:
	void restoreCharacterState(Character* player);
	void saveCharacterState(Character* player);
	void StageOfDifficulty(int stage);
	void NextTurn(Character* Player);
	void PlayerAction(Character* Player);
	void AttackSystem(Character* Player);
	void isEndBattle(Character* Player);
	void MonsterAction(Character* Player);
	void LootAction(Character* Player);
	void MonsterSkill(Character* Player);
	void UseItem(Character* Player);
	void UpdateInfo(Character* Player);
	bool RandomSuccess(int probability);

public:
	
	void Fight(Character* Player,BaseMonster* monster, int stage);
	

};



