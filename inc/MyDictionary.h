/*************************************************************************
	> File Name: MyDictionary.h
	> Author: 
	> Mail: 
	> Created Time: Wed 19 Aug 2015 02:27:07 AM PDT
 ************************************************************************/

#ifndef _MY_DICTIONARY_H
#define _MY_DICTIONARY_H


#include <string>
#include <map>
#include <vector>
#include <utility>
#include <set>


//英语（中文）字典类
//单例模式

class MyDictionary {
 public:
    static MyDictionary* createInstance(const char* dict_path);

    std::vector<std::pair<std::string,int> >& get_dict();

    //打印测试文件数据
    void showDict();
    void showInvertedIndex();

    void createInvertedIndex(int index);

    //构造函数私有化
 private:
    MyDictionary(const char*dict_path);

 private:
    static MyDictionary* pInstance;
    std::vector<std::pair<std::string,int> > m_dictionary_; //字典词频表
    
    std::map<std::string,std::set<int> > m_inverted_index_;   //字典倒排索引

};



#endif
