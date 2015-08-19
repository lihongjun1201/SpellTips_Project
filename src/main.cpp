/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 18 Aug 2015 07:30:40 PM PDT
 ************************************************************************/

#define _LOG4CPP_

#include <iostream>
#include "Mylog.h"
#include "MyConfig.h"
#include "MyDictionary.h"

#include <string>

int main(void) {
    log.setPriority(DEBUG);   //设置log4cpp 优先级
    
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

    
    



    return 0;
}
