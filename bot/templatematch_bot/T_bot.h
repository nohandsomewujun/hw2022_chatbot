//
// Created by 吴骏 on 2022/5/13.
//

#ifndef HW2022_CHATBOT_T_BOT_H
#define HW2022_CHATBOT_T_BOT_H
#include <map>
#include <vector>
#include <string>


class T_bot {

private:
    //qa_map
    //一个用于存放问题和回答的对应关系的map
    //即每个问题的string对应了多个回答的string
    //最后得到的answer是会利用随机数送这多个回答中取出一个即可
    std::map<std::string, std::vector<std::string>> qa_map;
    //用来存放得分最大的问题string
    std::vector<std::string> highest_score_q;
    //用来将./q&a/qa.txt中的qa读入map
    void read_qa_into_map();
public:
    //构造函数，类创建时可以自动读入map
    T_bot();
    //用来计算匹配，将最大的几个匹配的string放入highest_score_q中
    //!!!记住每次应当清空highest_score_q后再使用
    void calculate_score(const std::string& input_s);
    //利用随机数将highest_score_q中的某个string取出，作为map的key求出对应的value作为返回值
    std::string speak(const std::string& input_s);
};


#endif //HW2022_CHATBOT_T_BOT_H
