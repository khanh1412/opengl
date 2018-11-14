CC=g++
CXX_FLAGS=-std=c++17 -g -I./include -I../include -I../include/vendor
LIB_FLAGS= -lGL -lGLEW -lglfw


all: clean copy	
	$(CC) $(CXX_FLAGS) -o run main.cc sources/*.cc ./libRenderer.so $(LIB_FLAGS)
copy:
	cp ../libRenderer.so .
clean:
	rm -f run

