#include"VertexArray.h"
#include"Renderer.h"
VertexArray::VertexArray()
{

}
VertexArray::~VertexArray()
{

}
VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.Bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
}
