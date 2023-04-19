/*************************************************************************
    > File Name: Channel.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Friday, March 20, 2020 PM04:44:36 HKT
 ************************************************************************/
#pragma once
#include <sys/epoll.h>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "Timer.h"
using namespace std;

class EventLoop;
class HttpData;

class Channel {
	private:
		typedef std::function<void()> CallBack;
		EventLoop * loop_;
		int fd_;
		__uint32_t events_;
		__uint32_t revents_;
		__uint32_t lastEvents_;

		std::weak_ptr<HttpData> holder_;

	private:
		/*
		 * parse_URI??
		 */
		
		CallBack readHandler_;
		CallBack writeHandler_;
		CallBack errorHandler_;
		CallBack connHandler_;
		
	public:
		Channel(EventLoop* loop);
		Channel(EventLoop* loop, int fd);
		~Channel();
		int getFd() const {
			return fd_;
		}
		void setFd(int fd);

		void setHolder(std::shared_ptr<HttpData> holder) {
			holder_ = holder;
		}
		std::shared_ptr<HttpData> getHolder() {
			std::shared_ptr<HttpData> ret(holder_.lock());
			return ret;
		}

		void setReadHandler(CallBack &&readHandler) {
			readHandler_ = readHandler;
		}

		void setWriteHandler(CallBack &&writeHandler) {
			writeHandler_ = writeHandler;
		}
		void setErrorHandler(CallBack &&errorHandler) {
			errorHandler_ = errorHandler;
		}

		void setConnHandler(CallBack &&connHandler) {
			connHandler_ = connHandler;
		}

		void handleEvents() {
			events_ = 0;
			if((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
			{
				events_ = 0;
				return;
			}
			if(revents_ & EPOLLERR){
				if(errorHandler_) errorHandler_();
				events_ = 0;
				return;
			}
			if(revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
				handleRead();
			}
			if(revents_ & (EPOLLOUT)){
				handleWrite();

			}
			handleConn();//handle once process once
		}

		void handleRead();
		void handleWrite();
		void handleError(int fd, int err_num, std::string short_msg);
		void handleConn();

		void setRevents(__int32_t ev) {
			revents_ = ev;
		}

		void setEvents(__uint32_t ev) {
			events_ = ev;
		}

		__uint32_t& getEvents(){
			return events_;
		}

		bool EqualAndUpdateLastEvents() {
			bool ret = (lastEvents_ == events_);
			lastEvents_ = events_;
			return ret;
		}

		__uint32_t getLastEvents() const {
			return lastEvents_;
		}


		
};

typedef std::shared_ptr<Channel> SP_Channel;
