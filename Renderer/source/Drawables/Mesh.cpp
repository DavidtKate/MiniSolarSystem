#include "repch.h"
#include "Drawables/Mesh.h"

#include "Resources/ResourceManager.h"
#include "Resources/Texture.h"

namespace re
{
	Mesh::Mesh(const std::string& a_modelPath, Transform& a_transform, const std::string& a_textureName, const std::string& a_shaderName)
		: m_transform(&a_transform)
	{
		ModelLoader::GetInstance().LoadModel(a_modelPath, m_vertices, m_indices);

		// Set buffers
		m_vao = std::make_unique<VertexArray>();

		m_vbo = std::make_unique<VertexBuffer>(&m_vertices[0], static_cast<uint32_t>(m_vertices.size() * sizeof(ModelLoader::Vertex)));
		VertexAttribLayout layout;
		layout.Push<float>(3); // Pos
		layout.Push<float>(2); // Texcoords
		layout.Push<float>(3); // Normals
		m_vao->AddBuffer(*m_vbo, layout);

		m_ebo = std::make_unique<IndexBuffer>(&m_indices[0], m_indices.size());

		// Set texture
		m_texture = &ResourceManager::GetInstance().GetResource<Texture>(a_textureName);
		m_texture->Bind();

		m_shader = &ResourceManager::GetInstance().GetResource<Shader>(a_shaderName);
		m_shader->Bind();
		m_shader->SetUniform<int>("u_texture", 0);
	}

	void Mesh::Draw() const
	{
		m_vao->Bind();
		m_ebo->Bind();
		m_texture->Bind();

		GLCheckError(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr));
	}
}