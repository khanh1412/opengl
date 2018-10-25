#ifndef _VERTEX_ARRAY_
#define _VERTEX_ARRAY_

#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
class VertexArray
{
	private:
		
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
}
#endif
