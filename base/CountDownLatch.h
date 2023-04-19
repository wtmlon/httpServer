/*************************************************************************
    > File Name: CountDownLatch.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 PM08:32:25 HKT
 ************************************************************************/
#pragma once
#include "Condition.h"
#include "MutexLock.h"
#include "noncopyable.h"

using namespace std;

class CountDownLatch : noncopyable {
	public:
		explicit CountDownLatch(int count);
		void wait();
		void countDown();

	private:
		mutable MutexLock mutex_;//can be modified by const function
		Condition condition_;
		int count_;
};
