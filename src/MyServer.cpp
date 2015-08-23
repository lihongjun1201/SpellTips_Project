/*************************************************************************
	> File Name: MyServer.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 22 Aug 2015 08:52:17 AM PDT
 ************************************************************************/

#include "MyServer.h"

#include <muduo/base/Logging.h>
#include <boost/bind.hpp>

#include <algorithm>


using namespace muduo;
using namespace muduo::net;
using namespace std;


void SpellCheckServer::init() {
}



//返回三者最小函数
int minInThree(int a, int b, int c) {
    int t = a < b ? a : b;
    return t < c ? t : c;
}

#if 1
//获取最端编辑距离
int getShortestEditDistance(std::string a, muduo::string b) {
    int la = a.size();
    int lb = b.size();

    int dp_table[la+1][lb+1] ;

    for (int i = 0; i <= la; ++i)
        dp_table[i][0] = i;
   
    for (int j = 0; j <= lb; ++j)
        dp_table[0][j] = j;

    for (int i = 1; i < la + 1; ++i) {
        for (int j =1; j < lb + 1; ++j) {
            int cost = a[i-1] == b[j-1] ? 0 : 1; //相等则需要替换

            int deletion = dp_table[i-1][j] + 1;
            int insertion = dp_table[i][j-1] + 1;
            int replace = dp_table[i-1][j-1] + cost;

            dp_table[i][j] = minInThree(deletion,insertion,replace);
        }
    }

#if 0
    for (int i = 0; i < la + 1; ++i) {
        for (int j = 0; j < lb + 1; ++j) {
            cout << dp_table[i][j] << " ";
        }
        cout << endl;
    }
#endif

    return dp_table[la][lb];
}
#endif


//查找与用户输入相近的单词
std::vector<std::string>& SpellCheckServer::searchDictionary(muduo::string &search_word) {
    auto iter = ( pMydictionary_->get_dict() ).begin();
    for (; iter != ( pMydictionary_->get_dict() ).end(); ++iter) {
        int edit_dis = getShortestEditDistance(iter->first,search_word);
        if (edit_dis <= 2) {
            msearch_result_.push_back(iter->first);
        }
    }
    cout << "相近词大约有" << msearch_result_.size() << "个\n";

    return msearch_result_;
}


//服务器构造函数
SpellCheckServer::SpellCheckServer(EventLoop *loop,
                                  const InetAddress &listen_addr,
                                  MyDictionary *pDict)
 : mserver_(loop,listen_addr,"SpellCheckServer"),pMydictionary_(pDict)
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


    auto result = searchDictionary(msg);
    
    for (auto iter = result.begin(); iter != result.end(); ++iter) {
        cout << *iter << "\n";
        conn->send(*iter+"\r\n");
    }
    
    msearch_result_.clear();
    conn->send("\r\n");

    //pMydictionary_->showDict();
    
    
}



