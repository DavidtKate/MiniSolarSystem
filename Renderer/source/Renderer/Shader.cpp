#include "repch.h"
#include "Renderer/Shader.h"

namespace re
{
	Shader::Shader(const std::string& a_vertexShaderPath, const std::string& a_fragmentShaderPath)
		: m_vertexShaderPath(a_vertexShaderPath), m_fragmentShaderPath(a_fragmentShaderPath)
	{
		std::string vertexShader = LoadShader(a_vertexShaderPath);
		std::string fragmentShader = LoadShader(a_fragmentShaderPath);

		m_rendererID = LinkShader(vertexShader, fragmentShader);
	}

	Shader::~Shader()
	{
		GLCheckError(glDeleteProgram(m_rendererID));
	}

	void Shader::Bind() const
	{
		GLCheckError(glUseProgram(m_rendererID));
	}

	void Shader::Unbind() const
	{
		GLCheckError(glUseProgram(0));
	}

	std::string Shader::LoadShader(const std::string& a_filepath)
	{
		// Open file
		std::ifstream stream(a_filepath);
		if (!stream)
		{
			std::cout << "Shader failed to load! Could not find file path: " << a_filepath << std::endl;
			return {};
		}

		// Parse to std::string
		std::stringstream buffer;
		buffer << stream.rdbuf();

		return buffer.str();
	}

	GLuint Shader::LinkShader(const std::string& a_vertexShader, const std::string& a_fragmentShader)
	{
		GLuint program = glCreateProgram();
		GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, a_vertexShader);
		GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, a_fragmentShader);

		GLCheckError(glAttachShader(program, vertexShader));
		GLCheckError(glAttachShader(program, fragmentShader));
		GLCheckError(glLinkProgram(program));
		GLCheckError(glValidateProgram(program));

		GLCheckError(glDeleteShader(vertexShader));
		GLCheckError(glDeleteShader(fragmentShader));

		return program;
	}

	GLuint Shader::CreateShader(GLuint a_type, const std::string& a_source)
	{
		// Create shader
		GLuint id = glCreateShader(a_type);
		const char* source = a_source.c_str();
		GLCheckError(glShaderSource(id, 1, &source, nullptr));
		GLCheckError(glCompileShader(id));

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		// Check if shader compiled successfully
		if (result == GL_FALSE)
		{
			int length;
			GLCheckError(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = new char[length];
			GLCheckError(glGetShaderInfoLog(id, length, &length, message));

			std::cout << "Failed to compile shader!" << std::endl;
			std::cout << message << std::endl;
			GLCheckError(glDeleteShader(id));
			return 0;
		}

		return id;
	}

	GLuint Shader::GetUniformLocation(const std::string& a_name)
	{
		if (m_uniformLocationCache.find(a_name) != m_uniformLocationCache.end())
		{
			return m_uniformLocationCache[a_name];
		}

		int loc = glGetUniformLocation(m_rendererID, a_name.c_str());
		if (loc == -1)
		{
			std::cout << "[Shader Error] Uniform " << a_name << " Doesn't exist!" << std::endl;
		}

		m_uniformLocationCache[a_name] = loc;

		return loc;
	}
}