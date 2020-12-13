#include "repch.h"
#include "Drawables/Line.h"

namespace re
{
	Line::Line(Transform& a_transform, Shader& a_shader)
		: m_transform(&a_transform), m_shader(&a_shader) {}

	Line::Line(const glm::vec3& a_start, const glm::vec3& a_end, Transform& a_transform, Shader& a_shader)
		: m_transform(&a_transform), m_shader(&a_shader)
	{
		m_points.push_back(a_start);
		m_points.push_back(a_end);
	}

	Line::Line(const std::vector<glm::vec3>& a_points, Transform& a_transform, Shader& a_shader)
		: m_points(a_points), m_transform(&a_transform), m_shader(&a_shader) {}

	void Line::Draw() const
	{
		glVertexPointer(3, GL_FLOAT, 0, m_points.data());
		GLCheckError(glDrawArrays(GL_LINE_LOOP, 0, static_cast<GLsizei>(m_points.size())));
	}
}