#pragma once

// Meyers Singleton class
namespace re
{
	class Drawable;
	class Shader;
	class Camera;
	class PointLight;

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
		void Draw(Camera& a_camera) const;

		struct Stats
		{
			size_t vertices = 0;
			size_t drawables = 0;
		} stats;

	private:

		Renderer() = default;
		~Renderer() = default;

		std::vector<Drawable*> m_drawables;
		std::vector<PointLight*> m_lights;
	};
}