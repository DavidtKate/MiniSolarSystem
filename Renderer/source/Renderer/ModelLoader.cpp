#include "repch.h"
#include "Renderer/ModelLoader.h"

#include "tiny_obj_loader/tiny_obj_loader.h"

namespace re
{
	ModelLoader& ModelLoader::GetInstance()
	{
		static ModelLoader s_modelLoader;
		return s_modelLoader;
	}

	void ModelLoader::LoadModel(const std::string& a_modelPath, std::vector<ModelLoader::Vertex>& a_vertices, std::vector<uint32_t>& a_indices)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, a_modelPath.c_str());

		if (!warn.empty())
		{
			std::cout << warn << std::endl;
		}

		if (!err.empty())
		{
			std::cerr << err << std::endl;
		}

		if (!ret)
		{
			exit(1);
		}

		std::unordered_map<Vertex, uint32_t> uniqueVertices{};

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); ++s)
		{
			// Loop over faces
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f)
			{
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices
				for (size_t v = 0; v < fv; ++v)
				{
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

					ModelLoader::Vertex vertex;

					// Vertex position
					vertex.xPos = attrib.vertices[3 * idx.vertex_index + 0];
					vertex.yPos = attrib.vertices[3 * idx.vertex_index + 1];
					vertex.zPos = attrib.vertices[3 * idx.vertex_index + 2];

					// Vertex texcoords
					vertex.xTexcoord = attrib.texcoords[2 * idx.texcoord_index + 0];
					vertex.yTexcoord = attrib.texcoords[2 * idx.texcoord_index + 1];

					// Vertex normal
					vertex.xNormal = attrib.normals[3 * idx.normal_index + 0];
					vertex.yNormal = attrib.normals[3 * idx.normal_index + 1];
					vertex.zNormal = attrib.normals[3 * idx.normal_index + 2];

					if (uniqueVertices.count(vertex) == 0)
					{
						uniqueVertices[vertex] = static_cast<uint32_t>(a_vertices.size());
						a_vertices.push_back(vertex);
					}

					a_indices.push_back(uniqueVertices[vertex]);
				}

				index_offset += fv;
			}
		}
	}
}