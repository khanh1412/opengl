CC		= g++
CXX_FLAGS	= -std=c++17 -g
INCLUDE		= -I./include -I./include/vendor/glm -I./include/vendor/stb_image
LIB_FLAGS	= -lGL -lGLEW -lglfw

lib: objects
	$(CC) $(INCLUDE) $(CXX_FLAGS) -shared -o libRenderer.so objects/*.o
	rm -rf objects

objects: clean
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Renderer.o sources/Renderer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexArray.o sources/VertexArray.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexBuffer.o sources/VertexBuffer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexBufferLayout.o sources/VertexBufferLayout.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/IndexBuffer.o sources/IndexBuffer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Shader.o sources/Shader.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Texture.o sources/Texture.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/stb_image.o sources/vendor/stb_image.cc



dynamic:
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/5_dynamic.cc ./libRenderer.so $(LIB_FLAGS)

world:
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/4_world.cc ./libRenderer.so $(LIB_FLAGS)
depth_test:
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/8_world_with_depth_test.cc ./libRenderer.so $(LIB_FLAGS)

3d:
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/3_3d.cc ./libRenderer.so $(LIB_FLAGS)
rec:
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/2_rectangle.cc ./libRenderer.so $(LIB_FLAGS)
tri:
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run examples/1_red_triangle.cc ./libRenderer.so $(LIB_FLAGS)

clean:
	rm -rf objects
	rm -f run
	rm -f *.so
	mkdir objects
