#ifndef _CUDA_RESOURCE_H_
#define _CUDA_RESOURCE_H_
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"NormBuffer.h"
#include<cuda_runtime_api.h>
#include<cuda_gl_interop.h>
class CudaResource
{
	private:
		cudaStream_t stream;
		void *Buffer;
		cudaGraphicsResource_t resource;
	        void *d_ptr;
        	size_t size;
		bool isNormBuffer;


		void Register(unsigned int ID);
		void Unregister();
		
	public:
		CudaResource(VertexBuffer *vb);
		CudaResource(IndexBuffer *ib);
		CudaResource(NormBuffer *nb);
		~CudaResource();
		
		void Map();
		void Unmap();
		
		inline void *getPointer() const {return d_ptr;};
		inline size_t getSize() const {return size;};
		inline void setStream(cudaStream_t stream)
			{if (size) Unmap(); this->stream = stream;}		
		inline cudaStream_t getStream() const {return stream;}
		inline void syncStream() const {cudaStreamSynchronize(stream);}
};
#endif
