/*************************************************************************
    > File Name: MutexLock.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 PM05:28:17 HKT
 ************************************************************************/
#pragma once
#include <pthread.h>
#include <cstdio>
#include "noncopyable.h"
using namespace std;

class MutexLock : noncopyable {
	public:
		MutexLock() {
			pthread_mutex_init(&mutex, NULL);
		}
		~MutexLock() {
			pthread_mutex_lock(&mutex);//ensure nobody is using it
			pthread_mutex_destroy(&mutex);

		}

		void lock() {
			pthread_mutex_lock(&mutex);
		}
		void unlock() {
			pthread_mutex_unlock(&mutex);
		}
		pthread_mutex_t* get() {
			return &mutex;
		}
	private:
		pthread_mutex_t mutex;

	private:
		friend class Condition;
};

class MutexLockGuard : noncopyable {//construct is initialize principle
	public:
		explicit MutexLockGuard(MutexLock &_mutex) : mutex(_mutex) {
			mutex.lock();
		}
		~MutexLockGuard() {
			mutex.unlock();
		}
	private:
		MutexLock &mutex;
};

