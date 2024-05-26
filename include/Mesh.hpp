#pragma once
#include <vendor/glm/glm.hpp>
#include <vendor/glm/ext/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include <Renderer.hpp>

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

enum Axis{X_AXIS, Y_AXIS, Z_AXIS};

class Mesh {
public:
	/**
	* Constructor.
	* 
	* Creates a mesh with vertices.
	* @param data array of vertices.
	* @param size size of the array.
	*/
	Mesh(float* data, int size);
	/**
	* Default Deconstructor.
	*/
	~Mesh();
	/**
	* Get data.
	* 
	* Get the mesh constituent data. 
	* @return a pointer to the vertices
	*/
	float* Data();
	/**
	* Get number of vertices in the Mesh. 
	* 
	* Get the total number of Vertex in the Mesh.
	*/
	inline unsigned int GetVertexCount() { return vertices.size(); }
	/**
	* Number of primitive (float) variables.
	* 
	* The total number of floating point variables contained in the mesh. 
	* ~~~~~~~~~~~~~~~~~~~~~~.cpp
	* GetVertexCount() * (sizeof(Vertex) / sizeof(float));
	* ~~~~~~~~~~~~~~~~~~~~~~
	* @return number of floating point variables.
	*/
	inline unsigned int GetRawCount() { return GetVertexCount() * (sizeof(Vertex) / sizeof(float)); }
	/**
	* Size of this Mesh.
	* 
	* The total size of this Mesh in bytes.
	* @return size of mesh in bytes.
	*/
	inline unsigned int GetByteSize() { return GetVertexCount() * sizeof(Vertex); }
	/**
	* Add a Vertex to this Mesh.
	* 
	* Add a Vertex to the list of vertices of this Mesh.
	* @param v the vertex to add.
	*/
	inline void Add(Vertex v) { vertices.push_back(v); }
	/**
	* Rotate Mesh from the origin.
	* @deprecated This method usage is discouraged. 
	* @see RotateJoint()
	*/
	void Format(float angle);
	/**
	* Rotate a Meshthrough an axis by an angle.
	* 
	* This method can be used to create specialized animation for an Object with 
	* serveral Meshes. 
	*/
	void RotateJoint(float angle, Axis axis);
	vec3 rotation = vec3(glm::radians(-45.0f), 0.0f, 0.0f);
	void Transform(mat4 matrix);

private:
	vec3 origin = vec3(0.0f, 0.0f, 0.5f);
	vector<Vertex> vertices;
	void Parse(float* data, int size);
};