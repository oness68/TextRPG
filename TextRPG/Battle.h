#pragma once
#include "Character.h"
#include "Monster.h"

class Battle
{

public:
	virtual void Fight(Character* Player,NormalMonster* monster, int stage) = 0;
	virtual void PlayerAction() = 0;
	virtual void MonsterAction() = 0;
	void NextTrun(bool& turn);
};



class NormalBattle :public Battle
{
	NormalMonster Data;
	bool myTurn=true;
	bool endBattle=false;
public:
	void Fight(Character* Player, NormalMonster* monster, int stage) override;
	void PlayerAction() override;
	void MonsterAction() override;

};

class NamedBattle :public Battle
{
public:

	void Fight(Character* Player, NormalMonster* monster, int stage) override;
	void PlayerAction() override;
	void MonsterAction() override;
};

class BossBattle :public Battle
{
public:
	void Fight(Character* Player, NormalMonster* monster, int stage) override;
	void PlayerAction() override;
	void MonsterAction() override;
};


