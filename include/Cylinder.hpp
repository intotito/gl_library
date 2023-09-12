#pragma once
#include <Object.hpp>

class Cylinder : public Object {
public:
	Cylinder();
	Cylinder(int segments);
	virtual ~Cylinder();
private:
	void GenerateMesh();
	int stacks;
	int segments;
	float radius;
};