#pragma once

namespace re
{
	class Texture
	{
	public:

		Texture(const std::string& a_filepath);
		~Texture();

		void Bind(GLuint a_slot = 0) const;
		void Unbind() const;

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }
		int GetSize() const { return m_size; }

	private:

		GLuint m_rendererID = 0;
		std::string m_filePath = "";
		unsigned char* m_localBuffer = nullptr;
		int m_height = 0, m_width = 0, m_size = 0;
	};
}