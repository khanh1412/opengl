#include"Cuda.h"
#include<iostream>
CudaInterface::CudaInterface()
	: count(0), map(0)
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
		cudaError_t e = cudaGraphicsGLRegisterBuffer(&resource, vb->getID(), 0);
		if (e == cudaSuccess)
			count++;
		else
		{
			std::cout<<"RegisterBuffer Error: "<<vb->getID()<<std::endl;
			__builtin_trap();
		}
	}
}
void CudaInterface::RegisterBuffer(IndexBuffer *ib)
{
	if (count = 0)
	{
		cudaError_t e = cudaGraphicsGLRegisterBuffer(&resource, ib->getID(), 0);
		if (e == cudaSuccess)
			count++;
		else
		{
			std::cout<<"RegisterBuffer Error: "<<ib->getID()<<std::endl;
			__builtin_trap();

		}
	}
}
void CudaInterface::Unregister()
{
	if (count == 1)
	{
		cudaError_t e = cudaGraphicsUnregisterResource(resource);
		if (e == cudaSuccess)
			count--;
		else
		{
			std::cout<<"UnregisterBuffer Error: "<<std::endl;
			__builtin_trap();
		}
	}

}

void CudaInterface::Map()
{
	if (map==0)
	{
		cudaError_t e = cudaGraphicsMapResources(count, &resource);
		if (e == cudaSuccess)
			map++;
		else
		{
			std::cout<<"MapBuffer Error: "<<std::endl;
			__builtin_trap();
		}
	}
}
void CudaInterface::Unmap()
{
	if (map==1)
	{
		cudaError_t e = cudaGraphicsUnmapResources(count, &resource);
		if (e == cudaSuccess)
			map--;
		else
		{
			std::cout<<"UnmapBuffer Error: "<<std::endl;
			__builtin_trap();
		}
		map--;
	}
}
void CudaInterface::getPointer(void **ptr, size_t *size)
{
	if (map==1)
	{
		cudaError_t e = cudaGraphicsResourceGetMappedPointer(ptr, size, resource);
		if (e != cudaSuccess)
		{
			std::cout<<"Get Pointer Buffer Error: "<<std::endl;
			__builtin_trap();
		}
	}
}


