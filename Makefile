CC		= g++
CXX_FLAGS	= -std=c++17 -g
INCLUDE		= -I./include -I./include/vendor
LIB_FLAGS	= -lGL -lGLEW -lglfw


objects: clean
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Renderer.o sources/Renderer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexArray.o sources/VertexArray.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexBuffer.o sources/VertexBuffer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexBufferLayout.o sources/VertexBufferLayout.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/IndexBuffer.o sources/IndexBuffer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Shader.o sources/Shader.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Texture.o sources/Texture.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/stb_image.o sources/vendor/stb_image.cc


lib: objects
	$(CC) $(INCLUDE) $(CXX_FLAGS) -shared -o libRenderer.so objects/*.o

	rm -rf objects

dynamic: lib
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/5_dynamic.cc ./libRenderer.so $(LIB_FLAGS)

world: lib
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/4_world.cc ./libRenderer.so $(LIB_FLAGS)
depth_test: lib
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/8_world_with_depth_test.cc ./libRenderer.so $(LIB_FLAGS)

3d: lib
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/3_3d.cc ./libRenderer.so $(LIB_FLAGS)

clean:
	rm -rf objects
	rm -f run
	rm -f *.so
	mkdir objects
