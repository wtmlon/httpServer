/*************************************************************************
	> File Name: MyDB.h
	> Author: qinyu
	> Mail: qinyu.LT@gmail.com 
	> Created Time: 2023年04月17日 星期一 15时02分26秒
 ************************************************************************/
#ifndef _MYDB_H
#define _MYDB_H

//#include "../public.h"
#include "/usr/include/mysql/mysql.h"

class MyDB
{
public:
    MyDB();
    ~MyDB();
    bool initDB(string host,string user,string password,string db_name);
    bool execSQL(string sql);
    void showResult();
    list<string> getResult();
private:
    MYSQL *connection;
    MYSQL_RES *result;
    MYSQL_ROW row;
    list<string> res;
};

#endif
