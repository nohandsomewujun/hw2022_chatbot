#include "T_bot.h"
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

extern "C" {
    T_bot* newTBot() {
        T_bot* b = new T_bot();
        return b;
    }
    
    void call(T_bot* bot, char* str, char* dst) {
        string in;
        for(int i = 0; i < 10 && str[i] != 0; i++) {
            in = in + str[i];
        }
        cout << "in: " << in << endl;

        string out = bot->speak(in);
        cout << "out: " << out << endl;

        strcpy(dst, out.c_str());
    }
}
