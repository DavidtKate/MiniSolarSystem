#include "repch.h"
#include "Renderer/Texture.h"

#include "stb_image/stb_image.h"

namespace re
{
	Texture::Texture(const std::string& a_filepath)
		: m_filePath(a_filepath)
	{
		// Flip image since openGL expects us to start from bottom-left
		stbi_set_flip_vertically_on_load(1);
		m_localBuffer = stbi_load(a_filepath.c_str(), &m_width, &m_height, &m_size, 4);

		GLCheckError(glGenTextures(1, &m_rendererID));
		GLCheckError(glBindTexture(GL_TEXTURE_2D, m_rendererID));

		// Specify default texture parameters
		GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCheckError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
		GLCheckError(glBindTexture(GL_TEXTURE_2D, 0));

		if (m_localBuffer)
		{
			stbi_image_free(m_localBuffer);
		}
	}

	Texture::~Texture()
	{
		GLCheckError(glDeleteTextures(1, &m_rendererID));
	}

	void Texture::Bind(GLuint a_slot) const
	{
		// Slot default = 0
		GLCheckError(glActiveTexture(GL_TEXTURE0 + a_slot));

		GLCheckError(glBindTexture(GL_TEXTURE_2D, m_rendererID));
	}

	void Texture::Unbind() const
	{
		GLCheckError(glBindTexture(GL_TEXTURE_2D, 0));
	}
}