/*************************************************************************
    > File Name: Epoll.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Friday, March 20, 2020 PM01:37:54 HKT
 ************************************************************************/
#pragma once
#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Channel.h"
#include "HttpData.h"
#include "Timer.h"
using namespace std;

class Epoll {
	public:
		Epoll();
		~Epoll();
		void epoll_add(SP_Channel request, int timeout);
		void epoll_mod(SP_Channel request, int timeout);
		void epoll_del(SP_Channel request);
		std::vector<SP_Channel> poll();
		std::vector<SP_Channel> getEventsRequest(int events_num);
		void add_timer(SP_Channel request_data, int timeout);
		int getEpollFd() const {
			return epollFd_;
		}
		void handleExpired();

	private:
		static const int MAXFDS = 100000;
		int epollFd_;
		std::vector<epoll_event> events_;
		SP_Channel fd2chan_[MAXFDS];
		std::shared_ptr<HttpData> fd2http_[MAXFDS];
		TimerManager timerManager_;
};
