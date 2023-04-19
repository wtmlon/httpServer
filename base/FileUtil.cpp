/*************************************************************************
    > File Name: FileUtil.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Friday, March 20, 2020 PM08:38:38 HKT
 ************************************************************************/
#include "FileUtil.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
using namespace std;

AppendFile::AppendFile(string filename) : fp_(fopen(filename.c_str(), "wb+")){
	setbuffer(fp_, buffer_, sizeof buffer_);
}

AppendFile::~AppendFile(){
	fclose(fp_);
}


size_t AppendFile::write(const char* logline, size_t len) {
    //fwrite_unlocked("liuting", 1, 7, fp_);
    //cout<<"write!!"<<logline<<" "<<len<<endl;
	return fwrite_unlocked(logline, 1, len, fp_);
}


void AppendFile::append(const char* logline, const size_t len) {
	size_t n = this->write(logline, len);
	size_t remain = len- n;
	while(remain >0) {
		size_t x = this->write(logline + n, remain);
		if(x == 0)
		{
			int err = ferror(fp_);
			if(err) fprintf(stderr, "AppendFile::append failed\n");
			break;
		}
		n+=x;
		remain = len - n;
	}
}
void AppendFile::flush() {
	fflush(fp_);
}
