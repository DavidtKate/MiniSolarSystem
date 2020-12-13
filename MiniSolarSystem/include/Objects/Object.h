#pragma once
#include "Renderer/Transform.h"

// Abstract Class
class Object
{
public:

	virtual ~Object() = default;

	virtual void Update(float a_deltaTime) = 0;

	virtual const re::Transform& GetTransform() const = 0;
};