#include "repch.h"
#include "Renderer/Camera.h"

namespace re
{
	Camera::Camera(const glm::vec3& a_pos, float a_fov, float a_aspect, float a_zNear, float a_zFar)
		: m_pos(a_pos)
	{
		m_projection = glm::perspective(a_fov, a_aspect, a_zNear, a_zFar);
	}

	void Camera::Update(float a_deltaTime, GLFWwindow* a_window)
	{
		// Keyboard movement
		if (glfwGetKey(a_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_pos += (m_forward * m_cameraSpeed) * a_deltaTime;
		}
		if (glfwGetKey(a_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_pos -= (m_forward * m_cameraSpeed) * a_deltaTime;
		}
		if (glfwGetKey(a_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_pos -= (glm::normalize(glm::cross(m_forward, m_up)) * m_cameraSpeed) * a_deltaTime;
		}
		if (glfwGetKey(a_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_pos += (glm::normalize(glm::cross(m_forward, m_up)) * m_cameraSpeed) * a_deltaTime;
		}

		glfwGetCursorPos(a_window, &xCurPos, &yCurPos);

		// Mouse movement
		if (glfwGetMouseButton(a_window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		{
			if (firstMouse)
			{
				lastX = xCurPos;
				lastY = yCurPos;
				firstMouse = false;
			}

			float xoffset = static_cast<float>(xCurPos - lastX);
			float yoffset = static_cast<float>(lastY - yCurPos);
			lastX = xCurPos;
			lastY = yCurPos;

			xoffset *= m_cameraSensitivity;
			yoffset *= m_cameraSensitivity;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			m_forward = glm::normalize(direction);
		}

		if (glfwGetMouseButton(a_window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
		{
			lastX = xCurPos;
			lastY = yCurPos;
		}
	}
}