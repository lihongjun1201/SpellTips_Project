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

#include <iostream>

using namespace muduo::net;

class SpellCheckServer {
 public:
    //服务器构造函数
    SpellCheckServer(EventLoop *loop,  const InetAddress &listen_addr);
    
    void start();

 private:
    void onConnection(const TcpConnectionPtr &conn);

    void onMessage(const TcpConnectionPtr &conn,
                   muduo::net::Buffer *buf,
                   muduo::Timestamp time);

 private:
    TcpServer mserver_;


};

#if 1
class Printer: boost::noncopyable {
 public:
    Printer(muduo::net::EventLoop *loop):loop_(loop),
                                         count_(0)
    {
        loop_->runEvery(1,boost::bind(&Printer::print,this));
    }

    ~Printer() {
        std::cout << "Final count is" << count_ << "\n";
    }

    void print() {
        if (count_ < 5) {
            std::cout << count_ << "\n";
            ++count_;

            loop_->runEvery(1,boost::bind(&Printer::print,this));

        } else {
            loop_->quit();
        }
    }

 private:
    muduo::net::EventLoop *loop_;
    int count_;

};
#endif









#endif
