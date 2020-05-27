/*************************************************************************
    > File Name: AsyncLogging.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Saturday, March 21, 2020 AM10:51:00 HKT
 ************************************************************************/
#include <functional>
#include <string>
#include <vector>
#include "CountDownLatch.h"
#include "LogStream.h"
#include "MutexLock.h"
#include "Thread.h"
#include "noncopyable.h"

using namespace std;

class AsyncLogging : noncopyable {

	public:
		AsyncLogging(const string& basename, int flushInterval = 2);
		~AsyncLogging() {
			if(running_) stop();
		}

		void append(const char* logline, int len);

		void start() {
			running_ = true;
			thread_.start();
			latch_.wait();
		}

		void stop() {
			running_ = false;
			cond_.notify();
			thread_.join();
		}

	private:
		void threadFunc();
		typedef FixedBuffer<kLargeBuffer> Buffer;
		typedef vector<shared_ptr<Buffer>> BufferVector;
		typedef shared_ptr<Buffer> BufferPtr;
		const int flushInterval_;
		bool running_;
		string basename_;
		Thread thread_;
		MutexLock mutex_;
		Condition cond_;
		BufferPtr currentBuffer_;
		BufferPtr nextBuffer_;
		BufferVector buffers_;
		CountDownLatch latch_;

};
