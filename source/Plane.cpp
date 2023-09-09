#include <Plane.hpp>

Plane::Plane()
{
	GenerateMesh();
}

Plane::~Plane()
{

}

void Plane::GenerateMesh()
{
	vec3 A[4] = {
		vec3(-0.5f,  0.5f, 0.0f),
		vec3(-0.5f, -0.5f, 0.0f),
		vec3( 0.5f, -0.5f, 0.0f),
		vec3( 0.5f,  0.5f, 0.0f)
	};
	Mesh* mesh = new Mesh((float*)(&( A[0].x)), sizeof(A) / sizeof(float));
	std::cout << "Check am odogwu ---------------- " <<  sizeof(A) / sizeof(float) << std::endl;
}