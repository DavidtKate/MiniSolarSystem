#pragma once
#include "Resources/Resource.h"

namespace re
{
	class Texture : public Resource
	{
	public:

		Texture(const std::string& a_filepath)
			: m_filePath(a_filepath) {}
		~Texture() override = default;

		void Load() override;
		void Unload() override;

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