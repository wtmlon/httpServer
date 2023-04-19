/*************************************************************************
    > File Name: EventLoopThread.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 PM04:35:20 HKT
 ************************************************************************/
#pragma once
#include "EventLoop.h"
#include "base/Condition.h"
#include "base/MutexLock.h"
#include "base/Thread.h"
#include "base/noncopyable.h"

using namespace std;


class EventLoopThread : noncopyable {
	public:
		EventLoopThread();
		~EventLoopThread();
		EventLoop* startLoop();

	private:
		void threadFunc();
		EventLoop* loop_;
		bool exiting_;
		Thread thread_;
		MutexLock mutex_;
		Condition cond_;
};
