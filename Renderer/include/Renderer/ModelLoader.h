#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

namespace re
{
	class ModelLoader
	{
	public:

		static ModelLoader& GetInstance();

		struct Vertex
		{
			float xPos;
			float yPos;
			float zPos;
			float xTexcoord;
			float yTexcoord;
			float xNormal;
			float yNormal;
			float zNormal;

			bool operator==(const Vertex& other) const {
				return xPos == other.xPos && yPos == other.yPos && zPos == other.zPos && xTexcoord == other.xTexcoord && yTexcoord == other.yTexcoord
					&& xNormal == other.xNormal && yNormal == other.yNormal && zNormal == other.zNormal;
			}
		};

		void LoadModel(const std::string& a_modelPath, std::vector<ModelLoader::Vertex>& a_vertices, std::vector<uint32_t>& a_indices);

	private:

		ModelLoader() = default;
		~ModelLoader() = default;
	};
}

template<> struct std::hash<re::ModelLoader::Vertex>
{
	size_t operator()(re::ModelLoader::Vertex const& vertex) const
	{
		return ((std::hash<glm::vec3>()(glm::vec3(vertex.xPos, vertex.yPos, vertex.zPos)) ^
			(std::hash<glm::vec2>()(glm::vec2(vertex.xTexcoord, vertex.yTexcoord)) << 1)));
	}
};