#pragma once

namespace re
{
	class Transform
	{
	public:

		Transform(const glm::vec3& a_pos = glm::vec3(0.0f), const glm::vec3& a_rot = glm::vec3(0.0f), const glm::vec3& a_scale = glm::vec3(1.0f))
			: m_pos(a_pos), m_rot(a_rot), m_scale(a_scale) {}
		~Transform() = default;

		const glm::vec3& GetPosition() const { return m_pos; }
		const glm::vec3& GetRotation() const { return m_rot; }
		const glm::vec3& GetScale() const { return m_scale; }

		void SetPosition(const glm::vec3& a_pos) { m_pos = a_pos; }
		void SetRotation(const glm::vec3& a_rot) { m_rot = a_rot; }
		void SetScale(const glm::vec3& a_scale) { m_scale = a_scale; }

		glm::mat4 GetModel() const
		{
			glm::mat4 posMat = glm::translate(glm::mat4(1.f), m_pos);
			glm::mat4 scaleMat = glm::scale(glm::mat4(1.f), m_scale);
			glm::mat4 rotX = glm::rotate(glm::mat4(1.f), m_rot.x, glm::vec3(1.0, 0.0, 0.0));
			glm::mat4 rotY = glm::rotate(glm::mat4(1.f), m_rot.y, glm::vec3(0.0, 1.0, 0.0));
			glm::mat4 rotZ = glm::rotate(glm::mat4(1.f), m_rot.z, glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 rotMat = rotX * rotY * rotZ;

			return posMat * rotMat * scaleMat;
		}

	private:

		glm::vec3 m_pos = glm::vec3(0.0f);
		glm::vec3 m_rot = glm::vec3(0.0f);
		glm::vec3 m_scale = glm::vec3(1.0f);
	};
}