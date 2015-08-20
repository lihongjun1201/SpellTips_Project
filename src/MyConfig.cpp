/*************************************************************************
	> File Name: MyConfig.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 19 Aug 2015 01:47:40 AM PDT
 ************************************************************************/

#include "MyConfig.h"

//配置类构造函数
MyConfig::MyConfig(std::string &conf_file_path):
    m_config_file_in_(conf_file_path.c_str())
{}


//初始化配置文件map
bool MyConfig::init() {
    if (!m_config_file_in_) {
        return false;
    }
    
    std::string line;
    while (getline(m_config_file_in_,line)) {
        std::istringstream iss(line);
        std::string key,
                    value;
        iss >> key >> value;
        m_config_map_.insert(make_pair(key,value));
    }
    m_config_file_in_.close();
    return true;
}

void MyConfig::show() {
    std::map<std::string,std::string>::const_iterator
    map_citer = m_config_map_.begin();
    for (; map_citer != m_config_map_.end(); ++map_citer) {
        std::cout << map_citer->first << "---->" 
                  << map_citer->second << "\n";
    }
}
