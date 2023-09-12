#pragma once
#include <Object.hpp>

class Plane : public Object {
public:
	Plane();
	~Plane();
private:
	void GenerateMesh();
};