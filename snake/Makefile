CC=g++
CXX_FLAGS=-std=c++17 -g -I./include -I../include -I../include/vendor
LIB_FLAGS= -lGL -lGLEW -lglfw


lib: clean copy
	mkdir objects
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/Engine.o sources/Engine.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/Object.o sources/Object.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/Rectangle.o sources/Rectangle.cc
	$(CC) $(CXX_FLAGS) -shared -o libEngine.so objects/*.o ./libRenderer.so
	rm -rf objects

main: lib
	$(CC) $(CXX_FLAGS) -o run ./main.cc ./libEngine.so ./libRenderer.so $(LIB_FLAGS)

copy:
	cp ../libRenderer.so .
clean:
	rm -rf objects
	rm -f run
	rm -f libEngine.so
	rm -f libRenderer.so

