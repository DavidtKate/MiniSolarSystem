#pragma once

namespace re
{
	class Camera
	{
	public:

		Camera(const glm::vec3& a_pos, float a_fov, float a_aspect, float a_zNear, float a_zFar);
		~Camera() = default;

		void Update(float a_deltaTime, GLFWwindow& a_window);

		const glm::vec3 GetPosition() const { return m_pos; }
		const glm::vec3 GetForward() const { return m_forward; }
		const glm::vec3 GetUp() const { return m_up; }
		glm::mat4 GetView() const { return glm::lookAt(m_pos, m_pos + m_forward, m_up); }
		glm::mat4 GetProjection() const { return m_projection; }
		glm::mat4 GetViewProjection() const { return m_projection * glm::lookAt(m_pos, m_pos + m_forward, m_up); }

		void SetCameraSpeed(float a_newCameraSpeed) { m_cameraSpeed = a_newCameraSpeed; }
		void SetCameraSensitivity(float a_newCameraSensitivity) { m_cameraSensitivity = a_newCameraSensitivity; }

	private:

		glm::mat4 m_projection = glm::mat4(1.0f);
		glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_right = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 m_target = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_dir = glm::vec3(0.0f, 0.0f, 0.0f);
		float m_cameraSpeed = 50.0f;
		float m_cameraSensitivity = 0.2f;

		bool firstMouse = true;
		double lastX = 0, lastY = 0;
		float yaw = -90.0f, pitch = 0.0f;
		double xCurPos = 0, yCurPos = 0;
	};
}