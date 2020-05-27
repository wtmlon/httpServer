/*************************************************************************
    > File Name: TimerId.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Monday, March 23, 2020 PM05:09:36 HKT
 ************************************************************************/
#pragma once
#include "base/copyable.h"

using namespace std;

class Timer;

class TimerId : public copyable {
	
	public:
		TimerId()
			:timer_(NULL),
			sequence_(0)
	{
		
	}
		TimerId(Timer* timer, int64_t seq)
			:timer_(timer),
			sequence_(seq)
		{
			
		}
		friend class TimerQueue;

	private:
		Timer * timer_;
		int64_t sequence_;
};


