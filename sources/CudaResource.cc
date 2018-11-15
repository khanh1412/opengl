#include"CudaResource.h"
CudaResource::CudaResource(unsigned int ID, void* Buffer)
	: stream(0), d_ptr(nullptr), Buffer(Buffer), d_size(0)
{
	Register(ID);
}
CudaResource::CudaResource(VertexBuffer *vb)
	: stream(0), d_ptr(nullptr), Buffer(vb), d_size(0)
{
	Register(vb->getID());
}
CudaResource::CudaResource(IndexBuffer *ib)
	: stream(0), d_ptr(nullptr), Buffer(ib), d_size(0)
{
	Register(ib->getID());
}
CudaResource::~CudaResource()
{
	
}
inline void CudaResource::Register(unsigned int ID)
{
	if (cudaSuccess != cudaGraphicsGLRegisterBuffer(&resource, ID, cudaGraphicsRegisterFlagsNone))
		__builtin_trap();
}
inline void CudaResource::Unregister()
{
	cudaGraphicsUnregisterResource(resource);
}

void CudaResource::Map()
{
	if (cudaSuccess != cudaGraphicsMapResources(1, &resource, stream))
		__builtin_trap();
	cudaGraphicsResourceSetMapFlags(resource, cudaGraphicsMapFlagsNone);
	cudaGraphicsResourceGetMappedPointer(&d_ptr, &d_size, resource);
}
void CudaResource::Unmap()
{
	cudaGraphicsUnmapResources(1, &resource, stream);
	d_ptr = nullptr;
	d_size = 0;
}



