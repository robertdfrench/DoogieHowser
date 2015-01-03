all: doogie.exe

LUA_DIR = /usr/local/Cellar/lua/5.2.3_1
doogie.exe: main.cpp
	llvm-g++ -g main.cpp -o doogie.exe -I$(LUA_DIR)/include -L$(LUA_DIR)/lib -lm -llua

clean:
	rm -rf doogie.exe
