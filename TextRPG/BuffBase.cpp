#include "BuffBase.h"


BuffBase::BuffBase(BuffStat stat, int duration)
{
	this->buffStat = stat;
	this->duration = duration;
}

BuffType BuffBase::GetBuffType()
{
	return this->buffType;
}

BuffStat BuffBase::GetBuffStat()
{
	return this->buffStat;
}


int BuffBase::GetDuration()
{
	return this->duration;
}
