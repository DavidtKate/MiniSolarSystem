#pragma once
#include "Renderer/Transform.h"

// Abstract class
namespace re
{
	class Drawable
	{
	public:

		virtual ~Drawable() = default;

		virtual void Draw() const = 0;
		virtual const Transform& GetTransform() const = 0;
		virtual const size_t GetVertexCount() const = 0;
	};
}