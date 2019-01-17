#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

class IndexBuffer
{
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
		bool m_Dynamic;
	public:
		//size : size in bytes of data
		IndexBuffer(const unsigned int *data, unsigned int count);
		IndexBuffer(unsigned int count);
		~IndexBuffer();

                void setData(const unsigned int *data, unsigned int count);
		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const {return m_Count;}
		inline unsigned int getID() const {return m_RendererID;}
};
#include<Renderer.h>
#include<iostream>
IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
	: m_Count(count), m_Dynamic(false)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}
IndexBuffer::IndexBuffer(unsigned int count)
	: m_Count(count), m_Dynamic(true)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}
void IndexBuffer::setData(const unsigned int *data, unsigned int count)
{
	if (not m_Dynamic) return;
	if (count > m_Count)
	{
		std::cout<<"Set a larger data than buffer size!"<<std::endl;
		__builtin_trap();
	}
	else 
	{
		if (count < m_Count)
			std::cout<<"Set a smaller data than buffer size!"<<std::endl;

		//void glBufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
		//void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data);
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, static_cast<int>(0), count * sizeof(unsigned int), data);
	}
}
void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}
void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
#endif
