#ifndef _CUDA_RESOURCE_H_
#define _CUDA_RESOURCE_H_
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include<cuda_runtime_api.h>
#include<cuda_gl_interop.h>
class CudaResource
{
	private:
		void *Buffer;
		cudaGraphicsResource_t resource;
	        void *d_ptr;
        	size_t d_size;

		cudaStream_t stream;

		void Register(unsigned int ID);
		void Unregister();
		
	public:
		CudaResource(unsigned int ID, void *Buffer=nullptr);
		CudaResource(VertexBuffer *vb);
		CudaResource(IndexBuffer *ib);
		~CudaResource();
		
		void Map();
		void Unmap();
		
		inline void *getPointer() const {return d_ptr;};
		inline size_t getSize() const {return d_size;};
		inline void setStream(cudaStream_t stream)
			{if (d_size) Unmap(); this->stream = stream;}		
		inline cudaStream_t getStream() const {return stream;}
		inline void syncStream() const {cudaStreamSynchronize(stream);}
};
#endif
