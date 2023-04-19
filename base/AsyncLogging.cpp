/*************************************************************************
    > File Name: AsyncLogging.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Saturday, March 21, 2020 AM11:11:36 HKT
 ************************************************************************/
#include "AsyncLogging.h"
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <functional>
#include <iostream>
#include "LogFile.h"

using namespace std;

AsyncLogging::AsyncLogging(const string &logFileName_, int flushInterval)
	: flushInterval_(flushInterval),
	running_(false),
	basename_(logFileName_),
	thread_(std::bind(&AsyncLogging::threadFunc, this), "Logging"),
	mutex_(),
	cond_(mutex_),
	currentBuffer_(new Buffer),
	nextBuffer_(new Buffer),
	buffers_(),
	latch_(1) {
		assert(logFileName_.size() > 1);
		currentBuffer_->bzero();
		nextBuffer_->bzero();
		buffers_.reserve(16);//16Buffer space pre-set
	}

void AsyncLogging::append(const char* logline, int len) {
	MutexLockGuard lock(mutex_);
	if(currentBuffer_->avail() > len)
		currentBuffer_->append(logline, len);
	else {
		buffers_.push_back(std::move(currentBuffer_));
		//currentBuffer_->reset();//???! push_back is a pointer, can operate like this?absolutely not! shit man
		if(nextBuffer_)
			currentBuffer_ = std::move(nextBuffer_);
		else
			currentBuffer_.reset(new Buffer);
		currentBuffer_->append(logline, len);
		cond_.notify();//?
	}
}

void AsyncLogging::threadFunc() {
	assert(running_ == true);
	latch_.countDown();
	LogFile output(basename_);
	BufferPtr newBuffer1(new Buffer);
	BufferPtr newBuffer2(new Buffer);
	newBuffer1->bzero();
	newBuffer2->bzero();
	
	BufferVector buffersToWrite;
	buffersToWrite.reserve(16);
	while(running_){
		assert(newBuffer1 && newBuffer1->length() == 0);
		assert(newBuffer2 && newBuffer2->length() == 0);
		assert(buffersToWrite.empty());//???

		{
			MutexLockGuard lock(mutex_);
			if(buffers_.empty())
			{
				cond_.waitForSeconds(flushInterval_);

			}
			buffers_.push_back(std::move(currentBuffer_));
			//currentBuffer_->reset();

			currentBuffer_ = std::move(newBuffer1);
			buffersToWrite.swap(buffers_);
			if(!nextBuffer_)
				nextBuffer_ = std::move(newBuffer2);


		}
		assert(!buffersToWrite.empty());

		if(buffersToWrite.size() > 25)
		{
            cout<<"Yes"<<endl;
			buffersToWrite.erase(buffersToWrite.begin() + 2, buffersToWrite.end());
		}

		for(size_t i = 0; i<buffersToWrite.size(); ++i){
            //cout<<"LOOK THERE!!!"<<buffersToWrite[i]->data()<<" "<<buffersToWrite[i]->length()<<"  IS END!!!"<<endl;
			output.append(buffersToWrite[i]->data(), buffersToWrite[i]->length());
		}

		if(buffersToWrite.size() > 2)
			buffersToWrite.resize(2);

		if(!newBuffer1){
			assert(!buffersToWrite.empty());
			newBuffer1 = buffersToWrite.back();
			buffersToWrite.pop_back();
			newBuffer1->reset();
		}
		if(!newBuffer2){
			assert(!buffersToWrite.empty());
			newBuffer2 = buffersToWrite.back();
			buffersToWrite.pop_back();
			newBuffer2->reset();
		}

		buffersToWrite.clear();
		output.flush();

	}
	output.flush();
}
