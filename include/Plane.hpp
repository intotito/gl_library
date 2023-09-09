#pragma once
#include <Object.hpp>

class Plane : Object {
public:
	Plane();
	~Plane();
private:
	void GenerateMesh();
};