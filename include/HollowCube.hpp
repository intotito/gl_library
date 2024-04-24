#pragma once
#include<Object.hpp>

class HollowCube : public Object{
public:
	HollowCube();
	HollowCube(int segments, float radius);
	~HollowCube();

private:
	void GenerateMesh();
	int segments;
	float radius;
};