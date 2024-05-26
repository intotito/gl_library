#pragma once
#include<Object.hpp>

using glm::vec3;
using glm::vec2;
using std::vector;

class Jaw : public Object {
public:
	Jaw();
	virtual ~Jaw();
	static const float MAX_ANGLE_RAD;
	static const float MIN_ANGLE_RAD;
	virtual void OnUpdate(float deltaTime) override;
private:
	void RotateMesh(Mesh& mesh, float angle, Axis axis);
	int GetIndex(Mesh& mesh);
};
