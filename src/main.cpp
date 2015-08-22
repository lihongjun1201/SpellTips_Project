/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 18 Aug 2015 07:30:40 PM PDT
 ************************************************************************/





#include <iostream>
#include "MyConfig.h"
#include "MyDictionary.h"

#include <muduo/net/TcpServer.h>
#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

#include <string>
#include <map>

using namespace muduo;
using namespace muduo::net;

typedef std::map<string,string> UserMap;
UserMap users;

/*
string getUser(const string &user)
{
    string result = "No such user";
    UserMap::iterator iter = users.find(user);
    if ( iter != users.end() ) {
        result = iter->second;
    }
    return result;
}



void onMessage(const TcpConnectionPtr &conn,
                Buffer *buf,
                Timestamp receiveTime)
{
    const char *crlf = buf->findCRLF();
    if (crlf) {
        string user(buf->peek(),crlf);
        conn->send(getUser(user) + "\r\n");
        buf->retrieveUntil(crlf + 2);
        conn->shutdown();
    }
}
*/

/*
std::pair<std::string,int> getWordCount(MyDictionary *ptr_dic,string seach_word) {
    std::pair<std::string,int> result = ( ptr_dic->find(seach_word))->second;
    return result;
}
*/


int getDistance(string a,string b);

void onMessage(const TcpConnectionPtr &conn,
                Buffer *buf,
                Timestamp receiveTime)
{
    const char *crlf = buf->findCRLF();
    if (crlf) {
        string user(buf->peek(),crlf);
        conn->send(getUser(user) + "\r\n");
        buf->retrieveUntil(crlf + 2);
        conn->shutdown();
    }
}


int main(void) {
    
    LOG_INFO << "USE MUDUO LOG";

    //初始化配置文件
    std::string config_file_path = "../conf/config.txt";
    MyConfig config(config_file_path);
    bool init_success = config.init();
    if (init_success)
        config.show();

    std::map<std::string,std::string> &my_conf_map = config.get_map();

    //获取字典
    std::string dict_path = my_conf_map["my_dict_path"];
    MyDictionary *pMydict = MyDictionary::createInstance(dict_path.c_str());


    //测试网络库
    
    users["allen"] = "handsome and clever";

    EventLoop loop;

    TcpServer server(&loop,InetAddress(1079),"Finger");
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();

    
    



    return 0;
}
