#pragma once
#include<Object.hpp>
#include<vector>
#include<vendor/glm/glm.hpp>
class Sphere : public Object
{
public:
	Sphere();
	Sphere(int stacks, int segments);
	~Sphere();
private:
	void GenerateMesh();
	int stacks;
	int segments;
	float radius;
};