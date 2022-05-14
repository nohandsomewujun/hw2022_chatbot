#include "T_bot.h"
#include<iostream>

using namespace std;
int main(){
    std::string s = "Äã";
    std::cout << s.size() << std::endl;
    T_bot chatbot;
    string input_s, output_s;
    cout << "ÇëÊäÈë£º";
    cin >> input_s;
    while(input_s != "q"){
        output_s =  chatbot.speak(input_s);
        cout << output_s << endl;
        cout << "ÇëÊäÈë£º";
        cin >> input_s;
    }
    
}