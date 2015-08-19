/*************************************************************************
	> File Name: MyConfig.h
	> Author: 
	> Mail: 
	> Created Time: Wed 19 Aug 2015 01:38:46 AM PDT
 ************************************************************************/

#ifndef _MYCONFIG_H
#define _MYCONFIG_H

#include "Mylog.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>

class MyConfig {
 public:
    //配置类构造函数
    MyConfig(std::string &conf_file_path);

    //获取配置文件map
    std::map<std::string,std::string> &get_map() {
        return m_config_map_;
    }

    bool init();

    void show();

 private:
    std::ifstream m_config_file_in_;           //配置文件输入流
    std::map<std::string,std::string> m_config_map_;   //配置文件map映射
};











#endif
