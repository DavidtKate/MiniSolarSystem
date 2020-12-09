#include "repch.h"
#include "Renderer/IndexBuffer.h"

namespace re
{
	IndexBuffer::IndexBuffer(const GLuint* a_data, size_t a_count)
		: m_count(a_count)
	{
		GLCheckError(glGenBuffers(1, &m_rendererID));
		GLCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
		GLCheckError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_count * sizeof(GLuint), a_data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCheckError(glDeleteBuffers(1, &m_rendererID));
	}

	void IndexBuffer::Bind() const
	{
		GLCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	}

	void IndexBuffer::Unbind() const
	{
		GLCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}