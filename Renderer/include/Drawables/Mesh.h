#pragma once
#include "Drawable.h"

#include "Renderer/ModelLoader.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexAttribLayout.h"
#include "Renderer/IndexBuffer.h"

namespace re
{
	class Mesh : public Drawable
	{
	public:

		Mesh(const std::string& a_modelPath, const std::string& a_texturePath, Transform a_transform, Shader& a_shader);
		~Mesh() = default;

		void Draw() const;
		const size_t GetVertexCount() const { return m_vertices.size(); }
		const Transform& GetTransform() const { return m_transform; }

		void SetTransform(Transform a_transform) { m_transform = a_transform; }

		std::vector<ModelLoader::Vertex> m_vertices;
		std::vector<uint32_t> m_indices;

	private:

		Transform m_transform;

		std::unique_ptr<Texture> m_texture;
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vbo;
		std::unique_ptr<IndexBuffer> m_ebo;
	};
}