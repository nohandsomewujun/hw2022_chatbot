#include "./T_bot.h"
#include<iostream>

using namespace std;
int main() {
    std::string s = "你";
    std::cout << s.size() << std::endl;
    T_bot chatbot;
    string input_s, output_s;
    cout << "请输入：";
    cin >> input_s;
    while(input_s != "q"){
        output_s =  chatbot.speak(input_s);
        cout << output_s << endl;
        cout << "请输入：";
        cin >> input_s;
    }
}