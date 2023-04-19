/*************************************************************************
    > File Name: Channel.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Friday, March 20, 2020 PM06:02:59 HKT
 ************************************************************************/
#include "Channel.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <queue>
#include "Epoll.h"
#include "EventLoop.h"
#include "Util.h"
using namespace std;

Channel::Channel(EventLoop* loop)
	:loop_(loop), events_(0), lastEvents_(0), fd_(0) {

	}

Channel::Channel(EventLoop* loop, int fd)
	:loop_(loop), events_(0), lastEvents_(0), fd_(fd) {
	}

Channel::~Channel() {

}
/*
int Channel::getFd() {
	return fd_;
}
*/
void Channel::setFd(int fd){
	fd_ = fd;
}

void Channel::handleRead(){
	if(readHandler_)
		readHandler_();
}

void Channel::handleWrite(){
	if(writeHandler_)
		writeHandler_();
}
void Channel::handleConn(){
	if(connHandler_)
		connHandler_();
}

