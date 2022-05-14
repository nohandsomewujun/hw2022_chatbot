//
// Created by 吴骏 on 2022/5/13.
//

#include "T_bot.h"


void T_bot::read_qa_into_map() {
    //TODO:本函数用来将./q&a/qa.txt中的question作为key，answer作为对应的value读入qa_map中
    //记得裁剪掉q:,a:
    std::ifstream infile("q&a//qa.txt");
    if(!infile){
        std::cout << "file cannot open" << std::endl;
    }
    std::string temp_string;
    std::string q_string;
    while(std::getline(infile, temp_string)){
        if(temp_string[0] == 'q'){
            temp_string = temp_string.substr(2);
            q_string = temp_string;
            qa_map[temp_string] = {};
        }
        else{
            
            temp_string = temp_string.substr(2);
            qa_map[q_string].push_back(temp_string);
        }
    }
}

T_bot::T_bot() {
    //构造类的时候自动执行了map的构建
    read_qa_into_map();
}

void T_bot::calculate_score(const std::string& input_s) {
    //本函数用于计算map中每个key与input_s的匹配得分
    //TODO:将匹配得分最高的那几个key对应的string放入highest_score_q中即可
    //debug print
    // std::cout << qa_map.size() << std::endl;
    // for(auto &t : qa_map){
    //     for(int i = 0; i < t.second.size(); i++){
    //         std::cout << t.second[i] << std::endl;
    //     }
    // }
    int max_score = 0;//目前最高的分数
    for(auto &q : qa_map){
        int temp_score = 0;
        //std::cout << q.first << std::endl;
        for(int i = 0; i < 10; i++){//总共只有十个汉字
            if(input_s.find(q.first.substr(i*2, 2)) != -1){
                temp_score ++;
            }
        }
        //与当前最高分进行比较
        //std::cout << temp_score << std::endl;
        if(temp_score > max_score){
            max_score = temp_score;
            highest_score_q.clear();
            highest_score_q.push_back(q.first);
        }
        else if(temp_score == max_score){
            highest_score_q.push_back(q.first);
        }
    }
    //std::cout << highest_score_q.size() << std::endl;
}


std::string T_bot::speak(const std::string& input_s) {
    //该函数综合运用上述几个函数
    //实现用户输入一个string时，能够对应返回一个string即可
    //使用完记得清除highest_score_q用于下次计算
    //init
    srand((unsigned)time(NULL));

    std::string output_s;
    T_bot::calculate_score(input_s);
    //TODO:利用随机数来选择一个string作为map的key，再利用随机数从map对应的value中得到一个答案作为返回值即可
    std::string key_string;
    int size = highest_score_q.size();
    int randon_num = rand() % size;
    key_string = highest_score_q[randon_num];

    size = qa_map[key_string].size();
    randon_num = rand() % size;
    output_s = qa_map[key_string][randon_num];

    //TODO:清除highest_score_q中的元素来用于下一次计算
    highest_score_q.clear();


    //return
    return output_s;
}

