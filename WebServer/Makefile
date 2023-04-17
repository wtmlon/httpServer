build:
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o Server.o Server.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o Timer.o Timer.cpp
	#g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o ThreadPool.o ThreadPool.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o Epoll.o Epoll.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o Channel.o Channel.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o EventLoopThread.o EventLoopThread.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o EventLoopThreadPool.o EventLoopThreadPool.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o HttpData.o HttpData.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o Util.o Util.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o EventLoop.o EventLoop.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o base/CountDownLatch.o base/CountDownLatch.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o base/LogStream.o base/LogStream.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o base/LogFile.o base/LogFile.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o base/Thread.o base/Thread.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o base/Logging.o base/Logging.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o base/AsyncLogging.o base/AsyncLogging.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o base/FileUtil.o base/FileUtil.cpp
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o Main.o main.cpp
	#g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o base/tests/LoggingTest.o base/tests/LoggingTest.cpp
	#g++ -std=c++11 -g -Wall -O3 -D_PTHREADS   -c -o tests/HTTPClient.o tests/HTTPClient.cpp
Mysql:
	g++ -std=c++11 -g -Wall -O3 -c -o Mysql/MyDB.o Mysql/MyDB.cpp
	g++ -std=c++11 -g -Wall -O3 -c -o Mysql/sqlConnPool.o Mysql/sqlConnPool.cpp
.PHONY: Mysql

WebServer :
	#g++ -std=c++11 -g -Wall -O3 -D_PTHREADS -o WebServer Server.o Timer.o ThreadPool.o Epoll.o Channel.o EventLoopThread.o EventLoopThreadPool.o HttpData.o Util.o EventLoop.o base/CountDownLatch.o base/LogStream.o base/LogFile.o base/Thread.o base/Logging.o base/AsyncLogging.o base/FileUtil.o Main.o  -lpthread
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS -o WebServer Server.o Timer.o Epoll.o Channel.o EventLoopThread.o EventLoopThreadPool.o HttpData.o Util.o EventLoop.o base/CountDownLatch.o base/LogStream.o base/LogFile.o base/Thread.o base/Logging.o base/AsyncLogging.o base/FileUtil.o Main.o  -lpthread


LoggingTest :
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS -o LoggingTest Server.o Timer.o Epoll.o Channel.o EventLoopThread.o EventLoopThreadPool.o HttpData.o Util.o EventLoop.o base/CountDownLatch.o base/LogStream.o base/LogFile.o base/Thread.o base/Logging.o base/AsyncLogging.o base/FileUtil.o base/tests/LoggingTest.o  -lpthread
	#g++ -std=c++11 -g -Wall -O3 -D_PTHREADS -o LoggingTest Server.o Timer.o ThreadPool.o Epoll.o Channel.o EventLoopThread.o EventLoopThreadPool.o HttpData.o Util.o EventLoop.o base/CountDownLatch.o base/LogStream.o base/LogFile.o base/Thread.o base/Logging.o base/AsyncLogging.o base/FileUtil.o base/tests/LoggingTest.o  -lpthread


HTTPClient :
	g++ -std=c++11 -g -Wall -O3 -D_PTHREADS -o HTTPClient Server.o Timer.o Epoll.o Channel.o EventLoopThread.o EventLoopThreadPool.o HttpData.o Util.o EventLoop.o base/CountDownLatch.o base/LogStream.o base/LogFile.o base/Thread.o base/Logging.o base/AsyncLogging.o base/FileUtil.o tests/HTTPClient.o  -lpthread
	#g++ -std=c++11 -g -Wall -O3 -D_PTHREADS -o HTTPClient Server.o Timer.o ThreadPool.o Epoll.o Channel.o EventLoopThread.o EventLoopThreadPool.o HttpData.o Util.o EventLoop.o base/CountDownLatch.o base/LogStream.o base/LogFile.o base/Thread.o base/Logging.o base/AsyncLogging.o base/FileUtil.o tests/HTTPClient.o  -lpthread

all: build WebServer
.PHONY: WebServer
