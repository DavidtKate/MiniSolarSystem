#include "repch.h"
#include "Renderer/PointLight.h"

#include "Renderer/Shader.h"
#include "Renderer/Camera.h"

namespace re
{
	void PointLight::Update()
	{
		m_shader->Bind();
		m_shader->SetUniform<glm::vec3>("u_viewPos", m_camera->GetPosition());
		m_shader->SetUniform<glm::vec3>("u_light.position", m_position);
		m_shader->SetUniform<glm::vec3>("u_light.color", m_color);
		m_shader->SetUniform<float>("u_light.ambientCoef", m_ambientCoef);
		m_shader->SetUniform<float>("u_light.specularCoef", m_specularCoef);
	}
}