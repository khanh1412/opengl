CC=g++
CXX_FLAGS=-std=c++17 -I./include -I./include/vendor -g
LIB_FLAGS= -lGL -lGLEW -lglfw

lib: clean
	mkdir objects
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/Renderer.o sources/Renderer.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/VertexArray.o sources/VertexArray.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/VertexBuffer.o sources/VertexBuffer.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/VertexBufferLayout.o sources/VertexBufferLayout.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/IndexBuffer.o sources/IndexBuffer.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/Shader.o sources/Shader.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/Texture.o sources/Texture.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/stb_image.o sources/vendor/stb_image.cc
	$(CC) $(CXX_FLAGS) -shared -o libRenderer.so objects/*.o
	rm -rf objects
	mkdir objects
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/Engine.o sources/Engine.cc
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/Object.o sources/Object.cc
	$(CC) $(CXX_FLAGS) -shared -o libEngine.so objects/*.o
	rm -rf objects


main:
	$(CC) $(CXX_FLAGS) -o run main.cc snake/sources/Sphere.cc snake/sources/Rectangle.cc ./libRenderer.so ./libEngine.so $(LIB_FLAGS) -I./snake/include


3d:
	$(CC) $(CXX_FLAGS) -o run examples/3d.cc ./libRenderer.so $(LIB_FLAGS)
world:
	$(CC) $(CXX_FLAGS) -o run examples/world.cc ./libRenderer.so $(LIB_FLAGS)

clean:
	rm -rf objects
	rm -f run
	rm -f libRenderer.so
