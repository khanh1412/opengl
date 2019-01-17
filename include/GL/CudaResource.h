#ifndef _CUDA_RESOURCE_H_
#define _CUDA_RESOURCE_H_
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"Texture.h"
#include"CudaBuffer.h"
#include<cuda_runtime_api.h>
#include<cuda_gl_interop.h>
enum ResourceType {OPENGL_BUFFER, CUDA_BUFFER, IMAGE};
class CudaResource
{
	private:
		cudaStream_t stream;
		void *Buffer;
		cudaGraphicsResource_t resource;
	        void *d_ptr;
        	size_t size;
		ResourceType type;


		void Register(unsigned int ID);
		void Unregister();
		
	public:
		CudaResource(VertexBuffer *vb);
		CudaResource(IndexBuffer *ib);
		CudaResource(CudaBuffer *nb);
		CudaResource(Texture *t);
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
CudaResource::CudaResource(VertexBuffer *vb)
	: stream(0), Buffer(vb), d_ptr(nullptr), size(0), type(OPENGL_BUFFER)
{
	Register(vb->getID());
}
CudaResource::CudaResource(IndexBuffer *ib)
	: stream(0), Buffer(ib), d_ptr(nullptr), size(0), type(OPENGL_BUFFER)
{
	Register(ib->getID());
}
CudaResource::CudaResource(Texture *t)
	: stream(0), Buffer(t), d_ptr(nullptr), size(0), type(IMAGE)
{
	Register(t->getID());
}
CudaResource::CudaResource(CudaBuffer *nb)
	: stream(0), Buffer(nb), d_ptr(nullptr), size(0), type(CUDA_BUFFER)
{}
CudaResource::~CudaResource()
{
	Unmap();
	Unregister();
}
inline void CudaResource::Register(unsigned int ID)
{
	if (type == OPENGL_BUFFER)
	{
		if (cudaSuccess != cudaGraphicsGLRegisterBuffer(&resource, ID, cudaGraphicsRegisterFlagsNone))
			__builtin_trap();
	}
	else if (type == IMAGE)
	{
		if (cudaSuccess != cudaGraphicsGLRegisterImage(&resource, ID, GL_TEXTURE_2D, cudaGraphicsRegisterFlagsNone))
			__builtin_trap();
	}

}
inline void CudaResource::Unregister()
{
	if (type == OPENGL_BUFFER)
		cudaGraphicsUnregisterResource(resource);
}

void CudaResource::Map()
{
	if (type != CUDA_BUFFER)
	{
		if (cudaSuccess != cudaGraphicsMapResources(1, &resource, stream))
			__builtin_trap();
		cudaGraphicsResourceSetMapFlags(resource, cudaGraphicsMapFlagsNone);
		cudaGraphicsResourceGetMappedPointer(&d_ptr, &size, resource);
	}
	else
	{
		size = reinterpret_cast<CudaBuffer*>(Buffer)->getSize();
		void *h_ptr = reinterpret_cast<CudaBuffer*>(Buffer)->getHostPointer();
		cudaMalloc(&d_ptr, size);
		cudaMemcpyAsync(d_ptr, h_ptr, size, cudaMemcpyHostToDevice, stream);
	}
}
void CudaResource::Unmap()
{
	if (type != CUDA_BUFFER)
	{
		if(d_ptr)
		{
			cudaGraphicsUnmapResources(1, &resource, stream);
			d_ptr = nullptr;
			size = 0;
		}
	}
	else
	{
		cudaFree(d_ptr);
		d_ptr = nullptr;
		size = 0;
	}
}
#endif
