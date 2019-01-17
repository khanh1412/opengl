CC		= g++
CXX_FLAGS	= -std=c++17 -g
INCLUDE		= -I./include/GL -I./include/GL/vendor -I/usr/include/cuda
LIB_FLAGS	= -lGL -lGLEW -lglfw -lcudart

NVCC		= nvcc
CUDA_CC		= cuda-g++ #gcc 7.x
CUDA_FLAGS	= -ccbin $(CUDA_CC) --default-stream per-thread

normbuffer: 
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o examples/7_normbuffer/main.o examples/7_normbuffer/main.cc
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -dc -o examples/7_normbuffer/device.o examples/7_normbuffer/device.cu
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -o run examples/7_normbuffer/*.o  $(LIB_FLAGS) -lcudart
	rm -f examples/7_normbuffer/*.o
cuda: 
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o examples/6_cuda/main.o examples/6_cuda/main.cc
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -dc -o examples/6_cuda/device.o examples/6_cuda/device.cu
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -o run examples/6_cuda/*.o  $(LIB_FLAGS)
	rm -f examples/6_cuda/*.o
dynamic: 
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -o run examples/5_dynamic.cc  $(LIB_FLAGS)

world: 
	$(NVCC) $(INCLUDE) $(CDUA_FLAGS) -o run examples/4_world.cc  $(LIB_FLAGS)
depth_test: 
	$(NVCC) $(INCLUDE) $(CDUA_FLAGS) -o run examples/8_world_with_depth_test.cc  $(LIB_FLAGS)

3d: 
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -o run examples/3_3d.cc  $(LIB_FLAGS)

clean:
	rm -rf objects
	rm -f run
	rm -f *.so
	mkdir objects
