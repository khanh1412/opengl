#include"VertexBuffer.h"
#include"Renderer.h"
VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
	GLCall(glGenBuffer(1, &buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &(this->m_RendererID)));
}
void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererID));
}
void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
