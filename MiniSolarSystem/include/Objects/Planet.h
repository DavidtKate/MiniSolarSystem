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

	Planet(re::Transform a_transform, float a_mass, float a_radius, const glm::vec3& a_initialVelocity, const std::string& a_textureName, const std::string& a_shaderName);
	~Planet() override = default;

	void Update(float a_deltaTime) override;

	const re::Transform& GetTransform() const override{ return m_transform; }

	float GetMass() const { return m_mass; }
	float GetRadius() const { return m_radius; }

private:

	std::unique_ptr<re::Mesh> m_mesh;
	re::Transform m_transform;

	float m_mass = 1.0f;
	float m_radius = 1.0f;
	glm::vec3 m_currVelocity = glm::vec3(0.0f);
};