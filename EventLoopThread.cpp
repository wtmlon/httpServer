/*************************************************************************
    > File Name: EventLoopThread.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 PM04:52:32 HKT
 ************************************************************************/
#include "EventLoopThread.h"
#include <functional>
using namespace std;

EventLoopThread::EventLoopThread()
	:loop_(NULL),
	exiting_(false),
	thread_(bind(&EventLoopThread::threadFunc, this), "EventLoopThread"),
	mutex_(),
	cond_(mutex_) {

	}

EventLoopThread::~EventLoopThread() {
	exiting_ = true;
	if(loop_ != NULL){
		loop_->quit();
		thread_.join();
	}
}

EventLoop* EventLoopThread::startLoop() {
	assert(!thread_.started());
	thread_.start();
	{
		MutexLockGuard lock(mutex_);
		while(loop_ == NULL) cond_.wait();

	}
	return loop_;
}

void EventLoopThread::threadFunc() {
	EventLoop loop;
	{
		MutexLockGuard lock(mutex_);
		loop_ = &loop;
		cond_.notify();
	}

	loop.loop();
	loop_ = NULL;
}

