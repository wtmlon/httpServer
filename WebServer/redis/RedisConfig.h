#ifndef REDISCONFIG_H
#define REDISCONFIG_H
#include <string>

class RedisConfig
{
	public:
		RedisConfig();
		std::string getRedisIP();
		int getRedisPort();
};
#endif
