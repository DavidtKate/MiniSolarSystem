#include "repch.h"
#include "Objects/Planet.h"

#include "Renderer/Renderer.h"
#include "Renderer/Transform.h"
#include "Resources/Shader.h"

#include "Managers/PlanetManager.h"

Planet::Planet(re::Transform a_transform, float a_mass, float a_radius, const glm::vec3& a_initialVelocity, const std::string& a_textureName, const std::string& a_shaderName)
	: m_transform(a_transform), m_mass(a_mass), m_radius(a_radius), m_currVelocity(a_initialVelocity)
{
	m_mesh = std::make_unique<re::Mesh>("resources/models/planet.obj", a_transform, a_textureName, a_shaderName);
	re::Renderer::GetInstance().AddDrawable(*m_mesh);

	PlanetManager::GetInstance().AddPlanet(*this);
}

void Planet::Update(float a_deltaTime)
{
	// Update velocity
	for (Planet* planet : PlanetManager::GetInstance().GetPlanets())
	{
		if (planet != this)
		{
			glm::vec3 dist = planet->GetTransform().GetPosition() - m_transform.GetPosition();
			float sqrDist = glm::length(dist);

			glm::vec3 forceDir = glm::normalize(dist);
			glm::vec3 force = forceDir * 0.0001f * m_mass * planet->GetMass() / sqrDist;
			glm::vec3 acceleration = force / m_mass;

			m_currVelocity += acceleration * a_deltaTime;
		}
	}

	// Update position
	m_transform.SetPosition(m_transform.GetPosition() + m_currVelocity * a_deltaTime);
	m_mesh->SetTransform(m_transform);
}