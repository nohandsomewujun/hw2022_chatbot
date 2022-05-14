//
// Created by 吴骏 on 2022/5/13.
//

#include "T_bot.h"

void T_bot::read_qa_into_map() {
    //TODO:本函数用来将./q&a/qa.txt中的question作为key，answer作为对应的value读入qa_map中
    //记得裁剪掉q:,a:

}

T_bot::T_bot() {
    //构造类的时候自动执行了map的构建
    read_qa_into_map();
}

void T_bot::calculate_score(const std::string& input_s) {
    //本函数用于计算map中每个key与input_s的匹配得分
    //TODO:将匹配得分最高的那几个key对应的string放入highest_score_q中即可


}


std::string T_bot::speak(const std::string& input_s) {
    //该函数综合运用上述几个函数
    //实现用户输入一个string时，能够对应返回一个string即可
    //使用完记得清除highest_score_q用于下次计算
    //init
    std::string output_s;
    T_bot::calculate_score(input_s);
    //TODO:利用随机数来选择一个string作为map的key，再利用随机数从map对应的value中得到一个答案作为返回值即可


    //TODO:清除highest_score_q中的元素来用于下一次计算



    //return
    return output_s;
}