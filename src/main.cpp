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

#include <string>

int main(void) {
    log.setPriority(DEBUG);   //设置log4cpp 优先级
    
    //初始化配置文件
    std::string config_file_path = "./config.txt";
    MyConfig config(config_file_path);
    bool init_success = config.init();
    if (init_success)
        config.show();




    return 0;
}
