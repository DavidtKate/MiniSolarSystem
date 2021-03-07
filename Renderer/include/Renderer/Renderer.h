#pragma once
#include "Renderer/Camera.h"

namespace re
{
	class Drawable;
	class Shader;
	class PointLight;

	// Singleton class
	class Renderer
	{
	public:

		static Renderer& GetInstance();

		void Clear() const;

		void AddDrawable(Drawable& a_drawable);
		void RemoveDrawable(Drawable& a_drawable);

		void AddLight(PointLight& a_light);
		void RemoveLight(PointLight& a_light);

		void Update(float a_deltaTime);
		void Draw() const;

		void SetCamera(Camera& a_camera) { m_camera = &a_camera; }
		Camera& GetCamera() const { return *m_camera; }

		struct Stats
		{
			size_t vertices = 0;
			size_t drawables = 0;
		} stats;

	private:

		Renderer() = default;
		~Renderer() = default;

		Camera* m_camera = nullptr;
		std::vector<Drawable*> m_drawables;
		std::vector<PointLight*> m_lights;
	};
}