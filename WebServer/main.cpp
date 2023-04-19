/*************************************************************************
    > File Name: main.cpp
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Thursday, March 19, 2020 AM11:34:07 HKT
 ************************************************************************/
#include <getopt.h>
#include <string>
#include "EventLoop.h"
#include "Server.h"
#include "base/Logging.h"
#include "Mysql/model.h"
#include<iostream>
using namespace std;
using http_model::model_init;

int main(int argc, char* argv[]){
	int threadNum = 4;
	int port = 8091;
	std::string logPath = "./WebServer.log";

	int opt;
	const char* str = "t:l::p:";
	while((opt = getopt(argc, argv, str)) != -1){
		switch(opt) {
			case 't':
                cout<<"open: "<<optarg<<" threads"<<endl;
				threadNum = atoi(optarg);
				break;
			case 'l':
				logPath = optarg;
				if( logPath.size() < 2 || optarg[0] != '/'){
					cout<<"logPath should start with \"/\"\n";
					abort();
				}
				break;
			case 'p':
				cout<<"open in: "<<optarg<<" port"<<endl;
				port = atoi(optarg);
				break;
			default:
				break;
		}
	}
	Logger::setLogFileName(logPath);

#ifndef _PTHREADS
	LOG << "_PTHREADS is not defined";
#endif
	EventLoop mainLoop;
	Server HttpServer(&mainLoop, threadNum, port);//init

	//model init
    	const SqlConnInfo conInfo={10,"127.0.0.1","3306","wtmlon","12345"};
	http_model::model_init(conInfo, "yourdb");

	HttpServer.start();//set event and callback function and add to loop
	mainLoop.loop();//start accept
	return 0;
}

