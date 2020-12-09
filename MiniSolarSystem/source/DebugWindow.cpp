#include "repch.h"
#include "DebugWindow.h"

#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "Renderer/PointLight.h"

#include "imgui/imgui.h"

DebugWindow::DebugWindow(re::Camera* a_camera, re::PointLight* a_light)
	: m_camera(a_camera), m_light(a_light)
{
}

void DebugWindow::Update()
{
	// ImGui stats window
	ImGui::Begin("Stats");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Text("Amount of vertices: %i", re::Renderer::GetInstance().stats.vertices);
	ImGui::Text("Amount of drawables: %i", re::Renderer::GetInstance().stats.drawables);
	ImGui::End();

	// Camera settings window
	ImGui::Begin("Camera");
	ImGui::SliderFloat("Speed", &m_cameraSpeed, 1.0f, 100.0f);
	ImGui::SliderFloat("Sensitivity", &m_cameraSensitivity, 0.1f, 0.4f);
	ImGui::End();

	m_camera->SetCameraSpeed(m_cameraSpeed);
	m_camera->SetCameraSensitivity(m_cameraSensitivity);

	// Renderer settings window
	ImGui::Begin("Renderer");
	if (ImGui::InputFloat3("Light Position", m_lightPosition))
	{
		m_light->SetPosition(glm::vec3(m_lightPosition[0], m_lightPosition[1], m_lightPosition[2]));
	}

	if (ImGui::ColorPicker3("Light Color", m_lightColor))
	{
		m_light->SetColor(glm::vec3(m_lightColor[0], m_lightColor[1], m_lightColor[2]));
	}

	if (ImGui::SliderFloat("Light Ambient Coefficient", &m_lightAmbientCoef, 0.1f, 0.5f))
	{
		m_light->SetAmbientCoefficient(m_lightAmbientCoef);
	}

	if (ImGui::SliderFloat("Light Specular Coefficient", &m_lightSpecularCoef, 0.1f, 1.f))
	{
		m_light->SetSpecularCoefficient(m_lightSpecularCoef);
	}
	ImGui::End();
}