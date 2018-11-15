#ifndef _CUDA_H_
#define _CUDA_H_
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include<cuda_gl_interop.h>
#include<cuda_runtime_api.h>
#include<vector>
typedef struct
{
	void *Buffer;
	cudaGraphicsResource_t resource;
	void *d_ptr;
	size_t size;
}
CudaResource;


class CudaResourceArray
{
	private:
		cudaStream_t stream;
		std::vector<CudaResource*> elements;

		void pushBuffer(unsigned int ID, void *Buffer = nullptr);
		void popBuffer(std::vector<CudaResource*>::iterator it);
		void popAll();
		std::vector<CudaResource*>::iterator findElement(void *Buffer);
	public:
		CudaResourceArray();
		~CudaResourceArray();
		void pushBuffer(VertexBuffer *vb);
		void pushBuffer(IndexBuffer *ib);

		void popBuffer(VertexBuffer *vb);
		void popBuffer(IndexBuffer *ib);
		
		void *getPointer(VertexBuffer *vb);
		void *getPointer(IndexBuffer *ib);
		size_t getSize(VertexBuffer *vb);
		size_t getSize(IndexBuffer *ib);

		inline cudaStream_t getStream() const {return stream;}
		inline void syncStream() const {cudaStreamSynchronize(stream);}
};
#endif
