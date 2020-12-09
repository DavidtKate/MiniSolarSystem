#include "repch.h"
#include "Renderer/Renderer.h"

#include "Drawables/Drawable.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/PointLight.h"

namespace re
{
	Renderer& Renderer::GetInstance()
	{
		static Renderer s_instance;
		return s_instance;
	}

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Renderer::AddDrawable(Drawable* a_drawable)
	{
		if (a_drawable != nullptr)
		{
			m_drawables.push_back(a_drawable);
		}
	}

	void Renderer::RemoveDrawable(Drawable* a_drawable)
	{
		if (a_drawable != nullptr)
		{
			m_drawables.erase(std::remove(m_drawables.begin(), m_drawables.end(), a_drawable), m_drawables.end());
		}
	}

	void Renderer::AddLight(PointLight* a_light)
	{
		m_lights.push_back(a_light);
	}

	void Renderer::Update(float)
	{
		// Update lights
		for (PointLight* light : m_lights)
		{
			if (light != nullptr)
			{
				light->Update();
			}
		}

		// Update stats
		stats.drawables = m_drawables.size();
		stats.vertices = 0;

		for (Drawable* drawable : m_drawables)
		{
			stats.vertices += drawable->GetVertexCount();
		}
	}

	void Renderer::Draw(Shader& a_shader, Camera& a_camera) const
	{
		glm::mat4 viewProj = a_camera.GetViewProjection();

		for (Drawable* drawable : m_drawables)
		{
			if (drawable != nullptr)
			{
				glm::mat4 model = drawable->GetTransform().GetModel();
				glm::mat4 mvp = viewProj * model;

				a_shader.Bind();
				a_shader.SetUniform<glm::mat4>("u_MVP", mvp);
				a_shader.SetUniform<glm::mat4>("u_Model", model);

				drawable->Draw();
			}
		}
	}
}