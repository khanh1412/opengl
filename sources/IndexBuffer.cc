#include"IndexBuffer.h"
#include"Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
	: m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GLCall(glGenBuffer(1, &buffer));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &(this->m_RendererID)));
}
void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererID));
}
void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
