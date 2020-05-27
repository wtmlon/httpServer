/*************************************************************************
    > File Name: TimerQueue.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Tuesday, March 24, 2020 PM08:52:43 HKT
 ************************************************************************/
#include "TimerQueue.h"
#include "../base/Logging.h"
#include "../EventLoop.h"
#include "Timer.h"
#include "TimerId.h"
#include <sys/timerfd.h>
#include <unistd.h>


using namespace std;


int createTimerfd()
{
	int timerfd = ::timerfd_create(CLOCK_MONOTONIC,
									TFD_NONBLOCK | TFD_CLOEXEC);
	if(timerfd < 0)
		LOG<<"FAILED in timerfd create";
	return timerfd;
}

struct timespec howMuchTimeFromNow(Timestamp when)
{
	int64_t microseconds = when.microSecondsSinceEpoch() 
		- Timestamp::now().microSecondsSinceEpoch();
	if(microSeconds < 100)
		microseconds = 100;
	struct timespec ts;
	ts.tv_sec = static_cast<time_t>(
			microseconds / Timestamp::kMicroSecondsPerSecond);
	ts.tv_nsec = static_cast<long>(
			(microseconds % Timestamp::kMicroSecondsPerSecond)*1000);
	return ts;
}

void readTimerfd(int timerfd, Timestamp now)
{
	uint64_t howmany;
	ssize_t n = ::read(timerfd, &howmany, sizeof howmany);
	LOG<<"TimerQUeue handleRead() read"<<howmany<<" at "<<now.toString();
	if(n != sizeof howmany)
		LOG<<"TIMER READs "<<n<<" bytes instead of 8";

}

void resetTimerfd(int timerfd, Timestamp expiration)
{
	struct itimerspec newValue;
	struct itimerspec oldValue;
	memZero(&newValue, sizeof newValue);
	memZero(&oldValue, sizeof oldValue);
	newValue.it_value = howMuchTimeFromNow(expiration);
	int ret = ::timerfd_settime(timerfd, 0, &newValue, &oldValue);
	if(ret)
		LOG<<"timerfd_settime()";
}

TimerQueue::TimerQueue(EventLoop* loop)
	:loop_(loop),
	timerfd_(createTimerfd()),
	timerfdChannel_(loop, timerfd_),
	timers_(),
	callingExpiredTimers_(false)
{
	timerfdChannel_.setReadHandle(std::bind(&TimerQueue::handelRead, this));
}

TimerQueue::~TimerQueue()
{
	timerfdChannel_.remove();
	::close(timerfd_);
	for(const Entry& timer : timers_)
	{
		delete timer.second;
	}
}

Timerfd TimerQueue::addTimer(TimerCallback cb,
							Timestamp when,
							double interval)
{
	Timer* timer = new Timer(std::move(cb), when, interval);
	loop_->runInLoop(
			std::bind(&TimerQueue::addTimerInLoop, this, timer));
	return timerId(timer, timer->sequence());
}

void 
