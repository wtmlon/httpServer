/*************************************************************************
	> File Name: sqlConnPool.cpp
	> Author: wtmlon
	> Mail: wtmlon@foxmail.com 
	> Created Time: 2023年04月17日 星期一 15时02分26秒
 ************************************************************************/
#include "sqlConnPool.h"
#include <stdexcept>
#include <cppconn/config.h>
#include <cppconn/connection.h>

using namespace std;
using namespace sql;

int main()
{
    const SqlConnInfo conInfo={10,"127.0.0.1","3306","wtmlon","12345"};

    CSqlConnPool* pool = CSqlConnPool::getInstance();
    pool->Init(conInfo);
    pool->SetDBName("yourdb");

    Connection *conn;
    Statement *state;
    ResultSet *result;
    //MYSQL *result;

    conn=pool->GetConnection();
    state = conn->createStatement();
    state->execute("use yourdb");
    result = state->executeQuery("select *from user");
    size_t i = result->rowsCount();
    cout<<i<<endl;
    cout<<"password "<<result->findColumn("password")<<endl;
    while(result->next())
    {
        //cout<<result->getCursorName()<<" ";
        string name=result->getString("user_id");
        string password=result->getString("password");
        int i=result->getInt("salt");
        int j=result->getInt("age");
        cout<<result->getRow()<<":"<<name<<" "<<password<<" "<<i<<" "<<j<<endl;
    }
    const CSqlConnPool* pool1 = CSqlConnPool::getInstance();
    if(pool1 == pool)
	cout<<"yes!"<<endl;
    else
	cout<<"NOOOO!!"<<endl;

    //conn->setAutoCommit(0);
    //cout<<"DataBae model:"<<conn->getAutoCommit()<<endl;
    //cout<<"main :: conn "<<conn<<endl;
 
    delete result;
    delete state;
    delete conn;

    return 0;
}

