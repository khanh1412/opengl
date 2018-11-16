#include"CudaResource.h"
CudaResource::CudaResource(VertexBuffer *vb)
	: stream(0), Buffer(vb), d_ptr(nullptr), size(0), isCudaBuffer(false)
{
	Register(vb->getID());
}
CudaResource::CudaResource(IndexBuffer *ib)
	: stream(0), Buffer(ib), d_ptr(nullptr), size(0), isCudaBuffer(false)
{
	Register(ib->getID());
}
CudaResource::CudaResource(CudaBuffer *nb)
	: stream(0), Buffer(nb), d_ptr(nullptr), size(0), isCudaBuffer(true)
{}
CudaResource::~CudaResource()
{
	Unmap();
	Unregister();
}
inline void CudaResource::Register(unsigned int ID)
{
	if (not isCudaBuffer)
	if (cudaSuccess != cudaGraphicsGLRegisterBuffer(&resource, ID, cudaGraphicsRegisterFlagsNone))
			__builtin_trap();
}
inline void CudaResource::Unregister()
{
	if (not isCudaBuffer)
		cudaGraphicsUnregisterResource(resource);
}

void CudaResource::Map()
{
	if (not isCudaBuffer)
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
	if (not isCudaBuffer)
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



