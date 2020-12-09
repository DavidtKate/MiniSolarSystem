#pragma once
#include "Objects/Object.h"
#include "Drawables/Mesh.h"

namespace re
{
	class Transform;
	class Shader;
}

class Planet : public Object
{
public:

	Planet(re::Transform a_transform, float a_mass, float a_radius, glm::vec3 a_initialVelocity, const std::string& a_texturePath, re::Shader& a_shader);
	~Planet() = default;

	void Update(float a_deltaTime);
	void UpdateVelocity(float a_deltaTime);
	void UpdatePosition(float a_deltaTime);

	const glm::vec3& GetPosition() const { return m_mesh->GetTransform().GetPosition(); };
	const glm::vec3& GetRotation() const { return m_mesh->GetTransform().GetRotation(); };
	const glm::vec3& GetScale() const { return m_mesh->GetTransform().GetScale(); };

	const float GetMass() const { return m_mass; }
	const float GetRadius() const { return m_radius; }

private:

	std::unique_ptr<re::Mesh> m_mesh;
	re::Shader* m_shader = nullptr;
	float m_mass = 1.0f;
	float m_radius = 1.0f;
	glm::vec3 m_currVelocity = glm::vec3(0.0f);
};