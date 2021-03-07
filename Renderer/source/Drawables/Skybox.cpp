#include "repch.h"
#include "Drawables/Skybox.h"

#include "Renderer/Renderer.h"
#include "Resources/ResourceManager.h"
#include "stb_image/stb_image.h"

namespace re
{
	Skybox::Skybox(const std::string& a_skyboxFolder, Transform a_transform, const std::string& a_shaderName)
		: m_transform(&a_transform)
	{
		// Set buffers
		m_vao = std::make_unique<VertexArray>();

		m_vbo = std::make_unique<VertexBuffer>(&m_vertices[0], static_cast<uint32_t>(m_vertices.size() * sizeof(float)));
		VertexAttribLayout layout;
		layout.Push<float>(3); // Pos
		m_vao->AddBuffer(*m_vbo, layout);

		// Set cubemap
		CreateCubeMap(a_skyboxFolder);

		m_shader = &ResourceManager::GetInstance().GetResource<Shader>(a_shaderName);
		m_shader->Bind();
		m_shader->SetUniform<int>("u_skybox", 0);
	}

	Skybox::~Skybox()
	{
		GLCheckError(glDeleteTextures(1, &m_textureID));
	}

	void Skybox::Draw() const
	{
		Camera* camera = &Renderer::GetInstance().GetCamera();
		glm::mat4 viewProj = camera->GetProjection() * glm::mat4(glm::mat3(camera->GetView()));

		GLCheckError(glDepthMask(GL_FALSE));
		m_shader->Bind();
		m_shader->SetUniform<glm::mat4>("u_MVP", viewProj);
		m_vao->Bind();
		GLCheckError(glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID));

		GLCheckError(glDrawArrays(GL_TRIANGLES, 0, 36));
		GLCheckError(glDepthMask(GL_TRUE));
	}

	void Skybox::CreateCubeMap(const std::string& a_skyboxFolder)
	{
		stbi_set_flip_vertically_on_load(0);

		std::vector<std::string> faces = {
			a_skyboxFolder + "/right.jpg",
			a_skyboxFolder + "/left.jpg",
			a_skyboxFolder + "/top.jpg",
			a_skyboxFolder + "/bottom.jpg",
			a_skyboxFolder + "/front.jpg",
			a_skyboxFolder + "/back.jpg"
		};

		GLCheckError(glGenTextures(1, &m_textureID));
		GLCheckError(glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID));

		for (int i = 0; i < faces.size(); ++i)
		{
			m_cubeMapBuffer = stbi_load(faces[i].c_str(), &m_cubeMapWidth, &m_cubeMapHeight, &m_cubeMapChannels, 0);
			GLCheckError(glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, m_cubeMapWidth, m_cubeMapHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, m_cubeMapBuffer
			));

			if (m_cubeMapBuffer)
			{
				stbi_image_free(m_cubeMapBuffer);
			}
		}

		GLCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCheckError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	}
}