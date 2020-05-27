/*************************************************************************
    > File Name: FileUtil.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Friday, March 20, 2020 PM08:34:35 HKT
 ************************************************************************/
#pragma once

#include <string>
#include "noncopyable.h"
using namespace std;

class AppendFile : noncopyable {

	public:
		explicit AppendFile(std::string filename);
		~AppendFile();

		void append(const char* logline, const size_t len);
		void flush();
	private:

		size_t write(const char *logline, size_t len);
		FILE *fp_;
		char buffer_[64 * 1024];//64k
};

