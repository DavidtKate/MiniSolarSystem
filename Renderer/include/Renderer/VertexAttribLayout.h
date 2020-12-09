#pragma once

namespace re
{
	struct VertexAttrib
	{
		GLuint type = 0;
		GLuint count = 0;
		GLboolean normalized = GL_FALSE;

		static GLuint GetSizeOfType(GLuint type)
		{
			switch (type)
			{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:  return 1;
			}
			//ASSERT(false)
			return 0;
		}
	};

	class VertexAttribLayout
	{
	public:

		VertexAttribLayout() : m_stride(0) {}
		~VertexAttribLayout() = default;

		template<typename T>
		void Push(unsigned int a_count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int a_count)
		{
			m_elements.push_back({ GL_FLOAT, a_count, GL_FALSE });
			m_stride += a_count * VertexAttrib::GetSizeOfType(GL_FLOAT);
		}

		template<>
		void Push<unsigned int>(unsigned int a_count)
		{
			m_elements.push_back({ GL_UNSIGNED_INT, a_count, GL_FALSE });
			m_stride += a_count * VertexAttrib::GetSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(unsigned int a_count)
		{
			m_elements.push_back({ GL_UNSIGNED_BYTE, a_count, GL_TRUE });
			m_stride += a_count * VertexAttrib::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexAttrib>& GetElements() const { return m_elements; }
		inline unsigned int GetStride() const { return m_stride; }

	private:

		std::vector<VertexAttrib> m_elements;
		unsigned int m_stride = 0;
	};
}