/*************************************************************************
	> File Name: MyServer.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 22 Aug 2015 08:52:17 AM PDT
 ************************************************************************/

#include "MyServer.h"

#include <muduo/base/Logging.h>
#include <boost/bind.hpp>

using namespace muduo;
using namespace muduo::net;

//服务器构造函数
SpellCheckServer::SpellCheckServer(EventLoop *loop,
                                  const InetAddress &listen_addr)
 : mserver_(loop,listen_addr,"SpellCheckServer")
 {
    mserver_.setConnectionCallback(
        boost::bind(&SpellCheckServer::onConnection,this,_1));
   
    mserver_.setMessageCallback(
        boost::bind(&SpellCheckServer::onMessage,this,_1,_2,_3));
 }

 void SpellCheckServer::start() {
    mserver_.start();
    LOG_INFO << "拼写检查服务器启动成功";
 }

//有新客户端连接服务器时，新连接回调函数
 void SpellCheckServer::onConnection(const TcpConnectionPtr& conn)
 {
    LOG_INFO << "SpellCheckServer -- " << conn->peerAddress().toIpPort()
             << "新用户"
             << (conn->connected() ? "上线" : "下线");
 }

//当客户端有新消息发送到服务器时，消息响应回调函数
void SpellCheckServer::onMessage(const TcpConnectionPtr &conn,
                                 muduo::net::Buffer *buf,
                                 muduo::Timestamp time)
{
    muduo::string msg(buf->retrieveAllAsString()); //获取客户端发来消息
 
    LOG_INFO << conn->name() << "\n有新消息到达\n" 
             << "检查用户拼写 : " << msg
             << "收到数据大小：" << msg.size()
             << "\n时间：" << time.toString() << "\n";
    
    //将用户输入的单词与字典中的单词进行比较，利用最短编辑距离算法
    //求出多个相似的单词，返回给用户
    //查询倒排索引可以提升效率（避免从头到尾比对字典）

    conn->send(msg);  //收到数据后直接返回用户数据的字符串
}



