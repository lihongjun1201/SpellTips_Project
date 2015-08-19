/*************************************************************************
	> File Name: MyDictionary.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 19 Aug 2015 05:07:11 AM PDT
 ************************************************************************/


#include "MyDictionary.h"

#include <iostream>
#include <fstream>
#include <sstream>

MyDictionary* MyDictionary::pInstance = NULL;

//创建字典
MyDictionary* MyDictionary::createInstance(const char *dict_path) {
    if ( NULL == pInstance ) {
        pInstance = new MyDictionary(dict_path);
    }
    return pInstance;
}


//返回字典引用
std::vector<std::pair<std::string,int> >& MyDictionary::get_dict() {
    return m_dictionary_;
}

//显示字典文件
void MyDictionary::showDict()
{
    auto iter = m_dictionary_.begin();
    for(; iter != m_dictionary_.end(); ++iter) {
        std::cout << iter->first <<"-->"
                  << iter->second << "\n";
    }
}

//显示倒排索引
void MyDictionary::showInvertedIndex() {
    auto iter = m_inverted_index_.begin();
    for(; iter != m_inverted_index_.end(); ++iter ){
        std::cout << iter->first << "-->";
        auto sec_iter = iter->second.begin();
        for(;sec_iter != iter->second.end(); ++sec_iter) {
            std::cout << *sec_iter << " ";
        }
        std::cout << "\n";
    }
}



//私有构造函数
MyDictionary::MyDictionary(const char *dict_path) {
    std::ifstream file_in(dict_path);

    if (!file_in) {
        logDebug("read dict_file wrong");
        exit(-1);
    }

    std::string line;
    while (getline(file_in,line)) {
        std::stringstream ss(line);
        std::string word;
        int count;
        ss >> word >>count;
        m_dictionary_.push_back(make_pair(word,count));
    }

    file_in.close();
    logDebug("create dic_vector success!");

    //创建倒排索引表
    for (size_t idx = 0; idx != m_dictionary_.size(); ++idx) {
        createInvertedIndex(idx);
    }
    logDebug("create inverted_index success!");

}


//创建倒排索引表 (优化查询速度) 
void MyDictionary::createInvertedIndex(int index) {
    std::string key;
    std::string word = m_dictionary_[index].first;

    for(std::size_t iidx = 0; iidx != word.size(); ++iidx) {
        if (word[iidx] & (1 << 7)) { //存储GBK编码的中文字符
            key = word.substr(iidx,2);
            ++iidx;
        } else {
            key = word.substr(iidx,1);   
        }
        m_inverted_index_[key].insert(index);
    }
}
