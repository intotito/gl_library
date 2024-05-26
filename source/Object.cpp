#include <Object.hpp>

Object::Object() :	indices(nullptr), indexCount(0), sceneAddress(0), vb(NULL), transform(Transform())//, indexAddress(0)
{
	transform.SetContainer(this);
}

Object::~Object()
{
	free(indices);
}

void Object::AddMesh(Mesh mesh)
{
	Object::mesh.push_back(mesh);
}

float* Object::GetData()
{
	return mesh[0].Data();
}

unsigned int Object::GetCount()
{
	unsigned int count = 0;
	for (int i = 0; i < mesh.size(); i++)
	{
		count += mesh[i].GetRawCount();
	}
	return count;
}

void Object::TransformObject(glm::mat4 matrix) {
	for (int i = 0; i < mesh.size(); i++)
	{
		mesh[i].Transform(matrix);
	}
}

unsigned int* Object::GetIndices(unsigned int offset) const
{
	unsigned int* ind = (unsigned int*)malloc(sizeof(unsigned int) * indexCount);
	for (int i = 0; i < indexCount; i++)
	{
		*(ind + i) = offset + *(indices + i);	// I know what I am doing
	}
	return ind;
}

void Object::GenerateIndices()
{
	int vertexPerFace = 4; // quadilateral
	int trianglePerFace = (vertexPerFace - 3) + 1; // 2
	int faces = GetCount() / vertexPerFace;
	int triangles = faces * trianglePerFace;

	indexCount = triangles * 3;

	indices = (unsigned int*)malloc(sizeof(unsigned int) * indexCount);
	int seq[6] = { 0, 1, 2, 2, 3, 0 };
	for (int i = 0; i < faces; i++) {	// 12
		int aaa = i * 4;
		for (int j = 0; j < (sizeof(seq) / sizeof(int)); j++) {		// 6
			unsigned int index = (i * ((sizeof(seq) / sizeof(int)))) + j;
			unsigned int value = aaa + seq[j];
			*(indices + index) = value;
		}
	}

}

void Object::OnUpdate(float deltaTime)
{
	transform.Update();
}

void Object::OnStart()
{
	transform.Update();
}