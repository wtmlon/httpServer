/*************************************************************************
    > File Name: CountDownLatch.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 PM08:39:23 HKT
 ************************************************************************/
#include "CountDownLatch.h"

using namespace std;

CountDownLatch::CountDownLatch(int count)
	: mutex_(), condition_(mutex_), count_(count) {

	}

void CountDownLatch::wait(){
	MutexLockGuard lock(mutex_);
	while(count_ > 0) condition_.wait();
}

void CountDownLatch::countDown(){
	MutexLockGuard lock(mutex_);
	--count_;
	if(count_ == 0) condition_.notifyAll();
}
