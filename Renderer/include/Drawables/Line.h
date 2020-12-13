#pragma once
#include "Drawable.h"

namespace re
{
	class Line : public Drawable
	{
	public:

		Line(Transform& a_transform, Shader& a_shader);
		Line(const glm::vec3& a_start, const glm::vec3& a_end, Transform& a_transform, Shader& a_shader);
		Line(const std::vector<glm::vec3>& a_points, Transform& a_transform, Shader& a_shader);
		~Line() override = default;

		void AddPoint(const glm::vec3& a_point) { m_points.push_back(a_point); }
		void RemovePoint(unsigned int a_index) { m_points.erase(m_points.begin() + a_index); }
		const std::vector<glm::vec3>& GetPoints() const { return m_points; }
		void SetPoints(const std::vector<glm::vec3>& a_points) { m_points = a_points; }

		void Draw() const override;
		const Transform& GetTransform() const override { return *m_transform; }
		Shader& GetShader() const override { return *m_shader; }
		size_t GetVertexCount() const override { return sizeof(m_points) / sizeof(m_points[0]); }

		void SetTransform(Transform& a_transform) override { m_transform = &a_transform; }

	private:

		std::vector<glm::vec3> m_points;

		Transform* m_transform = nullptr;
		Shader* m_shader = nullptr;
	};
}