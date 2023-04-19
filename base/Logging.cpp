/*************************************************************************
    > File Name: Logging.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Saturday, March 21, 2020 PM01:09:57 HKT
 ************************************************************************/
#include "Logging.h"
#include "CurrentThread.h"
#include "Thread.h"
#include "AsyncLogging.h"
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include<iostream>
using namespace std;

static pthread_once_t once_control_ = PTHREAD_ONCE_INIT;
static AsyncLogging * AsyncLogger_;

string Logger::logFileName_ = "./WebServer.log";

void once_init(){
	AsyncLogger_ = new AsyncLogging(Logger::getLogFileName());
	AsyncLogger_->start();
}

void output(const char* msg, int len)
{
	//cout<<msg<<endl;
	pthread_once(&once_control_, once_init);
	AsyncLogger_->append(msg, len);
}

Logger::Impl::Impl(const char* fileName, int line)
	:stream_(),
	line_(line),
	basename_(fileName)
{
	formatTime();
}

void Logger::Impl::formatTime()
{
	struct timeval tv;
	time_t time;
	char str_t[26] = {0};
	gettimeofday(&tv, NULL);
	time = tv.tv_sec;
	struct tm* p_time = localtime(&time);
	strftime(str_t, 26, "%Y-%m-%d %H:%M:%S\n", p_time);
	stream_ << str_t;
	//cout<<"stream_ << str_t"<<endl;

}

Logger::Logger(const char* fileName, int line)
:impl_(fileName, line)
{

}

Logger::~Logger()
{
	impl_.stream_ << " -- " << impl_.basename_ << " : " << impl_.line_ << '\n';
	const LogStream::Buffer& buf(stream().buffer());
    //cout<<buf.data()<<endl;
	output(buf.data(), buf.length());
    
}
