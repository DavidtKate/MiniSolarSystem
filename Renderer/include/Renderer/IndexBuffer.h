#pragma once

namespace re
{
	class IndexBuffer
	{
	public:

		IndexBuffer(const GLuint* a_data, size_t a_count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		size_t GetCount() const { return m_count; }

	private:

		GLuint m_rendererID = 0;
		size_t m_count = 0;
	};
}