#include "RedisTools.h"
#include "RedisConfig.h"
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;

RedisTool::RedisTool()
{
	m_redis = NULL;
	init();
}

RedisTool::~RedisTool()
{
	if(m_redis != NULL)
	{
		redisFree(m_redis);
		std::cout<<"~RedisTool :: free connection "<<std::endl;
	}

}


void RedisTool::init()
{
	struct timeval timeout = {1, 500000};
	char ip[255];
	strcpy(ip, m_config.getRedisIP().c_str());
	std::cout<<"init : ip = "<<ip<<std::endl;

	m_redis = redisConnectWithTimeout(ip, m_config.getRedisPort(), timeout);

	if(m_redis->err){
		std::cout<<"RedisTool : Connection error: "<< m_redis->errstr<<std::endl;
	}else
	{
		cout<<"init redis tool success "<<endl;
		cout << "#define REDIS_REPLY_STRING 1"<< endl;
        cout << "#define REDIS_REPLY_ARRAY 2"<< endl;
        cout << "#define REDIS_REPLY_INTEGER 3"<< endl;
        cout << "#define REDIS_REPLY_NIL 4"<< endl;
        cout << "#define REDIS_REPLY_STATUS 5"<< endl;
        cout << "#define REDIS_REPLY_ERROR 6"<< endl;

	}
}

int RedisTool::setString(string key, string value)
{
	if(m_redis == NULL || m_redis->err)
	{
		cout<<"redis init error"<<endl;
		init();
		return -1;
	}
	redisReply *reply;
	reply = (redisReply *)redisCommand(m_redis, "SET %s %s", key.c_str(), value.c_str());
	cout<<"set string type = "<<reply->type<<endl;
	int result = 0;
	if(reply == NULL)
	{
		redisFree(m_redis);
		m_redis = NULL;
		result = -1;
		cout<<"set string fail : reply->str = NULL"<<endl;
		return -1;
	}
	else if(strcmp(reply->str, "OK")==0)
	{
		result = 1;
	}
	else
	{
		result = -1;
		cout<<"set string fail : "<<reply->str<<endl;
	}
	freeReplyObject(reply);//free when an reply off

	return result;
}


string RedisTool::getString(string key)
{
	if(m_redis == NULL || m_redis->err)
	{
		cout<<"Redis init error"<<endl;
		init();
		return NULL;
	}
	redisReply *reply;
	reply = (redisReply *)redisCommand(m_redis, "GET %s", key.c_str());
	cout<<"get string type = "<<reply->type<<endl;

	if(reply == NULL)
	{
		redisFree(m_redis);
		m_redis = NULL;
		cout<<"error getString: reply = NULL maybe redis server is down"<<endl;
		return NULL;
	}
	else if(reply->len <= 0)
	{
		freeReplyObject(reply);
		return NULL;
	}
	else
	{
		stringstream ss;
		ss << reply->str;
		freeReplyObject(reply);
		return ss.str();
	}
	
}

int RedisTool::setList(string key, vector<int> value)
{
	if(m_redis == NULL || m_redis->err)
	{
		cout<<"redis init error!"<<endl;
		init();
		return -1;
	}

	redisReply *reply;
	int valueSize = value.size();
	int result = 0;
	for(int i = 0; i < valueSize; i++)
	{
		reply = (redisReply *)redisCommand(m_redis, "RPUSH %s %d", key.c_str(), value.at(i));
		cout<<"set List type"<<reply->type<<' ';
		int old = reply->integer;//?
		if(reply == NULL)
		{
			redisFree(m_redis);
			m_redis = NULL;
			result = -1;
			cout<<"set list fail str == NULL"<<endl;
			return -1;
		}
		else if(reply->integer == old++)
		{
			result = 1;
			cout<<"rpush list ok"<<endl;
			continue;
		}
		else
		{
			result = -1;
			cout<<"fail in integer = "<<reply->integer<<endl;
			return -1;
		}
	}
	freeReplyObject(reply);
	cout<<"set list success"<<endl;
	return result;

}


vector<int> RedisTool::getList(string key)
{
	if(m_redis == NULL || m_redis->err)
	{
		cout<<"Redis init error"<<endl;
		init();
		return vector<int>{

		};
	}

	redisReply *reply;
	reply = (redisReply *)redisCommand(m_redis, "LLEN %s", key.c_str());
	int valueSize = reply->integer;
	reply = (redisReply* )redisCommand(m_redis, "LRANGE %s %d %d", key.c_str(), 0, valueSize - 1);
	cout<<"get List type "<<reply->type<<endl;
	cout<<"get list size "<<reply->elements<<endl;

	redisReply** replyVector = reply->element;
	vector<int> result;
	for(int i = 0; i < valueSize; i++)
	{
		string temp = (*replyVector)->str;
		int a = atoi(temp.c_str());
		result.push_back(a);
		replyVector++;
	}
	cout<<"result size: "<<result.size()<<endl;
	return result;

}
