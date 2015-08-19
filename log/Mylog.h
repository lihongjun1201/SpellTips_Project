/*************************************************************************
	> File Name: mylog.h
	> Author: 
	> Mail: 
	> Created Time: Thu 30 Jul 2015 05:35:03 AM PDT
 ************************************************************************/

#ifndef _MYLOG_H
#define _MYLOG_H

#include<log4cpp/Category.hh>
#include<iostream>

//日志优先级
enum Priority {
    ERROR,
    WARN,
    INFO,
    DEBUG
};

//用单例模式封装log4cpp
class Mylog {
 public: 
    static Mylog& getInstance();
    static void destory();

    void setPriority(Priority priority);
    void error(const char* msg);
    void warn(const char* msg);
    void info(const char* msg);
    void debug(const char* msg);

 private:
    Mylog();  //单例模式：构造函数私有化

 private:
    static Mylog *plog_;
    log4cpp::Category &category_ref_;
};

//整数类型文件行号 ->转换为string类型
inline std::string int2string(int line) {
    std::ostringstream oss;
    oss << line;
    return oss.str();
}


//定义一个在日志后添加 文件名 函数名 行号 的宏定义
#define suffix(msg)  std::string(msg).append(" ##")\
        .append(__FILE__).append(":").append(__func__)\
        .append(":").append(int2string(__LINE__))\
        .append("##").c_str()


//不用每次使用时写 getInstance语句
//只需要在主函数文件中写: #define _LOG4CPP_即可在整个程序中使用
#ifdef _LOG4CPP_
Mylog &log = Mylog::getInstance();
#else
extern Mylog &log;
#endif

//缩短并简化函数调用形式
#define logError(msg) log.error(suffix(msg))
#define logWarn(msg) log.warn(suffix(msg))
#define logInfo(msg) log.info(suffix(msg))
#define logDebug(msg) log.debug(suffix(msg))

#endif
