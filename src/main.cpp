/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 18 Aug 2015 07:30:40 PM PDT
 ************************************************************************/

#define _LOG4CPP_

#include <iostream>
#include "Mylog.h"
#include "func.h"

int main(void) {
    logError("error allen");
    logDebug("debug allen");
    logInfo("info allen");

    func();

    return 0;
}
