#pragma once
#include "Renderer/Transform.h"
#include "Resources/Shader.h"

// Abstract class
namespace re
{
	class Drawable
	{
	public:

		virtual ~Drawable() = default;

		virtual void Draw() const = 0;

		virtual const Transform& GetTransform() const = 0;
		virtual size_t GetVertexCount() const = 0;

		virtual void SetTransform(Transform& a_transform) = 0;
	};
}