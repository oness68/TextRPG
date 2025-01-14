#pragma once
#include "Character.h"
#include "Monster.h"
#include"Log.h"
#include<algorithm>
#include"EnumCollection.h"


class Battle
{
	struct saveState {
		int Power;
		int CurrentHP;
		int MaxHP;
	};
	saveState CharacterData;
	bool endBattle = false;
	bool myTurn = true;
	bool isWin = false;
	BaseMonster* battleMonster;
public:
	
	void restoreCharacterState(Character* player);
	void saveCharacterState(Character* player);
	void StageOfDifficulty();
	void NextTurn();
	int Input(int min,int max);
	void Fight(Character* Player,BaseMonster* monster, int stage);
	void PlayerAction(Character* Player);
	void AttackSystem(Character* Player);
	void isEndBattle(Character* Player);
	void MonsterAction(Character* Player);
	void LootAction(Character* Player);
	bool RandomSuccess(int probability);
};



