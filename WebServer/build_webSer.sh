 g++ -std=c++11 -g -Wall -D_PTHREADS -o WebServer Server.cpp Timer.cpp Epoll.cpp Channel.cpp EventLoopThread.cpp EventLoopThreadPool.cpp HttpData.cpp Util.cpp EventLoop.cpp base/CountDownLatch.cpp base/LogStream.cpp base/LogFile.cpp base/Thread.cpp base/Logging.cpp base/AsyncLogging.cpp base/FileUtil.cpp main.cpp  -lpthread
