#include "repch.h"
#include "Renderer/VertexBuffer.h"

namespace re
{
	VertexBuffer::VertexBuffer(const void* a_data, unsigned int a_size)
	{
		GLCheckError(glGenBuffers(1, &m_rendererID));
		GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
		GLCheckError(glBufferData(GL_ARRAY_BUFFER, a_size, a_data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCheckError(glDeleteBuffers(1, &m_rendererID));
	}

	void VertexBuffer::Bind() const
	{
		GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	}

	void VertexBuffer::Unbind() const
	{
		GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}