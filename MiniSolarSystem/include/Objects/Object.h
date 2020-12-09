#pragma once

// Abstract Class
class Object
{
public:

	virtual ~Object() = default;

	virtual void Update(float a_deltaTime) = 0;

	virtual const glm::vec3& GetPosition() const = 0;
	virtual const glm::vec3& GetRotation() const = 0;
	virtual const glm::vec3& GetScale() const = 0;
};