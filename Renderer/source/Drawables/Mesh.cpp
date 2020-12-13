#include "repch.h"
#include "Drawables/Mesh.h"

namespace re
{
	Mesh::Mesh(const std::string& a_modelPath, const std::string& a_texturePath, Transform& a_transform, Shader& a_shader)
		: m_transform(&a_transform), m_shader(&a_shader)
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
		m_texture = std::make_unique<Texture>(a_texturePath);
		a_shader.Bind();
		a_shader.SetUniform<int>("u_texture", 0);
	}

	void Mesh::Draw() const
	{
		m_vao->Bind();
		m_ebo->Bind();
		m_texture->Bind();

		GLCheckError(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr));
	}
}