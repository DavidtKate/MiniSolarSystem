#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include "Renderer/PointLight.h"
#include "Objects/Object.h"
#include "DebugWindow.h"

class Scene
{
public:

	Scene() = default;
	~Scene() = default;

	void Init();
	void Update(float a_deltaTime, GLFWwindow& a_window);

private:

	std::unique_ptr<re::Shader> m_defaultShader, m_unlitShader;
	std::unique_ptr<re::Camera> m_camera;
	std::unique_ptr<re::PointLight> m_pointLight;
	std::unique_ptr<DebugWindow> m_debugWindow;
	std::vector<std::unique_ptr<Object>> m_objects;
};