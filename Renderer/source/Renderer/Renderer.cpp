#include "repch.h"
#include "Renderer/Renderer.h"

#include "Drawables/Drawable.h"
#include "Resources/Shader.h"
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

	void Renderer::AddDrawable(Drawable& a_drawable)
	{
		m_drawables.push_back(&a_drawable);
	}

	void Renderer::RemoveDrawable(Drawable& a_drawable)
	{
		// Use erase-remove idiom
		m_drawables.erase(std::remove(m_drawables.begin(), m_drawables.end(), &a_drawable), m_drawables.end());
	}

	void Renderer::AddLight(PointLight& a_light)
	{
		m_lights.push_back(&a_light);
	}

	void Renderer::RemoveLight(PointLight& a_light)
	{
		// Use erase-remove idiom
		m_lights.erase(std::remove(m_lights.begin(), m_lights.end(), &a_light), m_lights.end());
	}

	void Renderer::Update(float)
	{
		// Update lights
		for (auto& light : m_lights)
		{
			light->Update();
		}

		// Update stats
		stats.drawables = m_drawables.size();
		stats.vertices = 0;

		for (auto& drawable : m_drawables)
		{
			stats.vertices += drawable->GetVertexCount();
		}
	}

	void Renderer::Draw() const
	{
		for (auto& drawable : m_drawables)
		{
			drawable->Draw();
		}
	}
}