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
	int stride = sizeof(Vertex) / sizeof(float);
	vec3 A[4] = {
		vec3(-0.5f,  0.5f, 0.0f),
		vec3(-0.5f, -0.5f, 0.0f),
		vec3( 0.5f, -0.5f, 0.0f),
		vec3( 0.5f,  0.5f, 0.0f)
	};

	vec3 Normal = vec3(0.0f, 0.0f, 1.0f);

	vec2 UV[4] = {
		vec2(0.0f, 1.0f),
		vec2(0.0f, 0.0f), 
		vec2(1.0f, 0.0f), 
		vec2(1.0f, 1.0f)
	};
	float* data = new float[4 * stride];
	for (int i = 0; i < 4; i++) {
		int pointer = 0;
		float texId = 0.0f;
		std::copy(&A[i].x, &A[i].x + 3, data + (i * stride + pointer));		pointer += 3;
		std::copy(&Normal.x, &Normal.x + 3, data + (i * stride + pointer)); pointer += 3;
		std::copy(&UV[i].x, &UV[i].x + 2, data + (i * stride + pointer));	pointer += 2;
		std::copy(&texId, &texId + 1, data + (i * stride + pointer));
	}

	Mesh mesh = Mesh(data, 4 * stride);
	AddMesh(mesh);
	GenerateIndices();
	delete[] data;
}