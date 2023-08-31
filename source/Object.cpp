#include <Object.hpp>

Object::Object() : indices(nullptr), indexCount(0)
{
	transpose_inverse_matrix = glm::mat3(glm::transpose(glm::inverse(model_matrix)));
}

Object::~Object()
{
	delete indices;
}

void Object::AddMesh(Mesh mesh)
{
	Object::mesh.push_back(mesh);
}

int Object::GetCount()
{
	int count = 0;
	for (int i = 0; i < mesh.size(); i++)
	{
		count += mesh[i].GetCount();
	}
	return count;
}

glm::mat4 Object::GetModelMatrix()
{
	if (state_changed) {
		model_matrix[3][0] = translation.x;
		model_matrix[3][1] = translation.y;
		model_matrix[3][2] = translation.z;
	} 
	state_changed = false;
	return model_matrix;
}

void Object::Translate(glm::vec3 translation) {
	if(!glm::all(glm::equal(Object::translation, translation))){
		state_changed = true;
	}
	Object::translation = translation;

}

void Object::RTranslate(glm::vec3 rTranslation) {
	translation += rTranslation;
	if (glm::length(rTranslation) > glm::epsilon<float>()) {
		state_changed = true;
	}
}

void Object::GenerateIndices()
{
	int vertexPerFace = 4; // quadilateral
	int trianglePerFace = (vertexPerFace - 3) + 1;
	int faces = GetCount() / vertexPerFace;
	int triangles = faces * trianglePerFace;

	indexCount = triangles * 3;

	indices = (unsigned int*)malloc(sizeof(unsigned int) * indexCount);
	int seq[6] = {0, 1, 2, 2, 3, 0};
	for (int i = 0; i < faces; i++) {	// 12
		int aaa = i * 4;
		for (int j = 0; j < (sizeof(seq) / sizeof(int)); j++) {		// 6

			unsigned int index = (i * ((sizeof(seq) / sizeof(int)))) + j;
			unsigned int value = aaa + seq[j];

			*(indices + index) = value;
		}
	}

}