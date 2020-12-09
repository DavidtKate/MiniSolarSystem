#pragma once
#include "Drawable.h"

#include "Renderer/Shader.h"
#include "Renderer/Transform.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexAttribLayout.h"

namespace re
{
	class Line : public Drawable
	{
	public:

		Line(Transform a_transform, Shader& a_shader);
		Line(glm::vec3 a_start, glm::vec3 a_end, Transform a_transform, Shader& a_shader);
		Line(std::vector<glm::vec3> a_points, Transform a_transform, Shader& a_shader);
		~Line() = default;

		void AddPoint(const glm::vec3& a_point) { m_points.push_back(a_point); }
		void RemovePoint(unsigned int a_pos) { m_points.erase(m_points.begin() + a_pos); }
		void SetPoints(const std::vector<glm::vec3>& a_points) { m_points = a_points; }
		const std::vector<glm::vec3> GetPoints() const { return m_points; }

		void Draw() const;
		const size_t GetVertexCount() const { return sizeof(m_points) / sizeof(m_points[0]); }
		const Transform& GetTransform() const { return m_transform; }

	private:

		std::vector<glm::vec3> m_points;

		Transform m_transform;

		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vbo;
	};
}