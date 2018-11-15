#include"Cuda.h"
CudaInterface::CudaInterface()
	: resource(nullptr), count(0)
{}
CudaInterface::~CudaInterface()
{
	Unmap();
	Unregister();
}

void CudaInterface::RegisterBuffer(VertexBuffer *vb)
{
	if (count == 0)
	{
		cudaGraphicsGLRegisterBuffer(resource, vb->getID(), 0);
		count++;
	}
}
void CudaInterface::RegisterBuffer(IndexBuffer *ib)
{
	if (count = 0)
	{
		cudaGraphicsGLRegisterBuffer(resource, ib->getID(), 0);
		count++;
	}
}
void CudaInterface::Unregister()
{
	if (count == 1)
	{
		cudaGraphicsUnregisterResource(*resource);
		count--;
	}

}

void CudaInterface::Map()
{
	cudaGraphicsMapResources(count, resource);
}
void CudaInterface::Unmap()
{
	cudaGraphicsUnmapResources(count, resource);
}
void CudaInterface::getPointer(void **ptr, size_t *size)
{
	cudaGraphicsResourceGetMappedPointer(ptr, size, *resource);
}


