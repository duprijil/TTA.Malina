all: compile

compile:
	g++ -o app src/*.cpp main.cpp -Iinclude/ -lczmq -lpthread -lX11 -ldl lib/libraylib.a lib/libzmqWrap.a
