#pragma once

namespace re
{
	class VertexBuffer
	{
	public:

		VertexBuffer(const void* a_data, unsigned int a_size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

	private:

		GLuint m_rendererID = 0;
	};
}