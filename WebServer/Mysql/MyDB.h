/*************************************************************************
	> File Name: MyDB.h
	> Author: wtmlon
	> Mail: wtmlon@foxmail.com 
	> Created Time: 2023年04月17日 星期一 15时02分26秒
 ************************************************************************/
#ifndef _MYDB_H
#define _MYDB_H

//#include "../public.h"
#include "/usr/include/mysql/mysql.h"
#include <string>
#include <list>

class MyDB
{
public:
    MyDB();
    ~MyDB();
    bool initDB(std::string host,std::string user,std::string password,std::string db_name);
    bool execSQL(std::string sql);
    void showResult();
    std::list<std::string> getResult();
private:
    MYSQL *connection;
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::list<std::string> res;
};

#endif
