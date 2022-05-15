pyCall: T_bot_pyCall.cpp T_bot.cpp
	g++ -fPIC -o T_bot_pyCall.so T_bot.cpp T_bot_pyCall.cpp -shared

test: test.cpp T_bot.o
	g++ -o test T_bot.o test.cpp

T_bot.o: T_bot.cpp
	g++ -o T_bot.o -c T_bot.cpp


clean:
	rm *.o test T_bot_pyCall.so