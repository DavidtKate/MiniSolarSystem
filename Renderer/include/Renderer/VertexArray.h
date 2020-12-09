#pragma once

namespace re
{
	class VertexBuffer;
	class VertexAttribLayout;

	class VertexArray
	{
	public:

		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& a_vertexBuffer, const VertexAttribLayout& a_vertexAttribLayout);
		void Bind() const;
		void Unbind() const;

	private:

		GLuint m_rendererID = 0;
	};
}