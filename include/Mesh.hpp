#pragma once
#include <vendor/glm/glm.hpp>
#include <vendor/glm/ext/matrix_transform.hpp>
#include <vector>
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::vec2;
using glm::mat3;
using glm::mat4;
using glm::cos;
using glm::sin;
using std::vector;

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 texUV;
	float texID;
};

class Mesh {
public:
	Mesh(float* data, int size);
	~Mesh();
	float* Data();
	inline unsigned int GetVertexCount() { return vertices.size(); }
	inline unsigned int GetRawCount() { return vertices.size() * (sizeof(Vertex) / sizeof(float)); }
	inline void Add(Vertex v) { vertices.push_back(v); }
	void Format();


private:
	vec3 origin = vec3(0.0f, 0.0f, -0.5f);
	vec3 rotation = vec3(glm::radians(-90.0f), 0.0f, 0.0f);
	vector<Vertex> vertices;
	void Parse(float* data, int size);
};