#include "repch.h"
#include "Objects/Planet.h"

#include "Renderer/Renderer.h"
#include "Renderer/Transform.h"
#include "Renderer/Shader.h"

#include "Managers/PlanetManager.h"

Planet::Planet(re::Transform a_transform, float a_mass, float a_radius, glm::vec3 a_initialVelocity, const std::string& a_texturePath, re::Shader& a_shader)
	: m_mass(a_mass), m_radius(a_radius), m_currVelocity(a_initialVelocity), m_shader(&a_shader)
{
	m_mesh = std::make_unique<re::Mesh>("resources/models/planet.obj", a_texturePath, a_transform, a_shader);
	re::Renderer::GetInstance().AddDrawable(m_mesh.get());

	PlanetManager::GetInstance().AddPlanet(this);
}

void Planet::Update(float a_deltaTime)
{
	UpdateVelocity(a_deltaTime);
	UpdatePosition(a_deltaTime);
}

void Planet::UpdateVelocity(float a_deltaTime)
{
	for (Planet* planet : PlanetManager::GetInstance().GetPlanets())
	{
		if (planet != this)
		{
			glm::vec3 dist = planet->GetPosition() - this->GetPosition();
			float sqrDist = glm::length(dist);

			glm::vec3 forceDir = glm::normalize(dist);
			glm::vec3 force = forceDir * 0.0001f * m_mass * planet->GetMass() / sqrDist;
			glm::vec3 acceleration = force / m_mass;

			m_currVelocity += acceleration * a_deltaTime;
		}
	}
}

void Planet::UpdatePosition(float a_deltaTime)
{
	glm::vec3 currPos = this->GetPosition();

	re::Transform newTransform = m_mesh->GetTransform();
	newTransform.SetPosition(currPos + m_currVelocity * a_deltaTime);
	m_mesh->SetTransform(newTransform);
}