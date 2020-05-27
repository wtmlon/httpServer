/*************************************************************************
    > File Name: Timer.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 PM12:03:10 HKT
 ************************************************************************/
#pragma once
#include <unistd.h>
#include <deque>
#include <memory>
#include <queue>
#include "HttpData.h"
#include "base/MutexLock.h"
#include "base/noncopyable.h"

#include<iostream>
using namespace std;
class HttpData;

class TimerNode{
	public:
		TimerNode(std::shared_ptr<HttpData> requestData, int timeout);
		~TimerNode();
		TimerNode(TimerNode &tn);
		void update(int timeout);
		bool isValid();
		void clearReq();
		void setDeleted() {
			deleted_ = true;
		}
		bool isDeleted() const {
			return deleted_;
		}
		size_t getExptime() const {
			return expiredTime_;
		}

	private:
		bool deleted_;
		size_t expiredTime_;
		std::shared_ptr<HttpData> SPHttpData;

};

struct TimerCmp {
	bool operator()(std::shared_ptr<TimerNode> &a,
			std::shared_ptr<TimerNode> &b) const {
		return a->getExptime() > b->getExptime();
	}
};


class TimerManager {
	public:
		TimerManager();
		~TimerManager();
		void addTimer(std::shared_ptr<HttpData> SPHttpData, int timeout);
		void handleExpiredEvent();

	private:
		typedef std::shared_ptr<TimerNode> SPTimerNode;
		std::priority_queue<SPTimerNode, std::deque<SPTimerNode>, TimerCmp>
			timerNodeQueue;
};
