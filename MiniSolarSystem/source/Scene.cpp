#include "repch.h"
#include "Scene.h"

#include "Renderer/Renderer.h"
#include "Objects/Planet.h"

#include "Resources/ResourceManager.h"
#include "Resources/Shader.h"
#include "Resources/Texture.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 800

Scene::~Scene()
{
	re::ResourceManager::GetInstance().FreeResources();
}

void Scene::Init()
{
	// Create shaders
	re::ResourceManager::GetInstance().AddResource(re::resource_ptr(new re::Shader("resources/shaders/default.vert", "resources/shaders/default.frag")), "default");
	re::ResourceManager::GetInstance().AddResource(re::resource_ptr(new re::Shader("resources/shaders/default.vert", "resources/shaders/unlit.frag")), "unlit");
	re::ResourceManager::GetInstance().AddResource(re::resource_ptr(new re::Shader("resources/shaders/skybox.vert", "resources/shaders/skybox.frag")), "skybox");

	// Create textures
	re::ResourceManager::GetInstance().AddResource(re::resource_ptr(new re::Texture("resources/textures/sun.jpg")), "sun");
	re::ResourceManager::GetInstance().AddResource(re::resource_ptr(new re::Texture("resources/textures/mercury.jpg")), "mercury");
	re::ResourceManager::GetInstance().AddResource(re::resource_ptr(new re::Texture("resources/textures/earth.jpg")), "earth");
	re::ResourceManager::GetInstance().AddResource(re::resource_ptr(new re::Texture("resources/textures/neptune.jpg")), "neptune");

	// Create camera
	m_camera = std::make_unique<re::Camera>(glm::vec3(0.0f, 0.0f, 200.0f), 70.f, static_cast<float>(SCREENWIDTH) / static_cast<float>(SCREENHEIGHT), 0.01f, 1000.0f);
	re::Renderer::GetInstance().SetCamera(*m_camera);

	// Create Sun
	m_objects.emplace_back(std::make_unique<Planet>(
		re::Transform(
			glm::vec3(0.0f),
			glm::vec3(0.0f),
			glm::vec3(0.3f)),
		1000000.0f,
		6.37f,
		glm::vec3(0.0f),
		"sun",
		"unlit"));

	// Create planet 1
	m_objects.emplace_back(std::make_unique<Planet>(
		re::Transform(
			glm::vec3(15, 0.0f, 0.0f),
			glm::vec3(0.0f),
			glm::vec3(0.1f)),
		1000.0f,
		1.74f,
		glm::vec3(5.0f, -5.f, 0.0f),
		"mercury",
		"default"));

	// Create planet 2
	m_objects.emplace_back(std::make_unique<Planet>(
		re::Transform(
			glm::vec3(-30.f, 0.0f, 0.0f),
			glm::vec3(0.0f),
			glm::vec3(0.2f)),
		1.0f,
		1.74f,
		glm::vec3(0.0f, -10.0f, 0.0f),
		"earth",
		"default"));

	// Create planet 3
	m_objects.emplace_back(std::make_unique<Planet>(
		re::Transform(
			glm::vec3(50.f, 0.0f, 0.0f),
			glm::vec3(0.0f),
			glm::vec3(0.3f)),
		1.0f,
		1.74f,
		glm::vec3(0.0f, 10.0f, 0.0f),
		"neptune",
		"default"));

	// Create skybox
	m_skybox = std::make_unique<re::Skybox>("resources/textures/skybox", re::Transform(), "skybox");
	re::Renderer::GetInstance().AddDrawable(*m_skybox);

	// Create point light
	m_pointLight = std::make_unique<re::PointLight>(glm::vec3(10.f), glm::vec3(1.f), re::ResourceManager::GetInstance().GetResource<re::Shader>("default"), *m_camera);
	re::Renderer::GetInstance().AddLight(*m_pointLight);

	// Create debugwindow
	m_debugWindow = std::make_unique<DebugWindow>(*m_camera, *m_pointLight);
}

void Scene::Update(float a_deltaTime, GLFWwindow& a_window)
{
	// Clear frame
	re::Renderer::GetInstance().Clear();

	// Update objects
	m_camera->Update(a_deltaTime, a_window);

	for (auto& object : m_objects)
	{
		object->Update(a_deltaTime);
	}

	// Render Scene
	re::Renderer::GetInstance().Update(a_deltaTime);
	re::Renderer::GetInstance().Draw();

	// Show debug info
	m_debugWindow->Update();
}