/*************************************************************************
    > File Name: LogFile.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Saturday, March 21, 2020 AM10:29:31 HKT
 ************************************************************************/
#pragma once
#include <memory>
#include <string>
#include "FileUtil.h"
#include "MutexLock.h"
#include "noncopyable.h"


using namespace std;

class LogFile : noncopyable {
	public:
		LogFile(const std::string& basename, int flushEveryN = 1024);
		~LogFile();

		void append(const char* logline, int len);
		void flush();
		bool roolFile();

	private:

		void append_unlocked(const char* logline, int len);
		const std::string basename_;
		const int flushEveryN_;

		int count_;
		std::unique_ptr<MutexLock> mutex_;
		std::unique_ptr<AppendFile> file_;

};

