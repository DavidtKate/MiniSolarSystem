#include "repch.h"
#include "Scene.h"

#include "Renderer/Renderer.h"
#include "Objects/Planet.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 800

void Scene::Init()
{
	// Create default shader
	m_shader = std::make_unique<re::Shader>("resources/shaders/default.vert", "resources/shaders/default.frag");

	// Create Sun
	m_objects.push_back(std::make_unique<Planet>(
		re::Transform(
			glm::vec3(0.0f),	// Position
			glm::vec3(0.0f),	// Rotation
			glm::vec3(0.3f)),	// Scale
		1000000.0f,				// Mass
		6.37f,					// Radius
		glm::vec3(0.0f),
		"resources/textures/sun.jpg",
		*m_shader));


	// Create planet 1
	m_objects.push_back(std::make_unique<Planet>(
		re::Transform(
			glm::vec3(15, 0.0f, 0.0f),	// Position
			glm::vec3(0.0f),			// Rotation
			glm::vec3(0.1f)),			// Scale
		1.0f,							// Mass
		1.74f,							// Radius
		glm::vec3(0.0f, 10.0f, 0.0f),
		"resources/textures/mercury.jpg",
		*m_shader));

	// Create planet 2
	m_objects.push_back(std::make_unique<Planet>(
		re::Transform(
			glm::vec3(-30.f, 0.0f, 0.0f),	// Position
			glm::vec3(0.0f),				// Rotation
			glm::vec3(0.2f)),				// Scale
		1.0f,								// Mass
		1.74f,								// Radius
		glm::vec3(0.0f, -10.0f, 0.0f),
		"resources/textures/earth.jpg",
		*m_shader));

	// Create planet 3
	m_objects.push_back(std::make_unique<Planet>(
		re::Transform(
			glm::vec3(50.f, 0.0f, 0.0f),	// Position
			glm::vec3(0.0f),				// Rotation
			glm::vec3(0.3f)),				// Scale
		1.0f,								// Mass
		1.74f,								// Radius
		glm::vec3(0.0f, 10.0f, 0.0f),
		"resources/textures/neptune.jpg",
		*m_shader));

	// Create camera
	m_camera = std::make_unique<re::Camera>(glm::vec3(0.0f, 0.0f, 200.0f), 70.f, static_cast<float>(SCREENWIDTH) / static_cast<float>(SCREENHEIGHT), 0.01f, 1000.0f);

	// Create point light
	//PointLight* pointLight = new PointLight(glm::vec3(10.f), glm::vec3(1.f), *m_shader, *m_camera);
	m_pointLight = std::make_unique<re::PointLight>(glm::vec3(10.f), glm::vec3(1.f), *m_shader, *m_camera);
	re::Renderer::GetInstance().AddLight(m_pointLight.get());

	// Create debugwindow
	m_debugWindow = std::make_unique<DebugWindow>(m_camera.get(), m_pointLight.get());
}

void Scene::Update(float a_deltaTime, GLFWwindow* a_window)
{
	// Clear frame
	re::Renderer::GetInstance().Clear();

	// Update objects
	m_camera->Update(a_deltaTime, a_window);

	for (auto& object : m_objects)
	{
		Planet* planet = dynamic_cast<Planet*>(object.get());

		if (planet != nullptr)
		{
			planet->Update(a_deltaTime);
		}
	}

	// Render Scene
	re::Renderer::GetInstance().Update(a_deltaTime);
	re::Renderer::GetInstance().Draw(*m_shader, *m_camera);

	// Show debug info
	m_debugWindow->Update();
}