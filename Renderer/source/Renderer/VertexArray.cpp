#include "repch.h"
#include "Renderer/VertexArray.h"

#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexAttribLayout.h"

namespace re
{
	VertexArray::VertexArray()
	{
		GLCheckError(glGenVertexArrays(1, &m_rendererID));
	}

	VertexArray::~VertexArray()
	{
		GLCheckError(glDeleteVertexArrays(1, &m_rendererID));
	}

	void VertexArray::AddBuffer(const VertexBuffer& a_vertexBuffer, const VertexAttribLayout& a_vertexAttribLayout)
	{
		Bind();
		a_vertexBuffer.Bind();
		const auto& elements = a_vertexAttribLayout.GetElements();

		size_t offset = 0;

		for (GLuint i = 0; i < elements.size(); ++i)
		{
			const auto& element = elements[i];
			GLCheckError(glEnableVertexAttribArray(i));
			GLCheckError(glVertexAttribPointer(i, element.count, element.type, static_cast<GLboolean>(element.normalized), a_vertexAttribLayout.GetStride(), (const void*)offset));
			offset += element.count * VertexAttrib::GetSizeOfType(element.type);
		}
	}

	void VertexArray::Bind() const
	{
		GLCheckError(glBindVertexArray(m_rendererID));
	}

	void VertexArray::Unbind() const
	{
		GLCheckError(glBindVertexArray(0));
	}
}