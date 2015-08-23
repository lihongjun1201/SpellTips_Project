/*************************************************************************
	> File Name: MyServer.h
	> Author: 
	> Mail: 
	> Created Time: Sat 22 Aug 2015 11:10:31 PM PDT
 ************************************************************************/

#ifndef _MYSERVER_H
#define _MYSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

#include <MyDictionary.h>

#include <iostream>
#include <string>
#include <vector>

using namespace muduo::net;

class SpellCheckServer {
 public:
    //服务器构造函数
    SpellCheckServer(EventLoop *loop,
                     const InetAddress &listen_addr,
                     MyDictionary *pDict);
    
    void init();

    void start();


    std::vector<std::string>& searchDictionary(muduo::string &search_word);
    

 private:
    void onConnection(const TcpConnectionPtr &conn);

    void onMessage(const TcpConnectionPtr &conn,
                   muduo::net::Buffer *buf,
                   muduo::Timestamp time);

 private:
    TcpServer mserver_;
    MyDictionary * pMydictionary_;
    std::vector<std::string> msearch_result_; //查询结果
    
};











#endif
