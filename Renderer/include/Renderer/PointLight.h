#pragma once

namespace re
{
	class Shader;
	class Camera;

	class PointLight
	{
	public:

		PointLight(glm::vec3 a_position, glm::vec3 a_color, Shader& a_shader, Camera& a_camera)
			: m_position(a_position), m_color(a_color), m_shader(&a_shader), m_camera(&a_camera) {}
		~PointLight() = default;

		void Update();

		const glm::vec3& GetPosition() const { return m_position; }
		const glm::vec3& GetColor() const { return m_color; }

		void SetPosition(glm::vec3 a_targetPosition) { m_position = a_targetPosition; }
		void SetColor(glm::vec3 a_targetColor) { m_color = a_targetColor; }
		void SetAmbientCoefficient(float a_targetAmbientCoeff) { m_ambientCoef = a_targetAmbientCoeff; }
		void SetSpecularCoefficient(float a_targetSpecularCoef) { m_specularCoef = a_targetSpecularCoef; }

	private:

		Shader* m_shader = nullptr;
		Camera* m_camera = nullptr;

		glm::vec3 m_position = glm::vec3(0.0f);
		glm::vec3 m_color = glm::vec3(1.0f);
		float m_ambientCoef = 0.1f;
		float m_specularCoef = 0.1f;
	};
}