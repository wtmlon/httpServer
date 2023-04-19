/*************************************************************************
    > File Name: EventLoopThreadPool.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 PM04:08:02 HKT
 ************************************************************************/
#pragma once
#include <memory>
#include <vector>
#include "EventLoopThread.h"
#include "base/Logging.h"
#include "base/noncopyable.h"

using namespace std;

class EventLoopThreadPool : noncopyable {

	public:
		EventLoopThreadPool(EventLoop* baseLoop, int numThreads );

		~EventLoopThreadPool() {
			LOG<<"~EVENTLOOPTHREADPOOL()";
		}
		void start();

		EventLoop* getNextLoop();

	private:
		EventLoop* baseLoop_;
		bool started_;
		int numThreads_;
		int next_;
		std::vector<std::shared_ptr<EventLoopThread>> threads_;
		std::vector<EventLoop*> loops_;
};

