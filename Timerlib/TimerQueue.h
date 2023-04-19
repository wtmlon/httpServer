/*************************************************************************
    > File Name: TimerQueue.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Monday, March 23, 2020 PM07:26:10 HKT
 ************************************************************************/
#pragma once
#include <set>
#include <vector>
#include "../base/Mutex.h"
#include "../base/Timestamp.h"
#include "../Callbacks.h"
#include "../Channel.h"
using namespace std;

class EventLoop;
class Timer;
class TimerId;

class TimerQueue : noncopyable {

	public:
		explicit TimerQueue(EventLoop* loop);
		~TimerQueue();

		TimerId addTimer(TimerCallback cb, Timestamp when, double interval);

		void cancel(TimerId timerId);

	private:
		typedef std::pair<Timestamp, Timer*> Entry;
		typedef std::set<Entry> TimerList;
		typedef std::pair<Timer*, int64_t> ActiveTimer;
		typedef std::set<ActiveTimer> ActiveTimerSet;

		void addTimerInLoop(Timer* timer);
		void cancelInLoop(TimerId timerId);
		//call when timerfd
		void handleRead();
		std::vector<Entry> getExpired(Timestamp now);
		void reset(const std::vector<Entry>& expired, Timestamp now);

		bool insert(Timer* timer);

		EventLoop* loop_;
		const int timerfd_;
		Channel timerfdChannel_;

		TimerList timers_;
		ActiveTimerSet activeTimers_;

		bool callingExpiredTimers_;
		ActiveTimerSet cancelingTimers_;

};

