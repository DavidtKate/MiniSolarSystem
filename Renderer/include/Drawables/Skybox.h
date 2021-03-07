#pragma once
#include "Drawable.h"

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexAttribLayout.h"

namespace re
{
	class Skybox : public Drawable
	{
	public:

        Skybox(const std::string& a_skyboxFolder, Transform a_transform, const std::string& a_shaderName);
		~Skybox() override;

		void Draw() const override;
		void SetTransform(Transform& a_transform) override { m_transform = &a_transform; }
		const Transform& GetTransform() const override { return *m_transform; }
        size_t GetVertexCount() const override { return m_vertices.size(); }

	private:

        void CreateCubeMap(const std::string& a_skyboxFolder);

        std::vector<float> m_vertices = {
            // pos       
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

		Transform* m_transform = nullptr;
		Shader* m_shader = nullptr;

        unsigned int m_textureID;
        unsigned char* m_cubeMapBuffer;
        int m_cubeMapWidth, m_cubeMapHeight, m_cubeMapChannels;
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vbo;
	};
}