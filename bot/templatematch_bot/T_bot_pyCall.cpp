#include "T_bot.h"
#include <cstring>

using namespace std;

extern "C" {
    T_bot* newTBot() {
        return new T_bot();
    }
    
    void call(T_bot* bot, char* str, char* dst) {
        strcpy(dst, bot->speak(string(str)).c_str());
    }
}
