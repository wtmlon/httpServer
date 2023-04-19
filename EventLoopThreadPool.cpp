/*************************************************************************
    > File Name: EventLoopThreadPool.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 PM04:17:45 HKT
 ************************************************************************/
#include "EventLoopThreadPool.h"

using namespace std;

EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, int numThreads)
	:baseLoop_(baseLoop), started_(false), numThreads_(numThreads), next_(0) {
		if(numThreads_ <= 0){
			LOG << "numThreads <= 0";
			abort();
		}
	}

void EventLoopThreadPool::start() {
	baseLoop_->assertInLoopThread();
	started_ = true;
	for( int i = 0; i < numThreads_; ++i)
	{
		std::shared_ptr<EventLoopThread> t(new EventLoopThread());
		threads_.push_back(t);
		loops_.push_back(t->startLoop());
	}
}

EventLoop* EventLoopThreadPool::getNextLoop() {
	baseLoop_->assertInLoopThread();
	assert(started_);
	EventLoop*  temp = baseLoop_; // use baseloop if dont have threadpool
	if(!loops_.empty()) {
		temp = loops_[next_];
		next_ = (next_ + 1) % numThreads_;
	}//Rounds Robin
	return temp;

}
