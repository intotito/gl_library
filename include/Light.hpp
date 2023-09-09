#pragma once
#include<vendor/glm/glm.hpp>
class Light {
public:
	Light();
	~Light();
private:
	glm::vec3 location;
};