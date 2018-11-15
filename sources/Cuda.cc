#include"Cuda.h"

CudaResourceArray::CudaResourceArray()
{
	cudaStreamCreate(&stream);
}
CudaResourceArray::~CudaResourceArray()
{
	popAll();
	cudaStreamDestroy(stream);
}

void CudaResourceArray::pushBuffer(unsigned int ID, void *Buffer)
{
	CudaResource* element = new CudaResource();

	if (cudaSuccess != cudaGraphicsGLRegisterBuffer(&(element->resource), ID, cudaGraphicsRegisterFlagsNone))
		__builtin_trap();
	if (cudaSuccess != cudaGraphicsMapResources(1, &(element->resource), stream))
		__builtin_trap();
	cudaGraphicsResourceSetMapFlags(element->resource, cudaGraphicsMapFlagsNone);
	cudaGraphicsResourceGetMappedPointer(&(element->d_ptr), &(element->size), element->resource);

	element->Buffer = Buffer;
	elements.push_back(element);

}

void CudaResourceArray::pushBuffer(VertexBuffer *vb)
{
	pushBuffer(vb->getID(), reinterpret_cast<void*>(vb));
}


void CudaResourceArray::pushBuffer(IndexBuffer *ib)
{
	pushBuffer(ib->getID(), reinterpret_cast<void*>(ib));
}

void CudaResourceArray::popBuffer(std::vector<CudaResource*>::iterator it)
{
	CudaResource* element = (*it);

	cudaGraphicsUnmapResources(1, &(element->resource), stream);
	cudaGraphicsUnregisterResource(element->resource);
	
	elements.erase(it);
}
void CudaResourceArray::popAll()
{
	while (not elements.empty())
	{
		auto it = elements.end();
		it--;
		popBuffer(it);
	}
}
std::vector<CudaResource*>::iterator CudaResourceArray::findElement(void *Buffer)
{
	std::vector<CudaResource*>::iterator it;
	for (it = elements.begin(); it != elements.end(); it++)
		if (((*it)->Buffer) == Buffer)
			break;
	return it;
}

void CudaResourceArray::popBuffer(VertexBuffer *vb)
{
	auto it = findElement(reinterpret_cast<void*>(vb));
	popBuffer(it);
}
void CudaResourceArray::popBuffer(IndexBuffer *ib)
{
	auto it = findElement(reinterpret_cast<void*>(ib));
	popBuffer(it);
}
void *CudaResourceArray::getPointer(VertexBuffer *vb)
{
	auto it = findElement(reinterpret_cast<void*>(vb));
	return (*it)->d_ptr;
}
void *CudaResourceArray::getPointer(IndexBuffer *ib)
{
	auto it = findElement(reinterpret_cast<void*>(ib));
	return (*it)->d_ptr;
}
size_t CudaResourceArray::getSize(VertexBuffer *vb)
{
	auto it = findElement(reinterpret_cast<void*>(vb));
	return (*it)->size;
}
size_t CudaResourceArray::getSize(IndexBuffer *ib)
{
	auto it = findElement(reinterpret_cast<void*>(ib));
	return (*it)->size;
}



