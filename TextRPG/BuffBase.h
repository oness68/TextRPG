#pragma once
enum class BuffType
{
	Unknown,

	IncreaseMaxHP,
	DecreaseMaxHP,

	IncreaseAttackPower,
	DecreaseAttackPower,

	TakeExp,
};

class BuffStat
{
public:
	BuffStat() {}
	BuffStat(int attackPower, int armor, int maxHP)
	{
		this->attackPower = attackPower;
		this->armor = armor;
		this->maxHP = maxHP;
	}

	~BuffStat() {}

	int attackPower = 0;
	int armor = 0;
	int maxHP = 0;
	//double APIncreaseRate = 1;

	void operator+=(BuffStat& rhs)
	{
		attackPower += rhs.attackPower;
		armor += rhs.armor;
		maxHP += rhs.maxHP;
	}

	void operator+=(BuffStat&& rhs)
	{
		attackPower += rhs.attackPower;
		armor += rhs.armor;
		maxHP += rhs.maxHP;
	}

	void operator-=(BuffStat& rhs)
	{
		attackPower -= rhs.attackPower;
		armor -= rhs.armor;
		maxHP -= rhs.maxHP;
	}

	void operator-=(BuffStat&& rhs) noexcept
	{
		attackPower -= rhs.attackPower;
		armor -= rhs.armor;
		maxHP -= rhs.maxHP;
	}
};


class BuffBase
{
public:
	BuffBase(BuffStat stat, int duration);

	BuffType GetBuffType();
	BuffStat GetBuffStat();
	//int GetAddAmount();
	//double GetMultipleAmount();
	int GetDuration();

	BuffType buffType = BuffType::Unknown;
	BuffStat buffStat;
	int duration = 0;

private:
	//BuffType buffType = BuffType::Unknown;
	//BuffStat buffStat;
	//int duration = 0;
};

