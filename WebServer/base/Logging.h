/*************************************************************************
    > File Name: Logging.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Saturday, March 21, 2020 PM01:03:27 HKT
 ************************************************************************/
#pragma once
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "LogStream.h"
using namespace std;

class AsyncLogging;

class Logger {

	public:
		Logger(const char* fileName, int line);
		~Logger();
		LogStream& stream() {
			return impl_.stream_;
		}

		static void setLogFileName(string& fileName){
			logFileName_ = fileName;
		}

		static string getLogFileName() {
			return logFileName_;
		}

	private:
		class Impl {
			public:
				Impl(const char* fileName, int line);
				void formatTime();

				LogStream stream_;
				int line_;
				string basename_;
		};
		Impl impl_;
		static string logFileName_;
};

#define LOG Logger(__FILE__, __LINE__).stream()
