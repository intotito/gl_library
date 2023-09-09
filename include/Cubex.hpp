#pragma once
#include <Object.hpp>
class Cubex : public Object {
public:
	Cubex();
	~Cubex();
private:
	void GenerateMesh();
};