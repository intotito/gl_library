#pragma once
#include<Object.hpp>

class HollowCylinder : public Object {
public:
	HollowCylinder();
	HollowCylinder(int segments, float radius);
	~HollowCylinder();

private:
	void GenerateMesh();
	int segments;
	float radius;
};