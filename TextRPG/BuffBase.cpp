#include "BuffBase.h"


BuffBase::BuffBase(BuffStat stat, int duration)
{
	buffStat = buffStat;
	duration = duration;
}

BuffType BuffBase::GetBuffType()
{
	return this->buffType;
}


int BuffBase::GetDuration()
{
	return this->duration;
}
