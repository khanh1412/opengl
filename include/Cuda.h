#ifndef _CUDA_H_
#define _CUDA_H_
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include<cuda_gl_interop.h>
#include<cuda_runtime_api.h>
class CudaInterface
{
	private:
		cudaGraphicsResource_t resource;
		int count;
	public:
		CudaInterface();
		~CudaInterface();
		void RegisterBuffer(VertexBuffer *vb);
		void RegisterBuffer(IndexBuffer *ib);
		void Unregister();
		void Map();
		void Unmap();
		void getPointer(void **ptr, size_t *size);

};
#endif
