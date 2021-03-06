#pragma once
#include "Resources/Resource.h"

namespace re
{
	class Shader : public Resource
	{
	public:

		Shader(const std::string& a_vertexShaderPath, const std::string& a_fragmentShaderPath)
			: m_vertexShaderPath(a_vertexShaderPath), m_fragmentShaderPath(a_fragmentShaderPath) {}
		~Shader() override = default;

		void Load() override;
		void Unload() override;

		void Bind() const;
		void Unbind() const;

		template <typename T>
		void SetUniform(const std::string& a_name, T a_value)
		{
			if constexpr (std::is_same_v<std::decay_t<T>, int>)
			{
				GLCheckError(glUniform1i(GetUniformLocation(a_name), a_value));
			}
			else if constexpr (std::is_same_v<std::decay_t<T>, float>)
			{
				GLCheckError(glUniform1f(GetUniformLocation(a_name), a_value));
			}
			else if constexpr (std::is_same_v<std::decay_t<T>, glm::vec2>)
			{
				GLCheckError(glUniform2f(GetUniformLocation(a_name), a_value.x, a_value.y));
			}
			else if constexpr (std::is_same_v<std::decay_t<T>, glm::vec3>)
			{
				GLCheckError(glUniform3f(GetUniformLocation(a_name), a_value.x, a_value.y, a_value.z));
			}
			else if constexpr (std::is_same_v<std::decay_t<T>, glm::vec4>)
			{
				GLCheckError(glUniform4f(GetUniformLocation(a_name), a_value.x, a_value.y, a_value.z, a_value.w));
			}
			else if constexpr (std::is_same_v<std::decay_t<T>, glm::mat4>)
			{
				GLCheckError(glUniformMatrix4fv(GetUniformLocation(a_name), 1, GL_FALSE, &a_value[0][0]));
			}
			else
			{
				std::cout << "Trying to modify invalid/unsupported uniform type!" << std::endl;
			}
		}

	private:

		std::string LoadShader(const std::string& a_filepath);
		GLuint LinkShader(const std::string& a_vertexShader, const std::string& a_fragmentShader);
		GLuint CreateShader(GLuint a_type, const std::string& a_source);

		GLuint GetUniformLocation(const std::string& a_name);

		GLuint m_rendererID = 0;
		std::string m_vertexShaderPath = "resources/shaders/default.vert";
		std::string m_fragmentShaderPath = "resources/shaders/default.frag";
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};
}