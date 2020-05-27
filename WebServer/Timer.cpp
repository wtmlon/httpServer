/*************************************************************************
    > File Name: Timer.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 PM12:16:12 HKT
 ************************************************************************/
#include "Timer.h"
#include <sys/time.h>
#include <unistd.h>
#include <queue>
#include<iostream>
using namespace std;

TimerNode::TimerNode(std::shared_ptr<HttpData> requestData, int timeout)
	:deleted_(false), SPHttpData(requestData) {
	struct timeval now;
	gettimeofday(&now, NULL);
	expiredTime_ = 
		(((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout; // why % 10000
}

TimerNode::~TimerNode() {
	if(SPHttpData) SPHttpData->handleClose();
}

TimerNode::TimerNode(TimerNode& tn)
	: SPHttpData(tn.SPHttpData), expiredTime_(0){

	}


void TimerNode::update(int timeout) {//reset timeout time
	struct timeval now;
	gettimeofday(&now, NULL);
	expiredTime_ = 
		(((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool TimerNode::isValid() {//whether timeout or not
	struct timeval now;
	gettimeofday(&now, NULL);
	size_t temp = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));
	if(temp <expiredTime_)
		return true;
	else{
		this->setDeleted();
		return false;
	}
}

void TimerNode::clearReq()
{
	SPHttpData.reset();
	this->setDeleted();
}

TimerManager::TimerManager() {

}

TimerManager::~TimerManager() {

}

void TimerManager::addTimer(std::shared_ptr<HttpData> SPHttpData, int timeout) {
	SPTimerNode new_node(new TimerNode(SPHttpData, timeout));
	timerNodeQueue.push(new_node);
	SPHttpData->linkTimer(new_node);
}

void TimerManager::handleExpiredEvent(){//thread safe is it? 
	while(!timerNodeQueue.empty()){
		SPTimerNode temp = timerNodeQueue.top();
		if(temp->isDeleted())
			timerNodeQueue.pop();
		else if((temp->isValid() == false))
			timerNodeQueue.pop();
		else 
			break;
	}

}
