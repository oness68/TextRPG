#pragma once
#include "Character.h"
#include "Monster.h"
#include"Character.h"
#include<algorithm>


class Battle
{
	bool endBattle = false;
	bool myTurn = true;
	
	
public:

	void StageOfDifficulty();
	void NextTurn(bool& flag);
	int Input(int min,int max);
	virtual void Fight(Character* Player, int stage) = 0;
	void PlayerAction(Character* Player);
	void AttackSystem(Character* Player);
	//void setTarget(NormalMonster monster) { this->monster = monster; }
	void MonsterAction();
	//void NextTrun(bool& turn);
};



class NormalBattle :public Battle
{

};


//class NormalBattle :public Battle
//{
//	NormalMonster Data;
//	
//public:
//	void Fight(Character* Player, NormalMonster* monster, int stage) override;
//	void PlayerAction() override;
//	void MonsterAction() override;
//	void StageOfDifficulty(int stage) override;
//};
//
//class NamedBattle :public Battle
//{
//public:
//
//	void Fight(Character* Player, NormalMonster* monster, int stage) override;
//	void PlayerAction() override;
//	void MonsterAction() override;
//};
//
//class BossBattle :public Battle
//{
//public:
//	void Fight(Character* Player, NormalMonster* monster, int stage) override;
//	void PlayerAction() override;
//	void MonsterAction() override;
//};
//

