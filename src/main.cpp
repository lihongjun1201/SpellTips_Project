/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 18 Aug 2015 07:30:40 PM PDT
 ************************************************************************/





#include <iostream>
#include "MyConfig.h"
#include "MyDictionary.h"
#include "MyServer.h"

#include <muduo/net/TcpServer.h>
#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

#include <string>
#include <map>

using namespace muduo;
using namespace muduo::net;


void print() {
    std:: cout << "更新缓存" << "\n";
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
    LOG_INFO << "PID = " << getpid();

    muduo::net::EventLoop loop;

    //定时器
    //loop.runEvery(5,print);

    InetAddress listen_addr(6917); //服务器端口号
    SpellCheckServer server(&loop,listen_addr,pMydict); 
    
    server.start();
    loop.loop();


    return 0;
}
