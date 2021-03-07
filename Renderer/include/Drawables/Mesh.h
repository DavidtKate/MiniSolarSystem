#pragma once
#include "Drawable.h"

#include "Renderer/ModelLoader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexAttribLayout.h"
#include "Renderer/IndexBuffer.h"

namespace re
{
	class Texture;

	class Mesh : public Drawable
	{
	public:

		Mesh(const std::string& a_modelPath, Transform& a_transform, const std::string& a_textureName, const std::string& a_shaderName);
		~Mesh() override = default;

		void Draw() const override;
		void SetTransform(Transform& a_transform) override { m_transform = &a_transform; }
		const Transform& GetTransform() const override { return *m_transform; }
		size_t GetVertexCount() const override { return m_vertices.size(); }

		std::vector<ModelLoader::Vertex> m_vertices;
		std::vector<uint32_t> m_indices;

	private:

		Transform* m_transform = nullptr;
		Shader* m_shader = nullptr;
		Texture* m_texture = nullptr;
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vbo;
		std::unique_ptr<IndexBuffer> m_ebo;
	};
}