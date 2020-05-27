/*************************************************************************
    > File Name: Timer.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Monday, March 23, 2020 PM07:18:38 HKT
 ************************************************************************/
#include "Timer.h"
using namespace std;

AtomicInt64 Timer::s_numCreated_;

void Timer::restart(Timestamp now) 
{
	if(repeat_)
		expiration_ = addTime(now, interval_);
	else
		expiration_ = Timestamp::invalid();
}
