CC=g++
CXX_FLAGS=-std=c++17 -I./include -I./include/vendor -g -I/usr/include/cuda
LIB_FLAGS= -lGL -lGLEW -lglfw -lcudart

NVCC=nvcc
CUDA_FLAGS= -ccbin cuda-g++ -I./include -I./include/vendor -I/usr/include/cuda -DCUDA --default-stream per-thread



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
	$(CC) $(CXX_FLAGS) -c -fPIC -o objects/Cuda.o sources/Cuda.cc -I/usr/include/cuda
	$(CC) $(CXX_FLAGS) -shared -o libRenderer.so objects/*.o
	rm -rf objects
cuda: ./libRenderer.so
	$(CC) $(CXX_FLAGS) -c -fPIC -o examples/6_cuda/main.o examples/6_cuda/main.cc -DCUDA
	$(NVCC) $(CUDA_FLAGS) -dc -o examples/6_cuda/device.o examples/6_cuda/device.cu -DCUDA
	$(NVCC) $(CUDA_FLAGS) -o run examples/6_cuda/main.o examples/6_cuda/device.o ./libRenderer.so $(LIB_FLAGS) -lcudart
	rm -f examples/6_cuda/*.o
dynamic: ./libRenderer.so
	$(CC) $(CXX_FLAGS) -o run examples/5_dynamic.cc ./libRenderer.so $(LIB_FLAGS)

world: ./libRenderer.so
	$(CC) $(CXX_FLAGS) -o run examples/4_world.cc ./libRenderer.so $(LIB_FLAGS)

3d: ./libRenderer.so
	$(CC) $(CXX_FLAGS) -o run examples/3_3d.cc ./libRenderer.so $(LIB_FLAGS)

clean:
	rm -rf objects
	rm -f run
	rm -f *.so
