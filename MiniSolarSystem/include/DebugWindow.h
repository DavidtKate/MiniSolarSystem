#pragma once

namespace re
{
	class Camera;
	class PointLight;
}

class DebugWindow
{
public:

	DebugWindow(re::Camera& a_camera, re::PointLight& a_light);
	~DebugWindow() = default;

	void Update();

private:

	re::Camera* m_camera = nullptr;
	re::PointLight* m_light = nullptr;

	// Camera
	float m_cameraSpeed = 50.0f;
	float m_cameraSensitivity = 0.2f;

	// Light
	float m_lightPosition[3] = { 10.0f, 10.0f, 10.0f};
	float m_lightColor[3] = { 1.0f, 1.0f, 1.0f };
	float m_lightAmbientCoef = 0.1f;
	float m_lightSpecularCoef = 0.1f;
};