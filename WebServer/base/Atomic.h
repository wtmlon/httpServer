/*************************************************************************
    > File Name: Atomic.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Monday, March 23, 2020 PM05:41:39 HKT
 ************************************************************************/
#pragma once
#include "noncopyable.h"
#include <stdint.h>
using namespace std;

template<typename T>
class AtomicIntegerT : noncopyable {

	public:
		AtomicIntegerT()
			:value_(0){
				
			}
		T get() 
		{
			return __sync_val_compare_and_swap(&value_, 0, 0);//if value == 0: value = 0; return value;
		}

		T getAndAdd(T x){
			return __sync_fetch_and_add(&value_, x);//return pre-modify value 
		}

		T addAndGet(T x)
		{
			return getAndAdd(x) + x;
		}
		
		T incrementAndGet()
		{
			return addAndGet(1);
		}
		T decrementAndGet()
		{
			return addAndGet(-1);
		}

		void add(T x)
		{
			getAndAdd(x);
		}

		void increment()
		{
			incrementAndGet();
		}

		void decrement()
		{
			decrementAndGet();
		}

		T getAndSet(T newValue)
		{
			return __sync_lock_test_and_set(&value_, newValue);
		}

	private:
		volatile value_;

};

typedef AtomicIntegerT<int32_t> AtomicInt32;
typedef AtomicIntegerT<int64_t> AtomicInt64;


